//
//  GizWifiCentralControlDevice.h
//  GizWifiSDK
//
//  Created by GeHaitong on 15/7/9.
//  Copyright (c) 2015年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDevice.h>

@class GizWifiCentralControlDevice;

/*
 GizWifiCentralControlDeviceDelegate是GizWifiCentralControlDevice 类的委托协议，为 APP 开发者处理中控子设备的添加、删除、获取提供委托函数
 */
@protocol GizWifiCentralControlDeviceDelegate <GizWifiDeviceDelegate>
@optional

/*
 子设备列表回调接口。添加、删除、同步更新子设备列表以及子设备列表变化上报都使用该回调接口。
 @param device 触发回调的 GizWifiCentralControlDevice对象
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，此时subDeviceList为中控当前的子设备列表；其他为失败，此时subDeviceList 大小为0。
 子设备列表主动上报时该参数为GIZ_SDK_SUCCESS，子设备添加、删除、同步更新时该参数是GIZ_SDK_SUCCESS或其他错误码
 @param subDeviceList 子设备列表。GizWifiDevice 对象数组
 @see 触发函数：[GizWifiCentralControlDevice getSubDevices], [GizWifiCentralControlDevice addSubDevice],[GizWifiCentralControlDevice deleteSubDevice]
 */
- (void)didUpdateSubDevices:(GizWifiCentralControlDevice *)device result:(NSError *)result subDeviceList:(NSArray *)subDeviceList;

- (void)device:(GizWifiCentralControlDevice *)device didDiscovered:(NSError *)result subDeviceList:(NSArray *)subDeviceList DEPRECATED_ATTRIBUTE;

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
 NSArray类型，GizWifiDevice对象数组，只读。中控子设备列表
 */
@property (strong, nonatomic, readonly) NSArray *subDeviceList;

/*
 同步更新子设备列表。只有中控设备可控后才能调用该接口。该接口会向中控设备发送获取子设备列表请求，中控设备将子设备列表通过回调返回
 @see 对应的回调接口：[GizWifiCentralControlDeviceDelegate GizWifiCentralControlDevice:didDiscovered:subDeviceList:]
 */
- (void)updateSubDevices;
- (void)getSubDevices DEPRECATED_ATTRIBUTE;

/*
 添加子设备，只有中控设备可控后才能执行添加操作。该接口会向中控设备发送添加子设备请求，中控设备将添加后的子设备列表通过回调返回
 @see 对应的回调接口：[GizWifiCentralControlDeviceDelegate GizWifiCentralControlDevice:didDiscovered:subDeviceList:]
 */
- (void)addSubDevice;

- (void)addSubDevice:(NSArray *)deviceMacs; //deviceMacs可不填

/*
 删除子设备，只有中控设备可控后才能执行删除操作。该接口会向中控设备发送删除子设备请求，中控设备将删除后的子设备列表通过回调返回
 @param device 待删除子设备，必须是这台中控网关对应的子设备
 @see 对应的回调接口：[GizWifiCentralControlDeviceDelegate GizWifiCentralControlDevice:didDiscovered:subDeviceList:]
 */
- (void)deleteSubDevice:(GizWifiDevice *)device;

@end
