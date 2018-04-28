//
//  YKCenterSDK.h
//  YKCenterSDK
//
//  Created by Don on 2017/1/12.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <YKCenterSDK/YKCenterSDKHeader.h>

@class GizWifiDevice;

NS_ASSUME_NONNULL_BEGIN

@interface YKCenterSDK : NSObject

//! Project version number for YKCenterSDK.
FOUNDATION_EXPORT double YKCenterSDKVersionNumber;

//! Project version string for YKCenterSDK.
FOUNDATION_EXPORT const unsigned char YKCenterSDKVersionString[];

- (instancetype)init NS_UNAVAILABLE;

/*
 获取 YKCenterSDK 单例的实例
 
 @return 返回初始化后 SDK 唯一的实例。SDK 不管有没有初始化，都会返回一个有效的值。
 */
+ (instancetype)sharedInstance;


/**
 注册并初始化 SDK。
 
 注意：此接口调用成功后，其他接口的功能才可以正常使用。
 
 @param appId 应用 ID 是在遥看开发者中心注册。
 */
+ (void)registApp:(NSString *)appId;

/**
 注册并初始化 SDK，有注册结果回调方法。
 
 注意：此接口调用成功后，其他接口的功能才可以正常使用。
 
 @param appId 应用 ID 是在遥看开发者中心注册。
 @param completion 注册成功回调。
 */
+ (void)registApp:(NSString *)appId completion:(void (^ __nullable)(NSError *error))completion;

/**
 注册并初始化遥控中心 SDK。
 
 注意：此接口仅初始化遥控中心SDK。
 
 @param appId 应用 ID 是在遥看开发者中心注册。
 */
+ (void)registYKApp:(NSString *)appId;

/**
 绑定遥控中心 YKC，完成后使用 block 回调返回结果。

 @param ssid Wi-Fi 的 SSID 名称
 @param password Wi-Fi 的密码
 @param completion 绑定遥控中心设备完成的回调。如果绑定出错，返回 error 对象；如果有连接成功，error 为空，返回新入网的设备device 对象。
 */
+ (void)bindYKCWithSSID:(NSString *)ssid
               password:(nullable NSString *)password
             completion:(void (^__nullable)(NSError * _Nullable error, GizWifiDevice * _Nullable  device))completion;



/**
 绑定遥控中心 YKC，完成后使用 block 回调返回结果。

 @param device 遥控中心设备对象
 @param completion 回调参数 did 为绑定后的遥控中心设备 ID
 */
+ (void)bindDevice:(GizWifiDevice *)device completion:(void (^__nullable)(NSString *did))completion;

/**
 解除遥控中心绑定，完成后使用 block 回调返回结果。

 @param device 遥控中心对象
 @param completion 成功，error 为空
 */
+ (void)unbindYKC:(GizWifiDevice *)device completion:(void (^__nullable)(NSError *error))completion;


/**
 订阅遥控中心，完成后使用 block 回调返回结果

 @param device 遥控中心对象
 @param handler 回调参数是订阅成功的遥控中心
 */
+ (void)subscribeDevice:(GizWifiDevice *)device completion:(void (^__nullable)(GizWifiDevice *))handler;

/**
 获取已绑定遥控中心 YKC

 @param completion 回调返回已绑定遥控中心列表
 */
+ (void)fetchBoundYKC:(void (^__nullable)(NSArray<GizWifiDevice *> * _Nullable devices,
                                          NSError *error))completion;


/**
 获取遥控码的设备类型

 @param ykcId       遥控中心 id
 @param completion  返回遥控码的设备类型列表
 */
+ (void)fetchRemoteDeviceTypeWithYKCId:(NSString *)ykcId
                            completion:(void (^__nullable)(NSArray<YKRemoteDeviceType *> *types, NSError *error))completion;


/**
 获取遥控码的设备品牌

 @param ykcId       遥控中心 id
 @param typeId      遥控码的设备类型 id
 @param completion  返回遥控码的设备品牌列表
 */
+ (void)fetchRemoteDeviceBrandWithYKCId:(NSString *)ykcId
                     remoteDeviceTypeId:(NSUInteger)typeId
                             completion:(void (^__nullable)(NSArray<YKRemoteDeviceBrand*> *brands, NSError *error))completion;


/**
 获取遥控码的匹配设备列表，每个遥控码设备只返回几个匹配用的按键（遥控码）

 @param ykcId 遥控中心 id
 @param typeId 遥控码的设备类型 id
 @param brandId 遥控码的品牌 id
 @param completion 返回遥控码的匹配设备列表
 */
+ (void)fetchMatchRemoteDeviceWithYKCId:(NSString *)ykcId
                     remoteDeviceTypeId:(NSUInteger)typeId
                    remoteDeviceBrandId:(NSUInteger)brandId
                             completion:(void (^__nullable)(NSArray<YKRemoteMatchDevice*> *mathes, NSError *error))completion;

/**
 获取遥控器设备，此方法会保存遥控器

 @param ykcId           遥控中心 id
 @param remoteDeviceId  遥控器设备 id
 @param completion      回调返回遥控器
 */
+ (void)fetchRemoteDeivceWithYKCId:(NSString *)ykcId
                    remoteDeviceId:(NSString *)remoteDeviceId
                        completion:(void (^__nullable)(YKRemoteDevice *remote, NSError *error))completion;

/**
 获取遥控器，此方法已废弃，请不要使用
 
 @param ykcId           遥控中心 id
 @param remoteDeviceId  遥控器设备 id
 @param match           是否匹配模式，是则不保存，保存需调用 YKRemoteDevice 的 + (void)fetchRemoteDeivceWithYKCId:remoteDeviceId:completion:，删除掉用 YKRemoteDevice 的 + (BOOL)removeMemoryModel
 @param completion      回调返回遥控器
 */
+ (void)fetchRemoteDeivceWithYKCId:(NSString *)ykcId
                    remoteDeviceId:(NSString *)remoteDeviceId
                        matchModel:(BOOL)match
                        completion:(void (^__nullable)(YKRemoteDevice *remote, NSError *error))completion __attribute__((deprecated("use fetchRemoteDeivceWithYKCId:remoteDeviceId:completion: instead")));

/**
 获取匹配遥控器，此方法已废弃，请不要使用
 
 @param ykcId           遥控中心 id
 @param remoteDeviceId  遥控器设备 id
 @param completion      回调返回匹配遥控器
 */
+ (void)matchRemoteDeivceWithYKCId:(NSString *)ykcId
                    remoteDeviceId:(NSString *)remoteDeviceId
                        completion:(void (^__nullable)(YKRemoteMatchDevice *remote, NSError *error))completion
__attribute__((deprecated("no available anymore")));

/**
 发码给遥控中心

 @param ykcId 遥控中心 id
 @param datas 遥控码对象数组
 @param completion 发码结果回调
 */
+ (void)sendRemoteWithYKCId:(NSString *)ykcId
                      datas:(NSArray *)datas
        completion:(void (^__nullable)(BOOL result, NSError *error))completion;

/**
 一键匹配新接口

 @param ykcid 遥控中心 id
 @param type 遥控器设备类型
 @param brandId 品牌 id
 @param key 键名
 @param cmd 键值
 @param completion 结果回调
 */
+ (void)oneKeyMatchWithYKCId:(NSString *)ykcid
                beRemoteType:(NSUInteger)type
                     brandId:(NSUInteger)brandId
                     cmd_key:(NSString *)key
                   cmd_value:(NSString *)cmd
                  completion:(void (^__nullable)(id result, NSError *error))completion;

/**
 发码给遥控中心

 @param ykcDevice 遥控中心对象
 @param datas 遥控码对象数组
 @param completion 发码结果回调
 */
+ (void)sendRemoteWithYKC:(id)ykcDevice
                    datas:(NSArray *)datas
               completion:(void (^__nullable)(BOOL result, NSError *error))completion;


/**
 发空调码给摇控中心

 @param ykcId 遥控中心 id
 @param remoteDevice 遥控器对象
 @param mode 空调模式
 @param temp 温度
 @param speed 风速
 @param windU 上下扫风级别
 @param windL 左右扫风级别
 @param asteriskDatas 匹配数据，可选
 @param completion 发码结果回调
 */
+ (void)sendRemoteKeyWithYKCId:(NSString *)ykcId
                  remoteDevice:(YKRemoteDevice *)remoteDevice
                      withMode:(NSString *)mode
                          temp:(NSUInteger)temp
                         speed:(NSUInteger)speed
                         windU:(NSUInteger)windU
                         windL:(NSUInteger)windL
                 asteriskDatas:(nullable NSArray *)asteriskDatas
                    completion:(void (^__nullable)(BOOL result, NSError *error))completion;


/**
 透传数据接口

 @param ykcId 遥控中心 id
 @param hexData 透传数据（16进制格式）
 @param completion 结果回调
 */
+ (void)sendTrunkWithYKCId:(NSString *)ykcId
                      data:(NSData *)hexData
                completion:(void (^__nullable)(id result, NSError *error))completion;

/**
 注册接收透传数据监听

 @param completion 结果回调
 */
+ (void)registerReceiveTrunkDataHandler:(void (^__nullable)(NSData *trunkData))completion;

/**
 开始学习
 
 @param ykcId 遥控中心 id
 @param completion 学习结果回调
 */
+ (void)learnCodeWithYKCId:(NSString *)ykcId
                completion:(void (^)( BOOL result, NSString * __nullable code))completion;


/**
 停止学习。
 可以退出红外和射频学习状态。
 
 @param ykcId 遥控中心 id
 */
+ (void)stopLearnCode:(NSString *)ykcId;


/**
 开始学习 433/315 码
 
 @param ykcId 遥控中心 id
 @param completion 学习结果回调
 */
+ (void)learnRFCodeWithYKCId:(NSString *)ykcId
                  completion:(void (^)( BOOL result, NSString * __nullable code))completion;


/**
 发送 433/315 码

 @param ykcId 遥控中心 id
 @param code 遥控码
 @param completion 结果回调
 */
+ (void)sendRFCodeWithYKCId:(NSString *)ykcId
                       code:(NSString *)code
                 completion:(void (^__nullable)(BOOL result, NSError *error))completion;

/**
 切换遥控中心LED灯开关
 
 @param ykcId 遥控中心 id
 */
+ (void)toogleLEDWithYKCId:(NSString *)ykcId;

#pragma mark - 用户管理
/**
 匿名登陆
 
 @param completion 登陆结果回调
 */
- (void)anonymousLogin:(void (^__nullable)(NSError *result, NSString *uid, NSString *token))completion;


/**
 使用用户名密码登陆，需使用注册成功的用户名、密码进行登录

 注意：此方法仅支持普通用户名登录，需要使用手机或邮箱登录，请使用 -login:password:accountType:handler: 方法
 
 @param username 用户名
 @param password 密码
 @param completion 登陆结果回调
 */
- (void)login:(NSString *)username
     password:(NSString *)password
      handler:(void (^__nullable)(NSError *result, NSString *uid, NSString *token))completion;

/**
 使用用户名密码登陆，需使用注册成功的用户名、密码进行登录
 
 @param username 用户名
 @param password 密码
 @param accountType 用户类型，详细见 YKUserAccountType 枚举定义。注册手机号时，此参数指定为手机用户，注册邮箱时，此参数指定为邮箱用户，注册普通用户名时，此参数指定为普通用户
 @param completion 登陆结果回调
 */
- (void)login:(NSString *)username
     password:(NSString *)password
  accountType:(YKUserAccountType)accountType
      handler:(void (^__nullable)(NSError *result, NSString *uid, NSString *token))completion;

/**
 使用用户名密码注册
 注意：使用此方式注册不支持找回密码
 
 @param username 用户名，普通用户名
 @param password 密码
 @param completion 注册结果回调
 */
- (void)reg:(NSString *)username
   password:(NSString *)password
    handler:(void (^__nullable)(NSError *result, NSString *uid, NSString *token))completion;

/**
 用户注册，需指定用户类型注册。手机用户的用户名是手机号，邮箱用户的用户名是邮箱、普通用户的用户名可以是普通用户名
 使用此方式注册支持找回密码
 
 @param username 用户名，普通用户名
 @param password 密码
 @param accountType 用户类型，详细见 YKUserAccountType 枚举定义。注册手机号时，此参数指定为手机用户，注册邮箱时，此参数指定为邮箱用户，注册普通用户名时，此参数指定为普通用户
 @param code 手机短信验证码。短信验证码注册后就失效了，不能被再次使用
 @param completion 注册结果回调
 */
- (void)reg:(NSString *)username
   password:(NSString *)password
 verifyCode:(NSString *)code
accountType:(YKUserAccountType)accountType
    handler:(void (^__nullable)(NSError *result, NSString *uid, NSString *token))completion;


/**
 通过手机号请求短信验证码

 注意，验证短信验证码后，验证码就失效了，无法再用于手机号注册
 
 @param phone 手机号
 @param completion 结果回调
 */
+ (void)sendPhoneSMSCode:(NSString *)phone
              completion:(void (^)(NSError *result, NSString *token))completion;


/**
 重置密码，找回密码

 @param username 待重置密码的手机号或邮箱
 @param code 重置手机用户密码时需要使用手机短信验证码（通过 sendPhoneSMSCode:completion: 方法获取）
 @param newPassword 新密码
 @param accountType 用户类型，详细见 YKUserAccountType 枚举定义。待重置密码的用户名是手机号时，此参数指定为手机用户，待重置密码的用户名是邮箱时，此参数指定为邮箱用户
 @param completion 结果回调
 */
+ (void)resetPassword:(NSString *)username
           verifyCode:(NSString *)code
          newPassword:(NSString *)newPassword
          accountType:(YKUserAccountType)accountType
           completion:(void (^)(NSError *__nullable result))completion;


/**
 将匿名用户转为普通注册用户

 @param username 要注册用户的用户名，必须未被使用
 @param token 匿名用户令牌
 @param password 要注册用户的密码
 @param completion 结果回调
 */
- (void)transAnonymousUser:(NSString *)username
                     token:(NSString *)token
                  password:(NSString *)password
                   handler:(void (^)(NSError * _Nullable))completion;

/**
 获取 SDK 版本号

 @return SDK 版本号
 */
+ (NSString *)sdkVersion;


/**
 关闭 SDK 日志

 @param disable YES 为关闭 SDK 日志，NO 为打开日志，默认为打开
 */
+ (void)disableSDKLog:(BOOL)disable;

@end

NS_ASSUME_NONNULL_END
