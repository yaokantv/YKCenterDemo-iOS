//
//  GizWifiSubDevice.h
//  GizWifiSDK
//
//  Created by GeHaitong on 15/7/9.
//  Copyright (c) 2015年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDevice.h>

/*
 GizWifiSubDevice 类为 APP 开发者提供中控子设备的操作函数
 */
NS_CLASS_DEPRECATED_IOS(1_0, 2_0, "GizWifiSubDevice is deprecated.")
@interface GizWifiSubDevice : GizWifiDevice

/*
 NSString类型。子设备标识 DID
 */
@property (strong, nonatomic, readonly) NSString *subDid;

/*
 NSString类型。子设备的产品类型标识码
 */
@property (strong, nonatomic, readonly) NSString *subProductKey;

/*
 NSString类型。子设备的产品类型名称
 */
@property (strong, nonatomic, readonly) NSString *subProductName;

/*
 获取设备状态。已订阅的设备变为可控状态后才能获取到状态
 @see 对应的回调接口：[GizWifiDeviceDelegate device:didReceiveData:data:withSN:]
 */
- (void)getDeviceStatus;

/*
 给设备发送控制指令。已订阅的设备变为可控状态后才能发送控制指令
 @param data 控制指令，格式与[GizWifiDevice write:]相同
 @see 对应的回调接口：[GizWifiDeviceDelegate device:didReceiveData:data:withSN:]
 */
- (void)write:(NSDictionary *)data withSN:(int)sn;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[write:key:withSN:]、[getDeviceStatus]
 */
- (void)write:(NSDictionary *)data DEPRECATED_ATTRIBUTE;

@end
