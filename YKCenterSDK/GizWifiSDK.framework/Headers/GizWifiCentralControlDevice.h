//
//  GizWifiCentralControlDevice.h
//  GizWifiSDK
//
//  Created by Tom on 15/7/9.
//  Copyright (c) 2015年 gizwits. All rights reserved.
//

#import <GizWifiSDK/GizWifiDevice.h>

@class GizWifiCentralControlDevice;

/**
 GizWifiCentralControlDeviceDelegate是GizWifiCentralControlDevice 类的委托协议，为 APP 开发者处理中控子设备的添加、删除、获取提供委托函数
 */
@protocol GizWifiCentralControlDeviceDelegate <GizWifiDeviceDelegate>
@optional

/**
 子设备列表回调接口。添加、删除、同步更新子设备列表以及子设备列表变化上报都使用该回调接口。
 @param device 触发回调的 GizWifiCentralControlDevice对象
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，此时subDeviceList为中控当前的子设备列表；其他为失败，此时subDeviceList 大小为0。
 子设备列表主动上报时该参数为GIZ_SDK_SUCCESS，子设备添加、删除、同步更新时该参数是GIZ_SDK_SUCCESS或其他错误码
 @param subDeviceList 子设备列表。GizWifiDevice 对象数组
 @see 触发函数：[GizWifiCentralControlDevice getSubDevices], [GizWifiCentralControlDevice addSubDevice:],[GizWifiCentralControlDevice deleteSubDevice:]
 */
- (void)didUpdateSubDevices:(GizWifiCentralControlDevice * _Nonnull)device result:(NSError * _Nonnull)result subDeviceList:(NSArray <GizWifiDevice *>* _Nullable)subDeviceList;

/** @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiCentralControlDeviceDelegate didUpdateSubDevices:result:subDeviceList:] */
- (void)device:(GizWifiCentralControlDevice * _Null_unspecified)device didDiscovered:(NSError * _Null_unspecified)result subDeviceList:(NSArray * _Null_unspecified)subDeviceList DEPRECATED_MSG_ATTRIBUTE("Please use didUpdateSubDevices:result:subDeviceList: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiCentralControlDeviceDelegate didUpdateSubDevices:result:subDeviceList:] */
- (void)XPGWifiCentralControlDevice:(GizWifiCentralControlDevice * _Null_unspecified)wifiCentralControlDevice didDiscovered:(NSArray * _Null_unspecified)subDeviceList result:(int)result DEPRECATED_MSG_ATTRIBUTE("Please use didUpdateSubDevices:result:subDeviceList: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");

@end

/**
 GizWifiCentralControlDevice 类为 APP 开发者提供中控设备的操作函数，如添加子设备、删除子设备、获取子设备列表
 */
@interface GizWifiCentralControlDevice : GizWifiDevice

/**
 使用委托获取对应事件。GizWifiCentralControlDevice 对应的回调接口在 GizWifiCentralControlDeviceDelegate 定义，需要用到哪个接口，实现对应的回调即可
 */
@property (weak, nonatomic) id <GizWifiCentralControlDeviceDelegate> _Nullable delegate;

/**
 NSArray类型，GizWifiDevice对象数组，只读。中控子设备列表
 */
@property (strong, nonatomic, readonly) NSArray <GizWifiDevice *>* _Nullable subDeviceList;

/**
 同步更新子设备列表。只有中控设备可控后才能调用该接口。该接口会向中控设备发送获取子设备列表请求，中控设备将子设备列表通过回调返回
 @see 对应的回调接口：[GizWifiCentralControlDeviceDelegate GizWifiCentralControlDevice:didDiscovered:subDeviceList:]
 */
- (void)updateSubDevices;

/**
 添加子设备，只有中控设备可控后才能执行添加操作。该接口会向中控设备发送添加子设备请求，中控设备将添加后的子设备列表通过回调返回
 @see 对应的回调接口：[GizWifiCentralControlDeviceDelegate GizWifiCentralControlDevice:didDiscovered:subDeviceList:]
 */
- (void)addSubDevice:(NSArray <NSString *>* _Nullable)deviceMacs; //deviceMacs可不填

/**
 删除子设备。子设备被删除后就不会出现在中控的组网设备中了。只有中控设备可控后才能执行此操作。该接口会向中控设备发送删除子设备请求，中控设备将删除后的子设备列表通过回调返回
 @param deviceList 待删除的子设备对象数组。此参数不能为nil或空数组
 @see 回调 [GizWifiCentralControlDeviceDelegate didUpdateSubDevices:result:subDeviceList:]
 */
- (void)deleteSubDevices:(NSArray * _Nonnull)deviceList;

/** @deprecated 此接口已废弃，不再提供支持。 */
- (void)getSubDevices DEPRECATED_MSG_ATTRIBUTE("No longer supported.") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持。替代接口：[GizWifiCentralControlDevice addSubDevice:] */
- (void)addSubDevice DEPRECATED_MSG_ATTRIBUTE("Please use addSubDevice: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");

- (void)deleteSubDevice:(GizWifiDevice * _Nonnull)device DEPRECATED_MSG_ATTRIBUTE("Please use deleteSubDevices: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");

@end
