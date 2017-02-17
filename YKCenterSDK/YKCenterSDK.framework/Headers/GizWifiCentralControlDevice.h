//
//  GizWifiCentralControlDevice.h
//  GizWifiSDK
//
//  Created by GeHaitong on 15/7/9.
//  Copyright (c) 2015年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GizWifiDevice.h"

@class GizWifiCentralControlDevice;

/*
 GizWifiCentralControlDeviceDelegate是GizWifiCentralControlDevice 类的委托协议，为 APP 开发者处理中控子设备的添加、删除、获取提供委托函数
 */
@protocol GizWifiCentralControlDeviceDelegate <GizWifiDeviceDelegate>
@optional

/*
 中控子设备发现
 @param device 触发回调的 GizWifiCentralControlDevice对象
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，subDeviceList 大小为0
 @param subDeviceList 子设备列表。GizWifiSubDevice 对象数组
 @see 触发函数：[GizWifiCentralControlDevice getSubDevices], [GizWifiCentralControlDevice addSubDevice],[GizWifiCentralControlDevice deleteSubDevice]
 */
- (void)device:(GizWifiCentralControlDevice *)device didDiscovered:(NSError *)result subDeviceList:(NSArray *)subDeviceList;

/*
 @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiCentralControlDeviceDelegate device:didDiscovered:subDeviceList:]
 */
- (void)XPGWifiCentralControlDevice:(GizWifiCentralControlDevice *)wifiCentralControlDevice didDiscovered:(NSArray *)subDeviceList result:(int)result DEPRECATED_ATTRIBUTE;

@end

/*
 GizWifiCentralControlDevice 类为 APP 开发者提供中控设备的操作函数，如添加子设备、删除子设备、获取子设备列表
 */
@interface GizWifiCentralControlDevice : GizWifiDevice

/*
 使用委托获取对应事件。GizWifiCentralControlDevice 对应的回调接口在 GizWifiCentralControlDeviceDelegate 定义，需要用到哪个接口，实现对应的回调即可
 */
@property (weak, nonatomic) id <GizWifiCentralControlDeviceDelegate>delegate;

/*
 NSArray类型，GizWifiSubDevice对象数组
 */
@property (strong, nonatomic, readonly) NSArray *subDeviceList;

/*
 获取子设备列表，只有中控设备可控后才能获取到。该接口会向中控设备发送获取子设备列表请求，中控设备将子设备列表通过回调返回
 @see 对应的回调接口：[GizWifiCentralControlDeviceDelegate GizWifiCentralControlDevice:didDiscovered:subDeviceList:]
 */
- (void)getSubDevices;

/*
 添加子设备，只有中控设备可控后才能执行添加操作。该接口会向中控设备发送添加子设备请求，中控设备将添加后的子设备列表通过回调返回
 @see 对应的回调接口：[GizWifiCentralControlDeviceDelegate GizWifiCentralControlDevice:didDiscovered:subDeviceList:]
 */
- (void)addSubDevice;

/*
 删除子设备，只有中控设备可控后才能执行删除操作。该接口会向中控设备发送删除子设备请求，中控设备将删除后的子设备列表通过回调返回
 @param subDid 为待删除的子设备id
 @see 对应的回调接口：[GizWifiCentralControlDeviceDelegate GizWifiCentralControlDevice:didDiscovered:subDeviceList:]
 */
- (void)deleteSubDevice:(NSString *)subDid;

@end
