//
//  GizWifiSDK.h
//  GizWifiSDK
//
//  Created by GeHaitong on 15/7/9.
//  Copyright (c) 2015年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDefinitions.h>
#import <GizWifiSDK/GizWifiCentralControlDevice.h>
#import <GizWifiSDK/GizWifiSSID.h>
#import <GizWifiSDK/GizWifiBinary.h>
#import <GizWifiSDK/GizDeviceOTA.h>
#import <GizWifiSDK/GizDeviceSharing.h>
#import <GizWifiSDK/GizDeviceSchedulerCenter.h>
#import <GizWifiSDK/GizDeviceGroupCenter.h>
#import <GizWifiSDK/GizDeviceSceneCenter.h>
#import <GizWifiSDK/GizDeviceJointActionCenter.h>
#import <GizWifiSDK/GizUserInfo.h>

#import <GizWifiSDK/GizWifiSubDevice.h>
#import <GizWifiSDK/GizWifiGroup.h>

@class GizWifiSDK;

/*
 GizWifiSDKDelegate 是 GizWifiSDK 类的委托协议，为APP开发者处理设备配置和发现、设备分组、用户登录和注册提供委托函数。
 */
@protocol GizWifiSDKDelegate <NSObject>
@optional

/*
 设备配置结果的回调接口
 @param wifiSDK 为回调的 GizWifiSDK 单例
 @param result 配置成功或失败。如果配置失败，其他参数为nil
 @param mac 设备 mac 地址
 @param did 设备 did。配置成功时，did的值取决于设备是否有上报
 @param productKey 设备的产品类型标识
 @note 注意：如果调用getBoundDevices接口时指定了待筛选的 productKey 集合，如果设备被成功配置到路由上了，会返回配置成功，但不会出现在设备列表中
 @see 触发函数：[GizWifiSDK setDeviceOnboarding:key:configMode:softAPSSIDPrefix:timeout:wifiGAgentType:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didSetDeviceOnboarding:(NSError * _Nonnull)result mac:(NSString * _Nullable)mac did:(NSString * _Nullable)did productKey:(NSString * _Nullable)productKey;

/** 设备配网回调接口 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didSetDeviceOnboarding:(NSError * _Nonnull)result device:(GizWifiDevice * _Nullable)device;

/*
 @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiSDKDelegate wifiSDK:didSetDeviceOnboarding:device:]
 */
- (void)XPGWifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didSetDeviceWifi:(GizWifiDevice * _Null_unspecified)device result:(int)result DEPRECATED_ATTRIBUTE;

/*
 获取设备周围Wi-Fi热点列表的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，ssidList为 nil
 @param ssidList 为若干 GizWifiSSID 实例组成的 SSID 信号列表
 @see 触发函数：[GizWifiSDK getSSIDList]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didGetSSIDList:(NSError * _Nonnull)result ssidList:(NSArray <GizWifiSSID *>* _Nullable)ssidList;

/*
 @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiSDKDelegate wifiSDK:didGetSSIDList:ssidList:]
 */
- (void)XPGWifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didGetSSIDList:(NSArray * _Null_unspecified)ssidList result:(int)result DEPRECATED_ATTRIBUTE;

/*
 设备列表上报的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义，result.code 为 GIZ_SDK_SUCCESS 表示成功。result.code 为失败的错误码时，deviceList 为非 nil 集合
 @param deviceList GizWifiDevice 实例组成的数组，该参数将只返回根据指定productKey筛选过的设备集合。productKey在 getBoundDevices接口调用时指定
 @note 该回调接口，在不调用getBoundDevices时也可能会由SDK主动触发，主动触发是由于SDK发现设备列表发生了变化，此时错误码GIZ_SDK_SUCCESS；
 getBoundDevices接口调用时会触发该回调，错误码代表云端请求状态，设备列表是绑定设备与局域网设备合并之后的集合；
 @see 触发函数：[GizWifiSDK getBoundDevices:token:specialProductKeys:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didDiscovered:(NSError * _Nonnull)result deviceList:(NSArray <GizWifiDevice *>* _Nullable)deviceList;

/*
 @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiSDKDelegate wifiSDK:didDiscovered:deviceList:]
 */
- (void)XPGWifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didDiscovered:(NSArray * _Null_unspecified)deviceList result:(int)result DEPRECATED_ATTRIBUTE;

/*
 设备配置文件上报的回调接口
 @param wifiSDK 为回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，其他回调参数为 nil
 @param productKey 下载数据点的产品类型唯一标识
 @param productUI 下载的 Json 格式的产品 UI 信息
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didUpdateProduct:(NSError * _Null_unspecified)result producKey:(NSString * _Null_unspecified)productKey productUI:(NSString * _Null_unspecified)productUI DEPRECATED_ATTRIBUTE;

/*
 @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiSDKDelegate wifiSDK:didUpdateProduct:producKey:productName:productUI:]
 */
- (void)XPGWifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didUpdateProduct:(NSString * _Null_unspecified)product result:(int)result DEPRECATED_ATTRIBUTE;

/*
 设备绑定结果的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param did 绑定成功的设备 did
 @see 触发函数：[GizWifiSDK bindRemoteDevice:token:mac:productKey:productSecret:], [GizWifiSDK bindDeviceByQRCode:token:QRContent:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didBindDevice:(NSError * _Nonnull)result did:(NSString * _Nullable)did;

/*
 @deprecated 此接口功能已废弃，不再提供支持。请使用替代接口：[GizWifiSDKDelegate wifiSDK:didBindDevice:]
 */
- (void)XPGWifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didBindDevice:(NSString * _Null_unspecified)did error:(NSNumber * _Null_unspecified)error errorMessage:(NSString * _Null_unspecified)errorMessage DEPRECATED_ATTRIBUTE;

/*
 设备解除绑定结果的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，其他回调参数为 nil
 @param did 已解绑的设备 did
 @see 触发函数：[GizWifiSDK unbindDevice:token:did:]
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didUnbindDevice:(NSError * _Nonnull)result did:(NSString * _Nullable)did;

/*
 @deprecated 此接口功能已废弃，不再提供支持。请使用替代接口：[GizWifiSDKDelegate wifiSDK:didUnbindDevice:did]
 */
- (void)XPGWifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didUnbindDevice:(NSString * _Null_unspecified)did error:(NSNumber * _Null_unspecified)error errorMessage:(NSString * _Null_unspecified)errorMessage DEPRECATED_ATTRIBUTE;

/*
 获取图片验证码的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，其他回调参数为 nil
 @param token 图片验证码 token。图片验证码token在1小时后过期
 @param captchaId 图片验证码 id。图片验证码5分钟后过期
 @param captchaURL 图片验证码网址。图片验证码 url 在使用后过期
 @see 触发函数：[GizWifiSDK getCaptchaCode:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didGetCaptchaCode:(NSError * _Nonnull)result token:(NSString * _Nullable)token captchaId:(NSString * _Nullable)captchaId captchaURL:(NSString * _Nullable)captchaURL;

/*
 请求手机短信验证码的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，其他回调参数为 nil
 @param token 请求短信验证码时得到的 token
 @see 触发函数：[GizWifiSDK requestSendPhoneSMSCode:phone:]、[GizWifiSDK requestSendPhoneSMSCode:captchaId:captchaCode:phone:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didRequestSendPhoneSMSCode:(NSError * _Nonnull)result token:(NSString * _Nullable)token;

/*
 @deprecated 此接口功能已废弃，不再提供支持。请使用替代接口：[GizWifiSDKDelegate wifiSDK:didRequestSendPhoneSMSCode:token:]
 */
- (void)wifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didRequestSendPhoneSMSCode:(NSError * _Null_unspecified)result DEPRECATED_ATTRIBUTE;

/*
 验证手机短信验证码的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，其他回调参数为 nil
 @see 触发函数：[GizWifiSDK verifyPhoneSMSCode:verifyCode:phone:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didVerifyPhoneSMSCode:(NSError * _Nonnull)result;

/*
 用户注册结果的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，其他回调参数为 nil
 @param uid 注册成功后得到的 uid
 @param token 注册成功后得到的 token
 @see 触发函数：[GizWifiSDK registerUser:password:verificationCode:accountType:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didRegisterUser:(NSError * _Nonnull)result uid:(NSString * _Nullable)uid token:(NSString * _Nullable)token;

/*
 @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiSDKDelegate wifiSDK:didRegisterUser:uid:token:]
 */
- (void)XPGWifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didRegisterUser:(NSNumber * _Null_unspecified)error errorMessage:(NSString * _Null_unspecified)errorMessage uid:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token DEPRECATED_ATTRIBUTE;

/*
 用户登录结果的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，其他回调参数为 nil
 @param uid 注册成功后得到的 uid
 @param token 注册成功后得到的 token
 @see 触发函数：[GizWifiSDK userLoginAnonymous], [GizWifiSDK userLogin:password:], [GizWifiSDK userLoginWithThirdAccount:uid:token:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didUserLogin:(NSError * _Nonnull)result uid:(NSString * _Nullable)uid token:(NSString * _Nullable)token;

/*
 @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiSDKDelegate wifiSDK:didUserLogin:uid:token:]
 */
- (void)XPGWifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didUserLogin:(NSNumber * _Null_unspecified)error errorMessage:(NSString * _Null_unspecified)errorMessage uid:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token DEPRECATED_ATTRIBUTE;

/*
 @deprecated 此接口已废弃，不再提供支持，无替代接口
 */
- (void)XPGWifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didUserLogout:(NSNumber * _Null_unspecified)error errorMessage:(NSString * _Null_unspecified)errorMessage DEPRECATED_ATTRIBUTE;

/*
 更换用户密码结果的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，其他回调参数为 nil
 @see 触发函数：[GizWifiSDK changeUserPassword:oldPassword:newPassword:]、[GizWifiSDK resetPassword:verificationCode:newPassword:accountType:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didChangeUserPassword:(NSError * _Nonnull)result;

/*
 @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiSDKDelegate wifiSDK:didChangeUserPassword:]
 */
- (void)XPGWifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didChangeUserPassword:(NSNumber * _Null_unspecified)error errorMessage:(NSString * _Null_unspecified)errorMessage DEPRECATED_ATTRIBUTE;

/*
 修改用户信息结果的回调接口
 @param wifiSDK 为回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败
 @see 触发函数：[GizWifiSDK changeUserInfo:username:SMSVerifyCode:accountType:additionalInfo:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didChangeUserInfo:(NSError * _Nonnull)result;

/*
 获取用户信息的回调接口，返回用户的信息结果
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param userInfo 用户信息，详细见 GizUserInfo类
 @see 触发函数：[GizWifiSDK getUserInfo:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didGetUserInfo:(NSError * _Nonnull)result userInfo:(GizUserInfo * _Nullable)userInfo;

/*
 匿名用户转换的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败
 @see 触发函数：[GizWifiSDK transAnonymousUser:username:password:verifyCode:accountType:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didTransAnonymousUser:(NSError * _Nonnull)result;

/*
 @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiSDKDelegate wifiSDK:didTransAnonymousUser:]
 */
- (void)XPGWifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didTransUser:(NSNumber * _Null_unspecified)error errorMessage:(NSString * _Null_unspecified)errorMessage DEPRECATED_ATTRIBUTE;

/*
 获取用户设备分组列表的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param groupList 为 GizWifiGroup 实例组成的数组
 @see 触发函数：[GizWifiSDK getGroups:specialProductKeys:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didGetGroups:(NSError * _Null_unspecified)result groupList:(NSArray * _Null_unspecified)groupList DEPRECATED_ATTRIBUTE;

/*
 @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiSDKDelegate wifiSDK:didGetGroups:groupList:]
 */
- (void)XPGWifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didGetGroups:(NSArray * _Null_unspecified)groupList result:(int)result DEPRECATED_ATTRIBUTE;

/*
 SDK系统事件通知
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param eventType 事件类型。指明发生了哪一类的事件，详细见 GizEventType 枚举定义
 @param eventSource 事件源，指是谁触发的事件。
 
 如果eventType是GizEventSDK，eventSource为nil；
 如果是GizEventDevice，eventSource需要强制转换为GizWifiDevice类型再使用；
 如果是GizEventM2Mservice或者GizEventToken，eventSource需要强制转换为NSString类型再使用
 
 @param eventID 事件ID。代表事件编号，详细见 GizWifiErrorCode 枚举定义。该参数指出 eventSource 发生了什么事
 @param eventMessage 事件ID的消息描述
 @see GizEventType
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didNotifyEvent:(GizEventType)eventType eventSource:(id _Nonnull)eventSource eventID:(GizWifiErrorCode)eventID eventMessage:(NSString * _Nullable)eventMessage;

/*
 切换服务的结果
 @param wifiSDK 为回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，其他回调参数为 nil
 @param cloudServiceInfo 云服务的信息，格式为：
 
 {
    "openAPIDomain" : "xxx",
    "openAPIPort" : xxx,
    "siteDomain" : "xxx",
    "sitePort" : xxx,
    "pushDomain": xxx,
    "pushPort": xxx
 }

 @see 触发函数：[GizWifiSDK setCloudService:]
 @see GizWifiErrorCode
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didGetCurrentCloudService:(NSError * _Nonnull)result cloudServiceInfo:(NSDictionary * _Nullable)cloudServiceInfo;

/*
 绑定推送id结果（此接口待发布）
 @param wifiSDK 为回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，其他回调参数为 nil
 @see 触发函数：[GizWifiSDK channelIDBind:channelID:alias:pushType:]
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didChannelIDBind:(NSError * _Nonnull)result;

/*
 解绑推送id结果（此接口待发布）
 @param wifiSDK 为回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，其他回调参数为 nil
 @see 触发函数：[GizWifiSDK channelIDUnBind:channelID:]
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didChannelIDUnBind:(NSError * _Nonnull)result;

/*
 禁用/启用小循环的结果
 @param wifiSDK 为回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，其他回调参数为 nil
 @see 触发函数：[GizWifiSDK disableLAN:]
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didDisableLAN:(NSError * _Nonnull)result;


- (void)wifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didCreateScheduler:(NSError * _Null_unspecified)result sid:(NSString * _Null_unspecified)sid DEPRECATED_ATTRIBUTE;
- (void)wifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didDeleteScheduler:(NSError * _Null_unspecified)result DEPRECATED_ATTRIBUTE;
- (void)wifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didGetSchedulers:(NSError * _Null_unspecified)result scheduleTaskList:(NSArray * _Nullable)scheduleTaskList DEPRECATED_ATTRIBUTE;
- (void)wifiSDK:(GizWifiSDK * _Null_unspecified)wifiSDK didGetSchedulerStatus:(NSError * _Null_unspecified)result sid:(NSString * _Null_unspecified)sid datetime:(NSString * _Null_unspecified)datetime status:(GizScheduleStatus)status statusDetail:(NSDictionary * _Null_unspecified)statusDetail DEPRECATED_ATTRIBUTE;

/*
 获取可以设置域名的设备列表的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 获取成功或失败。如果获取失败，其他参数为nil
 @param devices 设备信息字典组成的数组。设备信息的字典格式如下：
 {
 “mac”: “xxx” // 设备mac地址
 “productKey”: “xxx” // 设备的productKey
 “domain”: “xxx” // 设备的域名信息
 }
 @note 该回调接口只返回设备的mac、productKey、domain这三个信息，不返回设备对象
 @see 触发函数：[GizWifiSDK getDevicesToSetServerInfo]
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didGetDevicesToSetServerInfo:(NSError * _Nonnull)result devices:(NSArray <NSDictionary *>* _Nullable)devices;

/*
 给模组设置域名的回调接口
 @param wifiSDK 回调的 GizWifiSDK 单例
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param mac 设置域名的设备 mac
 @see 触发函数：[GizWifiSDK setDeviceServerInfo:mac:]
 */
- (void)wifiSDK:(GizWifiSDK * _Nonnull)wifiSDK didSetDeviceServerInfo:(NSError * _Nonnull)result mac:(NSString * _Nullable)mac;

@end

/*
 GizWifiSDK类为APP开发者提供设备配置和发现、设备分组、用户登录和注册函数
 */
@interface GizWifiSDK : NSObject

- (instancetype _Nullable)init NS_UNAVAILABLE;

/*
 获取 GizWifiSDK 单例的实例
 @return 返回初始化后 SDK 唯一的实例。SDK 不管有没有初始化，都会返回一个有效的值。
 */
+ (instancetype _Nonnull)sharedInstance;

+ (void)startWithAppID:(NSString * _Null_unspecified)appID DEPRECATED_ATTRIBUTE;
+ (void)startWithAppID:(NSString * _Null_unspecified)appID specialProductKeys:(NSArray * _Null_unspecified)specialProductKeys cloudServiceInfo:(NSDictionary * _Null_unspecified)cloudSeviceInfo DEPRECATED_ATTRIBUTE;
+ (void)startWithAppID:(NSString * _Null_unspecified)appID specialProductKeys:(NSArray * _Null_unspecified)specialProductKeys cloudServiceInfo:(NSDictionary * _Null_unspecified)cloudSeviceInfo autoSetDeviceDomain:(BOOL)autoSetDeviceDomain DEPRECATED_ATTRIBUTE;
+ (void)startWithAppID:(NSString * _Nonnull)appID appSecret:(NSString * _Nonnull)appSecret specialProductKeys:(NSArray <NSString *>* _Nullable)specialProductKeys cloudServiceInfo:(NSDictionary * _Nullable)cloudSeviceInfo autoSetDeviceDomain:(BOOL)autoSetDeviceDomain DEPRECATED_ATTRIBUTE;

/**
 初始化 SDK。该接口执行后，其他接口功能才能正常执行。如果已经设置了delegate，SDK会立即通过didDiscovered上报发现的设备。
 如果App要做域名切换和设备过滤，请在初始化SDK时就指定好要切换的域名和产品信息。
 如果需要设置设备连接的云服务域名，可以在该接口调用时开启自动设置功能。SDK会为所有已与AppID关联的设备设置域名，支持域名设置的设备会与App连接到同一个云服务域名上。但该接口默认是不开启此功能的。
 
 注意：设备域名自动设置开启后会一直生效，但调用setDeviceServerInfo接口时将会终止自动设置
 @param appInfo 应用信息，格式：{"appId": "xxx", "appSecret": "xxx"}。此参数不能填nil，appId和appSecret必须为有效值。在机智云开发者中心 dev.gizwits.com 中，每个注册的设备在对应的“应用配置”中，都能够查到对应的 appID和appSecret
 @param productInfo 产品信息数组，格式：[{"productKey": "xxx", "productSecret": "xxx"}]，此参数为选填。如果填写了此参数，需保证productKey和productSecret为有效值，无效值会被忽略。SDK会根据此参数过滤设备列表
 @param cloudSeviceInfo 服务器域名信息，格式：{"openAPIInfo": "xxx", "siteInfo": "xxx", "pushInfo": ""}。如果使用机智云统一部署的云服务域名，此参数填nil，此时将根据用户手机的地理位置信息使用匹配的域名。如果需要独立部署，此参数必须指定域名信息。如果需要指定端口号，需同时指定Http和Https端口：xxx.gizwits.com:81&8443。不指定端口号时，形如：xxx.gizwits.com
 @param autoSetDeviceDomain 是否要开启设备域名的自动设置功能。此参数默认值为NO，即不开启自动设置。参数值传YES则开启设备域名的自动设置功能，如果开启了设备域名的自动设置，小循环设备将被连接到App当前使用的云服务域名上
 @see 回调 [wifiSDK didNotifyEvent:eventSource:eventID:eventMessage:]
 */
+ (void)startWithAppInfo:(NSDictionary * _Nonnull)appInfo productInfo:(NSArray * _Nullable)productInfo cloudServiceInfo:(NSDictionary * _Nullable)cloudSeviceInfo autoSetDeviceDomain:(BOOL)autoSetDeviceDomain;

/*
 获取 SDK 版本号
 @return 返回当前 SDK 的版本号码
 */
+ (NSString * _Nonnull)getVersion;

/*
 使用委托获取对应事件。GizWifiSDK 对应的回调接口在 GizWifiSDKDelegate 定义。需要用到哪个接口，回调即可
 */
@property (weak, nonatomic) id <GizWifiSDKDelegate>_Nullable delegate;

/*
 设置日志输出级别。该级别指日志在调试终端的输出级别，默认是全部输出的
 @param logPrintLevel 日志输出级别，参考 GizLogPrintLevel 定义
 @see GizWifiLogLevel
 */
+ (void)setLogLevel:(GizLogPrintLevel)logPrintLevel;

/*
 @deprecated 此接口已废弃，不再提供支持，无替代接口。其对应的信息通过回调给出：[GizWifiSDKDelegate wifiSDK:didUpdateProduct:producKey:productName:productUI:]
 */
+ (void)updateDeviceFromServer:(NSString * _Null_unspecified)productKey DEPRECATED_ATTRIBUTE;

/*
 把设备配置到局域网 wifi 上。设备处于 softap 模式时，模组会产生一个热点名称，手机 wifi 连接此热点后就可以配置了。如果是机智云提供的固件，模组热点名称前缀为"XPG-GAgent-"，密码为"123456789"。设备处于 airlink 模式时，手机随时都可以开始配置。但无论哪种配置方式，设备上线时，手机要连接到配置的局域网 wifi 上，才能够确认设备已配置成功。
 设备配置成功时，在回调中会返回设备 mac 地址。如果设备重置了，设备did可能要在设备搜索回调中才能获取。
 
 @param ssid 待配置的路由 SSID 名
 @param key 待配置的路由密码
 @param mode 配置模式，详细见 GizWifiConfigureMode 枚举定义
 @param softAPSSIDPrefix SoftAPMode 模式下 SoftAP 的 SSID 前缀或全名。默认前缀为：XPG-GAgent-，SDK 以此判断手机当前是否连上了设备的 SoftAP 热点。AirLink 模式时传 nil 即可
 @param timeout 配置的超时时间。SDK 默认执行的最小超时时间为30秒
 @param types 待配置的模组类型，是一个GizWifiGAgentType 枚举数组。若不指定则默认配置乐鑫模组。GizWifiGAgentType定义了 SDK 支持的所有模组类型
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didSetDeviceOnboarding:device:]
 @see GizConfigureMode
 @see GizWifiGAgentType
 */
- (void)setDeviceOnboarding:(NSString * _Nonnull)ssid
                        key:(NSString * _Nullable)key
                 configMode:(GizWifiConfigureMode)mode
           softAPSSIDPrefix:(NSString * _Nullable)softAPSSIDPrefix
                    timeout:(int)timeout
             wifiGAgentType:(NSArray <NSNumber *>* _Nullable)types;

/**
 设备配网绑定接口，配网成功时自动绑定设备。此接口要在用户登录成功后再调用。
 设备处于 softap 模式时，模组会产生一个热点名称，手机 wifi 连接此热点后就可以配置了。如果是机智云提供的固件，模组热点名称前缀为"XPG-GAgent-"，密码为"123456789"或无密码。设备处于 airlink 模式时，手机随时都可以开始配置。但无论哪种配置方式，设备上线时，手机要先连接到配置的局域网 wifi 上然后才能被绑定到用户账号下。
 @param ssid 待配置的路由SSID名。此参数不能为nil
 @param key 待配置的路由密码。此参数不能为nil
 @param mode 配置模式，详细见GizWifiConfigureMode枚举定义。此参数必须填有效范围内的值
 @param softAPSSIDPrefix 热点模式下设备热点前缀或全名。默认前缀为:XPG-GAgent-，SDK以此判断手机当前是否连上了设备的热点。AirLink模式下可传nil
 @param timeout 配网绑定的超时时间，默认超时时间为30秒。在超时时间内如果无法配置和绑定会回调配网失败
 @param wifiGAgentType 待配置的模组类型数组，详细见GizWifiGAgentType枚举。默认类型为GizGAgentESP。如果在模组类型中找不到自己使用的模组，可传GizGAgentOther
 @see 回调函数 [GizWifiSDKDelegate wifiSDK:didSetDeviceOnboarding:mac:did:productKey:]
 */
- (void)setDeviceOnboardingByBind:(NSString * _Nonnull)ssid key:(NSString * _Nullable)key configMode:(GizWifiConfigureMode)mode softAPSSIDPrefix:(NSString * _Nullable)softAPSSIDPrefix timeout:(int)timeout wifiGAgentType:(NSArray * _Nullable)types;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[setDeviceOnboarding:key:configMode:softAPSSIDPrefix:timeout:wifiGAgentType:]
 */
- (void)setDeviceWifi:(NSString * _Null_unspecified)ssid key:(NSString * _Null_unspecified)key mode:(XPGConfigureMode)mode softAPSSIDPrefix:(NSString * _Null_unspecified)softAPSSIDPrefix timeout:(int)timeout wifiGAgentType:(NSArray * _Null_unspecified)types DEPRECATED_ATTRIBUTE;

/*
 在 Soft-AP 模式时，获得设备的 SSID 列表。SSID列表通过异步回调方式返回
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didGetSSIDList:ssidList:]
 */
- (void)getSSIDList;

/*
 NSArray类型，为 GizWifiDevice 对象数组。设备列表缓存，APP 访问该变量即可得到当前 GizWifiSDK 发现的设备列表
 */
@property (strong, nonatomic, readonly) NSArray <GizWifiDevice *>* _Nullable deviceList;

/*
 获取绑定设备列表。在不同的网络环境下，有不同的处理：
 当手机能访问外网时，该接口会向云端发起获取绑定设备列表请求；
 当手机不能访问外网时，局域网设备是实时发现的，但会保留之前已经获取过的绑定设备；
 手机处于无网模式时，局域网未绑定设备会消失，但会保留之前已经获取过的绑定设备；
 此接口传入的uid、token，如果长度错误，SDK会继续使用之前的uid、token作处理
 
 @param uid 用户登录或注册时得到的 uid
 @param token 用户登录或注册时得到的 token
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didDiscovered:deviceList:]
 */
- (void)getBoundDevices:(NSString * _Nullable)uid token:(NSString * _Nullable)token specialProductKeys:(NSArray <NSString *>* _Nullable)specialProductKeys DEPRECATED_ATTRIBUTE;
- (void)getBoundDevices:(NSString * _Nullable)uid token:(NSString * _Nullable)token;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[GizWifiSDK bindRemoteDevice:token:mac:productKey:productSecret:]
 */
- (void)bindDeviceWithUid:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token did:(NSString * _Null_unspecified)did passCode:(NSString * _Null_unspecified)passCode remark:(NSString * _Null_unspecified)remark DEPRECATED_ATTRIBUTE;

/*
 绑定远端设备到服务器
 @param uid 用户登录或注册时得到的 uid
 @param token 用户登录或注册时得到的 token
 @param mac 待绑定设备的mac
 @param productKey 待绑定设备的productKey
 @param productSecret 待绑定设备的productSecret
 @param appSecret 在 site 上的应用管理得到的 appSecret
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didBindDevice:did:]
 */
- (void)bindRemoteDevice:(NSString * _Nonnull)uid token:(NSString * _Nonnull)token mac:(NSString * _Nonnull)mac productKey:(NSString * _Nonnull)productKey productSecret:(NSString * _Nonnull)productSecret;

/*
 根据二维码绑定设备到服务器（此接口待发布）
 @param uid 用户登录或注册时得到的 uid
 @param token 用户登录或注册时得到的 token
 @param QRContent 二维码内容
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didBindDevice:did:]
 */
- (void)bindDeviceByQRCode:(NSString * _Nonnull)uid token:(NSString * _Nonnull)token QRContent:(NSString * _Nonnull)QRContent;

/*
 从服务器解绑设备
 @param 用户登录或注册时得到的uid
 @param 用户登录或注册时得到的token
 @param 待解绑设备的did
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didUnbindDevice:did:]
 */
- (void)unbindDevice:(NSString * _Nonnull)uid token:(NSString * _Nonnull)token did:(NSString * _Nonnull)did;

/*
 @deprecated 此接口功能已废弃，不再提供支持。替代接口：[unbindDevice:token:did:]
 */
- (void)unbindDeviceWithUid:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token did:(NSString * _Null_unspecified)did passCode:(NSString * _Null_unspecified)passCode DEPRECATED_ATTRIBUTE;

/*
 获取图片验证码。开发者登录 site.gizwits.com，在自己账户下的应用管理中可以得到 App Secret，通过应用的 App Secret 才能获取到图片验证码
 @param appSecret 应用的 secret 信息，从 site.gizwits.com 中可以看到
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didGetCaptchaCode:token:captchaId:captchaURL:]
 */
- (void)getCaptchaCode:(NSString *_Nonnull)appSecret;

/*
 通过图形验证码获取手机短信验证码
 @param token 通过 getCaptchaCode 获取到的 token
 @param captchaId 通过 getCaptchaCode 获取到的 captchaId
 @param captchaCode 图片验证码的内容
 @param phone 手机号
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didRequestSendPhoneSMSCode:]
 */
- (void)requestSendPhoneSMSCode:(NSString * _Nonnull)token captchaId:(NSString * _Nonnull)captchaId captchaCode:(NSString * _Nonnull)captchaCode phone:(NSString * _Nonnull)phone;

/*
 通过手机号请求短信验证码
 @param 应用的 secret 信息，从 site.gizwits.com 中可以看到
 @param phone 手机号
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didRequestSendPhoneSMSCode:token:]
 */
- (void)requestSendPhoneSMSCode:(NSString * _Nonnull)appSecret phone:(NSString * _Nonnull)phone;

/*
 验证手机短信验证码。注意，验证短信验证码后，验证码就失效了，无法再用于手机号注册
 @param token 验证码的 token，通过 getCaptchaCode 获取
 @param phoneCode 手机短信验证码
 @param phone 手机号
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didVerifyPhoneSMSCode:]
 */
- (void)verifyPhoneSMSCode:(NSString * _Nonnull)token verifyCode:(NSString * _Nonnull)code phone:(NSString * _Nonnull)phone;

/*
 用户注册。需指定用户类型注册。手机用户的用户名是手机号，邮箱用户的用户名是邮箱、普通用户的用户名可以是普通用户名
 @param username 注册用户名（可以是手机号、邮箱或普通用户名）
 @param password 注册密码
 @param code 手机短信验证码。短信验证码注册后就失效了，不能被再次使用
 @param accountType 用户类型，详细见 GizUserAccountType 枚举定义。注册手机号时，此参数指定为手机用户，注册邮箱时，此参数指定为邮箱用户，注册普通用户名时，此参数指定为普通用户
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didRegisterUser:uid:token:]
 @see GizUserAccountType
 */
- (void)registerUser:(NSString * _Nonnull)username
            password:(NSString * _Nonnull)password
          verifyCode:(NSString * _Nullable)code
         accountType:(GizUserAccountType)accountType;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[registerUser:password:verifyCode:accountType:]
 */
- (void)registerUser:(NSString * _Null_unspecified)userName password:(NSString * _Null_unspecified)password DEPRECATED_ATTRIBUTE;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[registerUser:password:verifyCode:accountType:]
 */
- (void)registerUserByPhoneAndCode:(NSString * _Null_unspecified)phone password:(NSString * _Null_unspecified)password code:(NSString * _Null_unspecified)code DEPRECATED_ATTRIBUTE;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[registerUser:password:verifyCode:accountType:]
 */
- (void)registerUserByEmail:(NSString * _Null_unspecified)email password:(NSString * _Null_unspecified)password DEPRECATED_ATTRIBUTE;

/*
 匿名登录。匿名方式登录，不需要注册用户账号
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didUserLogin:uid:token:]
 */
- (void)userLoginAnonymous;

/*
 用户登录。需使用注册成功的用户名、密码进行登录，可以是手机用户名、邮箱用户名或普通用户名
 @param username 注册成功的用户名
 @param password 注册成功的用户密码
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didUserLogin:uid:token:]
 */
- (void)userLogin:(NSString * _Nonnull)username password:(NSString * _Nonnull)password;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[userLogin:password:]
 */
- (void)userLoginWithUserName:(NSString * _Null_unspecified)szUserName password:(NSString * _Null_unspecified)szPassword DEPRECATED_ATTRIBUTE;

/*
 第三方账号登录（第三方接口登录方式）
 @param thirdAccountType 第三方账号类型，详细见 GizThirdAccountType 枚举定义
 @param uid 通过第三方平台 api 方式登录后得到的 uid
 @param token 通过第三方平台api方式 登录后得到的 token
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didUserLogin:uid:token:]
 @see GizThirdAccountType
 */
- (void)userLoginWithThirdAccount:(GizThirdAccountType)thirdAccountType uid:(NSString * _Nonnull)uid token:(NSString * _Nonnull)token;
- (void)userLoginWithThirdAccount:(GizThirdAccountType)thirdAccountType uid:(NSString * _Nonnull)uid token:(NSString * _Nonnull)token tokenSecret:(NSString * _Nullable)tokenSecret;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[userLoginWithThirdAccount:uid:token:]
 */
- (void)userLoginWithThirdAccountType:(XPGWifiThirdAccountType)thirdAccountType uid:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token DEPRECATED_ATTRIBUTE;

/*
 @deprecated 此接口已废弃，不再提供功能支持，无替代接口。
 */
- (void)userLogout:(NSString * _Null_unspecified)uid DEPRECATED_ATTRIBUTE;

/*
 修改用户密码
 @param token 用户登录或注册时得到的 token
 @param oldPassword 旧密码
 @param newPassword 新密码
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didChangeUserPassword:]
 */
- (void)changeUserPassword:(NSString * _Nonnull)token
               oldPassword:(NSString * _Nonnull)oldPassword
               newPassword:(NSString * _Nonnull)newPassword;

/*
 重置密码
 @param username 待重置密码的手机号或邮箱
 @param code 重置手机用户密码时需要使用手机短信验证码（通过 requestSendPhoneSMSCode 方法获取）
 @param newPassword 新密码
 @param accountType 用户类型，详细见 GizThirdAccountType 枚举定义。待重置密码的用户名是手机号时，此参数指定为手机用户，待重置密码的用户名是邮箱时，此参数指定为邮箱用户
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didChangeUserPassword:errorMessage:]
 @see GizUserAccountType
 */
- (void)resetPassword:(NSString * _Nonnull)username
           verifyCode:(NSString * _Nullable)code
          newPassword:(NSString * _Nullable)newPassword
          accountType:(GizUserAccountType)accountType;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[resetPassword:verifyCode:newPassword:accountType:]
 */
- (void)changeUserPasswordByCode:(NSString * _Null_unspecified)phone code:(NSString * _Null_unspecified)code newPassword:(NSString * _Null_unspecified)newPassword DEPRECATED_ATTRIBUTE;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[resetPassword:verifyCode:newPassword:accountType:]
 */
- (void)changeUserPasswordByEmail:(NSString * _Null_unspecified)email DEPRECATED_ATTRIBUTE;

/*
 修改用户信息，包括用户名和个人信息。用户名只支持修改手机号或邮箱，并且手机号或邮箱必须是已经注册过的。该接口用于以下场景：
 只修改手机号、只修改邮箱、只修改普通用户的个人信息、同时修改手机号和补充信息、同时修改邮箱和补充信息。
 只修改个人信息时，accountType可以指定为GizUserNormal；修改手机号要指定为GizUserPhone；修改邮箱要指定为GizUserEmail
 
 @param token 用户登录或注册时得到的 token
 @param username 待修改的手机号或邮箱
 @param code 修改手机号时要使用的手机短信验证码
 @param accountType 用户类型，详细见 GizThirdAccountType 枚举定义。修改手机号时，accountType传GizUserPhone；修改普通用户名时，accountType传GizUserEmail；只修改个人信息时，accountType传GizUserNormal；同时修改用户名和个人信息时，可根据待修改的是手机号还是邮箱来指定
 @param additionalInfo 待修改的个人信息，详细见 GizUserInfo 类定义。如果只修改个人信息，需要指定token，username、code填null
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didChangeUserInfo:]
 @see GizUserAccountType
 @see GizUserInfo
 */
- (void)changeUserInfo:(NSString * _Nonnull)token username:(NSString * _Nonnull)username SMSVerifyCode:(NSString * _Nullable)code accountType:(GizUserAccountType)accountType additionalInfo:(GizUserInfo * _Nonnull)additionalInfo;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[changeUserInfo:username:SMSVerifyCode:accountType:additionalInfo:]
 */
- (void)changeUserInfo:(NSString * _Null_unspecified)token username:(NSString * _Null_unspecified)username verifyCode:(NSString * _Null_unspecified)code accountType:(XPGUserAccountType)accountType additionalInfo:(GizUserInfo * _Null_unspecified)additionalInfo DEPRECATED_ATTRIBUTE;

/*
 获取用户信息
 @param token 用户登录或注册时得到的 token
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didGetUserInfo:]
 */
- (void)getUserInfo:(NSString * _Nonnull)token;

/*
 匿名用户转换，可转换为手机用户或者普通用户。注意，待转换的帐号必须是还未注册过的
 @param token 用户登录或注册时得到的 token
 @param username 待转换用户的普通账号或手机号
 @param password 待转换用户的密码
 @param code 转换为手机用户时需要使用手机短信验证码
 @param accountType 用户类型，详细见 GizThirdAccountType 枚举定义。待转换的用户名是手机号时，此参数指定为GizUserPhone，待转换用户名是普通账号时，此参数指定为GizUserNormal
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didTransAnonymousUser:]
 @see GizUserAccountType
 */
- (void)transAnonymousUser:(NSString * _Nonnull)token
                  username:(NSString * _Nonnull)username
                  password:(NSString * _Nonnull)password
                verifyCode:(NSString * _Nullable)code
               accountType:(GizUserAccountType)accountType;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[transAnonymousUser:username:password:verifyCode:accountType:]
 */
- (void)transAnonymousUserToNormalUser:(NSString * _Null_unspecified)token userName:(NSString * _Null_unspecified)userName password:(NSString * _Null_unspecified)password DEPRECATED_ATTRIBUTE;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[transAnonymousUser:username:password:verifyCode:accountType:]
 */
- (void)transAnonymousUserToPhoneUser:(NSString * _Null_unspecified)token phone:(NSString * _Null_unspecified)phone password:(NSString * _Null_unspecified)password code:(NSString * _Null_unspecified)code DEPRECATED_ATTRIBUTE;

- (void)getGroups:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token specialProductKeys:(NSArray * _Null_unspecified)specialProductKeys DEPRECATED_ATTRIBUTE;
- (void)addGroup:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token productKey:(NSString * _Null_unspecified)productKey groupName:(NSString * _Null_unspecified)groupName specialDevices:(NSArray * _Null_unspecified)specialDevices DEPRECATED_ATTRIBUTE;
- (void)removeGroup:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token gid:(NSString * _Null_unspecified)gid DEPRECATED_ATTRIBUTE;
- (void)editGroup:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token gid:(NSString * _Null_unspecified)gid groupName:(NSString * _Null_unspecified)groupName specialDevices:(NSArray * _Null_unspecified)specialDevices DEPRECATED_ATTRIBUTE;

/*
 切换服务器（已废弃）
 @see 替代接口：[GizWifiSDK startWithAppID:specialProductKeys:cloudServiceInfo:autoSetDeviceDomain:]
 */
+ (void)setCloudService:(NSDictionary * _Null_unspecified)cloudServiceInfo DEPRECATED_ATTRIBUTE;

/*
 @deprecated 此接口已废弃，不再提供支持。替代接口：[setCloudService:]
 */
+ (void)setCloudService:(NSString * _Null_unspecified)openAPIDomain openAPIPort:(int)port siteDomain:(NSString * _Null_unspecified)domain sitePort:(int)sitePort DEPRECATED_ATTRIBUTE;

/*
 获取当前的服务器
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didGetCurrentCloudService:cloudServiceInfo:]
 */
+ (void)getCurrentCloudService;

/*
 绑定推送的id（此接口待发布）
 @param token 用户登录或注册时得到的 token
 @param channelID 推送ID
 @param alias 别名
 @param pushType 推送类型，详细见 GizPushType 枚举定义
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didChannelIDBind:]
 */
- (void)channelIDBind:(NSString * _Nonnull)token channelID:(NSString * _Nonnull)channelID alias:(NSString * _Nullable)alias pushType:(GizPushType)pushType;

/*
 解绑推送的id（此接口待发布）
 @param token 用户登录或注册时得到的 token
 @param channelID 推送ID
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didChannelIDUnBind:]
 */
- (void)channelIDUnBind:(NSString * _Nonnull)token channelID:(NSString * _Nonnull)channelID;

/*
 禁用/启用小循环
 @param disabled YES=禁用小循环，NO=启用小循环
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didDisableLAN:]
 */
+ (void)disableLAN:(BOOL)disabled;

- (void)createScheduler:(NSString * _Null_unspecified)token schedulerInfo:(GizDeviceScheduler * _Null_unspecified)schedulerInfo DEPRECATED_ATTRIBUTE;
- (void)getSchedulers:(NSString * _Null_unspecified)token DEPRECATED_ATTRIBUTE;
- (void)deleteScheduler:(NSString * _Null_unspecified)token sid:(NSString * _Null_unspecified)sid DEPRECATED_ATTRIBUTE;
- (void)getSchedulerStatus:(NSString * _Null_unspecified)token sid:(NSString * _Null_unspecified)sid DEPRECATED_ATTRIBUTE;

@property (strong, nonatomic, readonly) NSString * _Nullable domain;

/*
 获取可以设置域名的设备列表。返回的设备列表中只包括支持设置域名功能的设备。
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didGetDevicesToSetServerInfo:devices:]
 */
+ (void)getDevicesToSetServerInfo;

/*
 此接口为手动设置设备域名接口，可为设备设置对应的云服务域名。
 设备和手机都连接到同一个 wifi 路由器后，可以设置设备要连接的云服务域名。可以设置当 前已上线的所有小循环设备的域名。也可以单独设置某个设备的域名。如果不知道设备的 MAC 地址，可以先调用 getDevicesToSetServerInfo 接口查看有哪些设备可以设置域名，再调 用该接口进行设置。
 注意:只支持可设置域名的设备。
 @param domain 待设置的域名。若该参数为 nil，SDK 将根据用户手机的地理位置信息 为设备设置机智云统一部署的云服务域名。若要让设备连接独立部署的私有云域名，该参数为对应的私有云域名字符串，格式为:api.xxxxxx.com。这里需保证传入的域名是有效的， 否则可能导致设备无法正常工作
 @param mac 待设置的设备 mac。默认参数为 nil，即所有已发现的小循环设备都会 被修改域名。如果只设置特定设备的域名，需指定 mac 地址
 @see 对应的回调接口：[GizWifiSDKDelegate wifiSDK:didSetDeviceServerInfo:mac:]
 */
+ (void)setDeviceServerInfo:(NSString * _Nonnull)domain mac:(NSString * _Nonnull)mac;

/**
 用户反馈，此接口无回调。调用后就会上传信息
 @param contactInfo 用户的联系方式。此参数为选填
 @param feedbackInfo 用户反馈的信息。此参数为选填
 @param sendLog 是否发送问题日志。如果前面两个参数都没填，则默认发送问题日志
 */
+ (void)userFeedback:(NSString * _Nullable)contactInfo feedbackInfo:(NSString * _Nullable)feedbackInfo sendLog:(BOOL)sendLog;

@end
