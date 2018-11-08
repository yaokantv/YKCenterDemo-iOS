//
//  YKSoftAPDetection.h
//  DeviceConfigDemo
//
//  Created by Don on 2017/1/16.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol YKSoftAPDetectionDelegate <NSObject>
@required

- (BOOL)didSoftAPModeDetected:(NSString *)ssid;

@end

@interface YKSoftAPDetection : NSObject

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithSoftAPSSID:(NSString *)ssidPrefix delegate:(id <YKSoftAPDetectionDelegate>)delegate;

@end
