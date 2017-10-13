//
//  YKCenterCommon.h
//  YKCenterDemo
//
//  Created by Don on 2017/1/16.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SystemConfiguration/CaptiveNetwork.h>
@class GizWifiDevice;

/**
 登录类型类型
 */
typedef NS_ENUM(NSInteger, YKLoginStatus) {
    /**
     未登录
     */
    YKLoginNone = 0,
    
    /**
     用户登录
     */
    YKLoginUser = 1,
    
    /**
     匿名登录
     */
    YKLoginAnonymous = 2,
    
    /**
     尝试匿名登录中
     */
    YKLoginAnonymousProcess = 3,
    
    /**
     匿名登录中断
     */
    YKLoginAnonymousCancel = 4,
};

static inline NSString *YKGetCurrentSSID() {
    NSArray *interfaces = (__bridge_transfer NSArray *)CNCopySupportedInterfaces();
    for (NSString *interface in interfaces) {
        NSDictionary *ssidInfo = (__bridge_transfer NSDictionary *)CNCopyCurrentNetworkInfo((__bridge CFStringRef)interface);
        NSString *ssid = ssidInfo[(__bridge_transfer NSString *)kCNNetworkInfoKeySSID];
        if (ssid.length > 0) {
            return ssid;
        }
    }
    return @"";
}

static inline void SHOW_ALERT_CANCEL(NSString *message, id delegate) {
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil)
                                                        message:message
                                                       delegate:delegate
                                              cancelButtonTitle:NSLocalizedString(@"NO", nil)
                                              otherButtonTitles:NSLocalizedString(@"OK", nil), nil];
    [alertView show];
}

id YKGetControllerWithClass(Class class, UITableView *tableView, NSString *reuseIndentifer);

@interface YKCenterCommon : NSObject

@property (nonatomic, copy) NSString *ssid;
@property (nonatomic, copy) NSString *currentYKCId;
@property (nonatomic, strong) GizWifiDevice *currentDevice;
@property (nonatomic, assign) YKLoginStatus loginStatus;
@property (nonatomic, copy) NSString *uid;
@property (nonatomic, copy) NSString *token;

+ (instancetype)sharedInstance;

- (id)init NS_UNAVAILABLE;

/*
 * ssid 缓存
 */
- (void)saveSSID:(NSString *)ssid key:(NSString *)key;
- (NSString *)getPasswrodFromSSID:(NSString *)ssid;
- (void)saveUserDefaults:(NSString *)username password:(NSString *)password uid:(NSString *)uid token:(NSString *)token;
- (void)removeUserDefaults;
+ (BOOL)isMobileNumber:(NSString *)mobileNum;

@end
