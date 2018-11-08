//
//  YKSoftAPDetection.m
//  DeviceConfigDemo
//
//  Created by Don on 2017/1/16.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKSoftAPDetection.h"
#import <UIKit/UIKit.h>
#import "Reachability.h"
#import <SystemConfiguration/CaptiveNetwork.h>

typedef NS_ENUM(NSInteger, GizNetStatus) {
    GizNetStatusDisconnected,
    GizNetStatusConnecting,
    GizNetStatusConnected
};

@interface YKSoftAPDetection()

@property (assign) UIBackgroundTaskIdentifier taskid_atomic;

@property (strong) NSString *ssidPrefix_atomic;
@property (assign) id <YKSoftAPDetectionDelegate>delegate_atomic;
@property (strong) Reachability *netReach_atomic;
@property (assign) GizNetStatus netStatus_atomic;
@property (assign) BOOL netStatusChanged_atomic;

@end

@implementation YKSoftAPDetection

- (instancetype)initWithSoftAPSSID:(NSString *)ssidPrefix delegate:(id <YKSoftAPDetectionDelegate>)delegate {
    self = [super init];
    if (self) {
        self.ssidPrefix_atomic = ssidPrefix;
        self.delegate_atomic = delegate;
        self.netReach_atomic = [Reachability reachabilityWithHostName:@"www.yaokantv.com"];
        if (![self.netReach_atomic startNotifier]) {
            NSLog(@"startNotifier failed");
            return nil;
        }
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didEnterBackground) name:UIApplicationDidEnterBackgroundNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didNetStatusChanged) name:kGizReachabilityChangedNotification object:nil];
    }
    return self;
}

- (void)dealloc {
    [self.netReach_atomic stopNotifier];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationDidEnterBackgroundNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:kGizReachabilityChangedNotification object:nil];
    [self endBackgrondTask];
}

/*
 * 获取当前链接的 ssid
 */
- (NSString *)ssid {
    NSArray *interfaces = (__bridge_transfer NSArray *)CNCopySupportedInterfaces();
    for (NSString *interface in interfaces) {
        NSDictionary *networkInfo = (__bridge_transfer NSDictionary *)CNCopyCurrentNetworkInfo((__bridge CFStringRef)interface);
        NSString *ssid = networkInfo[(__bridge_transfer NSString *)kCNNetworkInfoKeySSID];
        if (ssid.length > 0) {
            return ssid;
        }
    }
    return nil;
}

/*
 * 检测网络状态是否改变
 */
- (void)didNetStatusChanged {
    self.netStatusChanged_atomic = YES;
    if (GizReachableViaWiFi == self.netReach_atomic.currentReachabilityStatus) {
        if (self.netReach_atomic.isConnectingWiFi)
            self.netStatus_atomic = GizNetStatusConnecting;
        else
            self.netStatus_atomic = GizNetStatusConnected;
    } else {
        self.netStatus_atomic = GizNetStatusDisconnected;
    }
}

/*
 * 后台模式自动检测状态变化
 */
- (void)didEnterBackground {
    if (![self beginBackgroundTask]) {
        return;
    }
    
    __weak __typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        __strong __typeof(self) strongSelf = weakSelf;
        
        if (nil == strongSelf) {
            return;
        }
        
        // 旧版 iOS 设置超时，防止出现后台时间太短的情况
        if ([[UIApplication sharedApplication] respondsToSelector:@selector(setKeepAliveTimeout:handler:)]) {
            [[UIApplication sharedApplication] setKeepAliveTimeout:600 handler:nil];
        }

        NSTimeInterval min = 3;
        NSTimeInterval max = [UIApplication sharedApplication].backgroundTimeRemaining;
        
        if (max < 20) {
            NSLog(@"The ios system has bug?");
        }
        
        NSString *ssid = [strongSelf ssid];
        
        // 如果已经是 soft ap 模式，不重复检测
        if ((GizNotReachable == strongSelf.netReach_atomic.currentReachabilityStatus || !strongSelf.netReach_atomic.isConnectingWiFi) &&
            [ssid hasPrefix:strongSelf.ssidPrefix_atomic]) {
            if ([strongSelf.delegate_atomic didSoftAPModeDetected:ssid]) {
                [strongSelf endBackgrondTask];
                return;
            }
        }
        
        strongSelf.netStatus_atomic = GizNetStatusDisconnected;
        NSLog(@"background detect softap mode started");
        
        int counter = 0;
        
        // 检测网络切换过程
        while ([UIApplication sharedApplication].backgroundTimeRemaining > min &&
               [UIApplication sharedApplication].backgroundTimeRemaining <= max) {
            NSString *new_ssid = [strongSelf ssid];
            
            //ssid 发生改变，清除计数器的同时，拷贝新的 ssid
            if (![ssid isEqualToString:new_ssid]) {
                counter = 0;
                ssid = new_ssid;
            }
            
            if ([ssid hasPrefix:strongSelf.ssidPrefix_atomic]) {
                /*
                 * 1. 状态 4 次（1 ～ 1.5s）无变化
                 * 2. 状态发生变化且变为已连接状态
                 */
                if (!strongSelf.netStatusChanged_atomic && !strongSelf.netReach_atomic.isConnectingWiFi) {
                    counter ++;
                    if (counter == 4) {
                        if ([strongSelf.delegate_atomic didSoftAPModeDetected:ssid]) {
                            break;
                        }
                    }
//                } else if (GizNetStatusConnecting != strongSelf.netStatus_atomic) {
                } else if (GizNetStatusConnected == strongSelf.netStatus_atomic) {
                    counter = 5;
                    strongSelf.netStatusChanged_atomic = NO;
                    strongSelf.netStatus_atomic = GizNetStatusDisconnected;
                    if ([strongSelf.delegate_atomic didSoftAPModeDetected:ssid]) {
                        break;
                    }
                }
            } else {
                strongSelf.netStatusChanged_atomic = NO;
            }

            usleep(250000);
        }
        
        NSLog(@"background detect softap mode stoped");
        [strongSelf endBackgrondTask];
    });
}

- (BOOL)beginBackgroundTask {
    if (0 != self.taskid_atomic) {
        return NO;
    }
    
    self.taskid_atomic = [[UIApplication sharedApplication] beginBackgroundTaskWithExpirationHandler:nil];
    return 0 != self.taskid_atomic;
}

- (void)endBackgrondTask {
    sleep(1);
    if (0 != self.taskid_atomic) {
        NSInteger taskid = self.taskid_atomic;
        self.taskid_atomic = 0;
        [[UIApplication sharedApplication] endBackgroundTask:taskid];
    }
}

@end
