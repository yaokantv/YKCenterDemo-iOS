//
//  GizDeviceOTA.h
//  GizWifiSDK
//
//  Created by Tom Ge on 2016/10/25.
//  Copyright © 2016年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol GizDeviceOTADelegate <NSObject>
@optional

- (void)didCheckDeviceUpdate:(NSError *)result deviceID:(NSString *)deviceID needUpdate:(BOOL)needUpdate;
- (void)didUpgradeDevice:(NSError *)result deviceID:(NSString *)deviceID;
- (void)didNotifyDeviceUpdate:(NSString *)deviceID;
- (void)didNotifyDeviceUpgradeStatus:(NSString *)deviceID upgradeStatus:(NSError *)upgradeStatus;

@end

@interface GizDeviceOTA : NSObject

+ (void)setDelegate:(id <GizDeviceOTADelegate>)delegate;
+ (void)checkDeviceUpdate:(NSString *)uid token:(NSString *)token deviceID:(NSString *)deviceID;
+ (void)upgradeDevice:(NSString *)uid token:(NSString *)token deviceID:(NSString *)deviceID;

@end
