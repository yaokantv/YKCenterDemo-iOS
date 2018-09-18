//
//  GizDeviceOTA.h
//  GizWifiSDK
//
//  Created by Tom Ge on 2016/10/25.
//  Copyright © 2016年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDefinitions.h>

@class GizWifiDevice;

@protocol GizDeviceOTADelegate <NSObject>
@optional

/**
 检查设备更新回调
 @param result 接口执行结果，见GizWifiErrorCode定义。GIZ_SDK_SUCCESS表示成功，其他为失败。失败时参数wifiVersion和mcuVersion值为nil
 @param device 触发回调的设备
 @param wifiVersion 模组固件版本，字典格式：{"latest":"xxx", "current":"xxx"}。若此参数为nil，表示没有检查到模组固件更新信息
 @param mcuVersion mcu固件版本，字典格式：{"latest":"xxx", "current":"xxx"}。若此参数为nil，表示没有检查到mcu固件更新信息
 @see 接口 [GizDeviceOTA checkDeviceUpdate:token:device:firmwareType:]
 */
 - (void)didCheckDeviceUpdate:(GizWifiDevice * _Nullable)device result:(NSError * _Nonnull)result wifiVersion:(NSDictionary <NSString *, NSString *>* _Nullable)wifiVersion mcuVersion:(NSDictionary <NSString *, NSString *>* _Nullable)mcuVersion;

/**
 设备是否开始升级的回调
 @param result 接口执行结果，见GizWifiErrorCode定义。GIZ_SDK_SUCCESS表示开始升级，其他为失败
 @param device 触发回调的设备
 @see 接口 [GizDeviceOTA upgradeDevice:token:device:]
 */
 - (void)didUpgradeDevice:(GizWifiDevice * _Nullable)device result:(NSError * _Nonnull)result firmwareType:(GizOTAFirmwareType)firmwareType;

/**
 设备固件有更新通知
 @param device 固件有更新的设备
 @param wifiVersion 模组固件版本，字典格式：{"latest":"xxx", "current":"xxx"}。若此参数为nil，表示没有检查到模组固件更新信息
 @param mcuVersion mcu固件版本，字典格式：{"latest":"xxx", "current":"xxx"}。若此参数为nil，表示没有检查到mcu固件更新信息
 */
 - (void)didNotifyDeviceUpdate:(GizWifiDevice * _Nullable)device  wifiVersion:(NSDictionary <NSString *, NSString *>* _Nullable)wifiVersion mcuVersion:(NSDictionary <NSString *, NSString *>* _Nullable)mcuVersion;

/**
 设备升级状态通知。在设备升级过程中会主动上报当前状态
 @param device 触发回调的设备
 @param upgradeStatus 设备升级状态，见GizWifiErrorCode定义中枚举值范围[8350, 8358]
 */
 - (void)didNotifyDeviceUpgradeStatus:(GizWifiDevice * _Nullable)device firmwareType:(GizOTAFirmwareType)firmwareType upgradeStatus:(NSError * _Nonnull)upgradeStatus;

@end

@interface GizDeviceOTA : NSObject

/**
 GizDeviceOTADelegate委托对象
 */
@property (class, weak, nonatomic) id <GizDeviceOTADelegate> _Nullable delegate;

/**
 检查设备更新。
 @param uid 用户ID
 @param token 用户token
 @param device 待检查的设备
 @see 回调 [GizDeviceOTADelegate didCheckDeviceUpdate:device:needUpdate:latestWifiVersion:latestDeviceVersion:]
 */
+ (void)checkDeviceUpdate:(NSString * _Nonnull)uid token:( NSString * _Nonnull)token device:(GizWifiDevice * _Nonnull)device;

/**
 升级设备固件
 @param uid 用户ID
 @param token 用户token
 @param device 要升级的设备
 @see 回调 [GizDeviceOTADelegate didUpgradeDevice:device:]
 */
+ (void)upgradeDevice:(NSString * _Nonnull)uid token:(NSString * _Nonnull)token device:(GizWifiDevice * _Nonnull)device firmwareType:(GizOTAFirmwareType)firmwareType;

@end
