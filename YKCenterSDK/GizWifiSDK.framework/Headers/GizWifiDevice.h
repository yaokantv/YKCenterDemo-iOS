//
//  GizWifiDevice.h
//  GizWifiSDK
//
//  Created by Tom on 15/7/9.
//  Copyright (c) 2015年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDefinitions.h>

extern NSString * _Null_unspecified XPGWifiDeviceHardwareWifiHardVerKey DEPRECATED_MSG_ATTRIBUTE("No longer supported.") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
extern NSString * _Null_unspecified XPGWifiDeviceHardwareWifiSoftVerKey DEPRECATED_MSG_ATTRIBUTE("No longer supported.") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
extern NSString * _Null_unspecified XPGWifiDeviceHardwareMCUHardVerKey DEPRECATED_MSG_ATTRIBUTE("No longer supported.") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
extern NSString * _Null_unspecified XPGWifiDeviceHardwareMCUSoftVerKey DEPRECATED_MSG_ATTRIBUTE("No longer supported.") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
extern NSString * _Null_unspecified XPGWifiDeviceHardwareFirmwareIdKey DEPRECATED_MSG_ATTRIBUTE("No longer supported.") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
extern NSString * _Null_unspecified XPGWifiDeviceHardwareFirmwareVerKey DEPRECATED_MSG_ATTRIBUTE("No longer supported.") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
extern NSString * _Null_unspecified XPGWifiDeviceHardwareProductKey DEPRECATED_MSG_ATTRIBUTE("No longer supported.") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");

@class GizWifiDevice;
@class GizWifiCentralControlDevice;

/**
 GizWifiDeviceDelegate 是 GizWifiDevice 类的委托协议，为 APP 开发者处理设备登录、设备控制、设备在线状态提供委托函数
 */
@protocol GizWifiDeviceDelegate <NSObject>
@optional

/**
 设备订阅或解除订阅的回调
 @param device 回调的 GizWifiDevice 对象
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，设备的订阅状态无变化
 @param isSubscribed 设备是被订阅了还是被取消订阅了。YES表示被订阅，NO表示被解除订阅
 @see 触发函数：[GizWifiDevice write:withSN:]
 @see GizWifiErrorCode
 */
- (void)device:(GizWifiDevice * _Nonnull)device didSetSubscribe:(NSError * _Nonnull)result isSubscribed:(BOOL)isSubscribed;

/**
 接收到设备状态上报的回调
 @param device 回复状态的设备对象
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，dataMap为空字典
 @param attrStatus 设备上报的状态，字典格式：
 {
 "data": [value],  // value 为 NSDictionary 类型，内容为设备状态键值对，[数据点标识名：数据点值]，数据点值的类型与 site 上的定义一致
 "alerts": [value],  // value 为 NSDictionary 类型，内容为设备报警键值对，[数据点标识名：数据点值]，数据点值的类型与 site 上的定义一致
 "faults": [value],  // value 为 NSDictionary 类型，内容为设备故障键值对，[数据点标识名：数据点值]，数据点值的类型与 site 上的定义一致
 "binary": [value],  // value 为 NSData 类型，内容为二进制数据，专指没有在 site 上定义数据点的需要透传的数据
 }
 @param adapterAttrStatus 设备上报的适配状态，字典格式同attrStatus
 @param sn 控制指令的应答序号，此应答序号与 APP 发送控制指令的序号一致。设备主动上报数据和回复状态查询时，序号为0
 @note 设备回复或上报的数据中，当 SDK 遇到无法解析的数据时，会作为透传数据处理，此时错误码为 GIZ_SDK_SUCCESS
 @see 触发函数：[GizWifiDevice write:withSN:]、[GizWifiDevice getDeviceStatus]
 @see GizWifiErrorCode
 **/
- (void)device:(GizWifiDevice * _Nonnull)device didReceiveAttrStatus:(NSError * _Nonnull)result attrStatus:(NSDictionary * _Nullable)attrStatus adapterAttrStatus:(NSDictionary * _Nullable)adapterAttrStatus withSN:(NSNumber * _Nullable)sn;

/**
 设置设备绑定信息的回调
 @param device 修改备注和别名的设备对象
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败
 @see 触发函数：[GizWifiDevice setCustomInfo:]
 @see GizWifiErrorCode
 */
- (void)device:(GizWifiDevice * _Nonnull)device didSetCustomInfo:(NSError * _Nonnull)result;

/**
 设备硬件信息的回调
 @param device 返回硬件信息的设备对象
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，hardwareInfo为nil
 @param hardwareInfo 硬件信息。对应的硬件信息键值对有：
 
     {
         "wifiHardVersion": [value],    // value 为 NSString 类型，设备的 Wifi 模组硬件版本号
         "wifiSoftVersion": [value],    // value 为 NSString 类型，设备的 Wifi 模组软件版本号
         "wifiFirmwareId": [value],     // value 为 NSString 类型，设备的 Wifi 固件 ID
         "wifiFirmwareVer": [value],    // value 为 NSString 类型，设备的 Wifi 固件版本
         "mcuHardVersion": [value],     // value 为 NSString 类型，设备的硬件版本号
         "mcuSoftVersion": [value],     // value 为 NSString 类型，设备的软件版本号
         "productKey": [value],         // value 为 NSString 类型，设备的产品唯一标识码
     }

 @see 触发函数：[GizWifiDevice getHardwareInfo]
 */
- (void)device:(GizWifiDevice * _Nonnull)device didGetHardwareInfo:(NSError * _Nonnull)result hardwareInfo:(NSDictionary <NSString *, NSString *>* _Nullable)hardwareInfo;

/**
 设备网络状态变化通知
 @param device 回调的 GizWifiDevice 对象
 @param netStatus 设备是离线、在线还是可控状态
 @note 该回调主动上报设备的网络状态变化，当设备重上电、断电或可控时会触发该回调
 @see GizWifiDeviceNetStatus
 */
- (void)device:(GizWifiDevice * _Nonnull)device didUpdateNetStatus:(GizWifiDeviceNetStatus)netStatus;

/**
 设备退出产测的回调
 @param device 触发回调的设备实例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败
 @see 触发函数：[GizWifiDevice exitProductionTesting]
 */
- (void)device:(GizWifiDevice * _Nonnull)device didExitProductionTesting:(NSError * _Nonnull)result;

/** @deprecated 此接口已废弃，不再提供支持。替代接口：[GizWifiDeviceDelegate device: didReceiveAttrStatus:attrStatus:adapterAttrStatus:withSN:] */
- (void)device:(GizWifiDevice * _Nonnull)device didReceiveData:(NSError * _Nonnull)result data:(NSDictionary <NSString *, id>* _Nullable)dataMap withSN:(NSNumber * _Nullable)sn DEPRECATED_MSG_ATTRIBUTE("Please use device:didReceiveAttrStatus:attrStatus:adapterAttrStatus:withSN: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持。替代接口：[GizWifiDeviceDelegate device:didReceiveAttrStatus:attrStatus:adapterAttrStatus:withSN:] */
- (void)XPGWifiDevice:(GizWifiDevice * _Null_unspecified)device didReceiveData:(NSDictionary * _Null_unspecified)data result:(int)result DEPRECATED_MSG_ATTRIBUTE("Please use device:didReceiveAttrStatus:attrStatus:adapterAttrStatus:withSN: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiDeviceDelegate device:didGetHardwareInfo:hardwareInfo:] */
- (void)XPGWifiDevice:(GizWifiDevice * _Null_unspecified)device didQueryHardwareInfo:(NSDictionary * _Null_unspecified)hwInfo DEPRECATED_MSG_ATTRIBUTE("Please use device:didGetHardwareInfo:hardwareInfo: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持，请使用替代接口：[GizWifiDeviceDelegate device:didUpdateNetStatus:] */
- (void)XPGWifiDeviceDidDisconnected:(GizWifiDevice * _Null_unspecified)device result:(int)result DEPRECATED_MSG_ATTRIBUTE("Please use device:didUpdateNetStatus: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持，请使用替代接口：[GizWifiDeviceDelegate device:didUpdateNetStatus:] */
- (void)XPGWifiDevice:(GizWifiDevice * _Null_unspecified)device didLogin:(int)result DEPRECATED_MSG_ATTRIBUTE("Please use device:didUpdateNetStatus: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持，请使用替代接口：[GizWifiDeviceDelegate device:didUpdateNetStatus:] */
- (void)XPGWifiDevice:(GizWifiDevice * _Null_unspecified)device didDeviceIsOnline:(BOOL)isOnline DEPRECATED_MSG_ATTRIBUTE("Please use device:didUpdateNetStatus: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");

@end

/**
 GizWifiDevice 类为 APP 开发者提供设备订阅、设备数据通知、设备状态通知等功能
 */
@interface GizWifiDevice : NSObject

- (instancetype _Nullable)init NS_UNAVAILABLE;

/**
 使用委托获取对应事件。GizWifiDevice 对应的回调接口在 GizWifiDeviceDelegate 定义。需要用到哪个接口，回调即可
 */
@property (weak, nonatomic) id <GizWifiDeviceDelegate> _Nullable delegate;
/**
 NSString类型。设备的物理地址，如果是 VIRTUAL:SITE，则是虚拟设备
 */
@property (strong, nonatomic, readonly) NSString * _Nonnull macAddress;
/**
 NSString类型。设备云端身份标识 DID
 */
@property (strong, nonatomic, readonly) NSString * _Nonnull did;
/**
 NSString类型。设备的ip 地址，大循环设备的ip地址为云端服务器域名
 */
@property (strong, nonatomic, readonly) NSString * _Nonnull ipAddress;
/**
 NSString类型。设备的产品类型识别码
 */
@property (strong, nonatomic, readonly) NSString * _Nonnull productKey;
/**
 NSString类型。设备的产品名称
 */
@property (strong, nonatomic, readonly) NSString * _Nonnull productName;
/**
 NSString类型。设备的备注信息，设备绑定后可以修改，默认为空
 */
@property (strong, nonatomic, readonly) NSString * _Nonnull remark;
/**
 NSString类型。设备的别名，设备绑定后可以修改，默认为空
 */
@property (strong, nonatomic, readonly) NSString * _Nonnull alias;
/**
 GizDeviceSharingUserRole类型。表示绑定设备的用户具有的权限
 */
@property (assign, nonatomic, readonly) GizDeviceSharingUserRole sharingRole;
/**
 BOOL类型。设备是否为小循环
 */
@property (assign, nonatomic, readonly) BOOL isLAN;
/**
 BOOL类型。设备是否已绑定
 */
@property (assign, nonatomic, readonly) BOOL isBind;
/**
 BOOL类型。判断设备是否已在云端注销
 */
@property (assign, nonatomic, readonly) BOOL isDisabled;
/**
 GizWifiDeviceType类型。设备分类，是中控设备还是普通设备
 */
@property (assign, nonatomic, readonly) GizWifiDeviceType productType;
/**
 GizWifiDeviceNetStatus类型。设备的网络状态
 */
@property (assign, nonatomic, readonly) GizWifiDeviceNetStatus netStatus;
/**
 BOOL类型。设备是否已订阅
 */
@property (assign, nonatomic, readonly) BOOL isSubscribed;
/**
 BOOL类型。设备是否定义了产品数据点
 */
@property (assign, nonatomic, readonly) BOOL isProductDefined;
/**
 NSDictionary类型。缓存最新的设备状态
 */
@property (strong, nonatomic, readonly) NSDictionary <NSString *, id>* _Nullable attrStatus;
@property (strong, nonatomic, readonly) NSString * _Nullable deviceModuleFirmwareVer;
@property (strong, nonatomic, readonly) NSString * _Nullable deviceMcuFirmwareVer;
@property (strong, nonatomic, readonly) NSString * _Nullable productUI;
@property (strong, nonatomic, readonly) NSString * _Nullable productAdapterUI;
@property (weak, nonatomic, readonly) GizWifiDevice * _Nullable rootDevice;
/**
 GizWifiDeviceNetType类型。设备网络类型
 */
@property (assign, nonatomic, readonly) GizWifiDeviceNetType netType;

/**
 设备订阅或解除订阅。订阅了设备，表示使用者关心这个设备的消息推送。解除订阅，表示使用者不关心这个设备的消息推送。订阅设备后，SDK将自动登录和自动绑定设备。解除订阅后，设备连接将自动断开，但不会自动解绑。一般来说，设备订阅都会成功的，SDK会记住设备是否被订阅了
 
 @param subscribed 订阅或解除订阅。YES表示订阅，NO表示解除订阅
 
 @see 对应回调接口：[GizWifiDeviceDelegate device:didSetSubscribe:]
 */
- (void)setSubscribe:(NSString * _Nullable)productSecret subscribed:(BOOL)subscribed;

/**
 获取硬件信息
 @see 对应的回调接口：[GizWifiDeviceDelegate device:didGetHardwareInfo:]
 */
- (void)getHardwareInfo;

/**
 获取设备状态。已订阅的设备变为可控状态后才能获取到状态。如果设备是变长数据点类型，则可查询指定的数据点状态
 @param attrs 要查询状态的数据点名称，为NSString类型数组。此参数默认值为nil。SDK默认返回设备的所有数据点状态。
    若要查询某些数据点的状态，参数应指定为要查询的数据点数组
 @see 对应的回调接口：[GizWifiDeviceDelegate device: didReceiveAttrStatus:attrStatus:adapterAttrStatus:withSN:]
 */
- (void)getDeviceStatus:(NSArray <NSString *>* _Nullable)attrs;

/**
 退出产测模式。不订阅设备就可以调用此接口，设备进入产测模式后会响应
 @see 对应的回调接口：[GizWifiDeviceDelegate device:didExitProductionTesting:]
 */
- (void)exitProductionTesting;

/**
 给设备发送控制指令。已订阅的设备变为可控状态后才能发送控制指令
 @param data 该参数为要发给设备的操作指令。为字典格式，字典键值对可按以下方式填充：
 如果设备有数据点定义，操作指令一次可以下发多个数据点。字典中的key为数据点名称，value为数据点的值。value类型要与数据点定义一致：
 （1）如果数据点为布尔类型，则value为NSNumber类型；
 （2）如果数据点为数值类型，则value为NSNumber类型；
 （3）如果数据点为枚举类型，则value为枚举序号（NSNumber类型）或者枚举字符串（NSString类型）；
 （4）如果数据点为扩展类型，则value为NSData类型；
 如果设备操作采用透传方式，透传指令一次只能下发一条。透传数据的key为”binary”，value为NSData类型
 @param sn 控制指令序号，用于对应控制指令应答数据。控制确认回调时会返回这个sn
 @note 主动上报的sn为0。如果要准确判断sn，这里的sn不要设置为0
 @see 对应的回调接口：[GizWifiDeviceDelegate device: didReceiveAttrStatus:attrStatus:adapterAttrStatus:withSN:]
 */
- (void)write:(NSDictionary <NSString *, id>* _Nonnull)data withSN:(int)sn;

/**
 修改设备的备注和别名。设备绑定后才能修改
 @param remark 待修改的备注信息。传 null表示不修改，传@""则会覆盖为空串
 @param alias 待修改的设备别名。传 null表示不修改，传@""则会覆盖为空串
 @see 对应的回调接口：[GizWifiDeviceDelegate device:didSetCustomInfo:]
 */
- (void)setCustomInfo:(NSString * _Nullable)remark alias:(NSString * _Nullable)alias;

/** @deprecated 此变量已废弃，不再提供支持。 */
@property (strong, nonatomic, readonly) NSString * _Null_unspecified passcode DEPRECATED_MSG_ATTRIBUTE("No longer supported.") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此变量已废弃，不再提供支持。替代变量为 productType */
@property (assign, nonatomic, readonly) XPGWifiDeviceType type DEPRECATED_MSG_ATTRIBUTE("Please use productType instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此变量已废弃，不再提供支持。替代变量为 netStatus */
@property (assign, nonatomic, readonly) BOOL isOnline DEPRECATED_MSG_ATTRIBUTE("Please use netStatus instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此变量已废弃，不再提供支持。替代变量为 netStatus */
@property (assign, nonatomic, readonly) BOOL isConnected DEPRECATED_MSG_ATTRIBUTE("Please use netStatus instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持。替代变量为 isBind */
- (BOOL)isBind:(NSString * _Null_unspecified)uid DEPRECATED_MSG_ATTRIBUTE("Please use isBind instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持。替代接口：[GizWifiDevice setSubscribe:subscribed:] */
- (void)setSubscribe:(BOOL)subscribed DEPRECATED_MSG_ATTRIBUTE("Please use setSubscribe:subscribed: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持。替代接口：[GizWifiDevice getDeviceStatus:] */
- (void)getDeviceStatus DEPRECATED_MSG_ATTRIBUTE("Please use getDeviceStatus: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持。替代接口：[GizWifiDevice setSubscribe:] */
- (void)disconnect DEPRECATED_MSG_ATTRIBUTE("Please use setSubscribe: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持。替代接口：[GizWifiDevice setSubscribe:] */
- (void)login:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token DEPRECATED_MSG_ATTRIBUTE("Please use setSubscribe: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持。替代接口：[GizWifiDevice write:key:withSN:] */
- (void)write:(NSDictionary * _Null_unspecified)data DEPRECATED_MSG_ATTRIBUTE("Please use write:withSN: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");

@end
