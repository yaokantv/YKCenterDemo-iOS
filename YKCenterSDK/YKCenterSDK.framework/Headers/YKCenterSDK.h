//
//  YKCenterSDK.h
//  YKCenterSDK
//
//  Created by Don on 2017/1/12.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GizWifiDevice.h"
#import <YKCenterSDK/YKCenterSDKHeader.h>

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
 绑定遥控中心 YKC，完成后使用 block 回调返回结果。

 @param ssid Wi-Fi 的 SSID 名称
 @param password Wi-Fi 的密码
 @param completion 绑定遥控中心设备完成的回调。如果绑定出错，返回 error 对象；如果有连接成功，error 为空。
 */
+ (void)bindYKCWithSSID:(NSString *)ssid
               password:(nullable NSString *)password
             completion:(void (^__nullable)(NSError *error))completion;


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
 获取遥控器设备

 @param ykcId           遥控中心 id
 @param remoteDeviceId  遥控器设备 id
 @param completion      回调返回遥控器
 */
+ (void)fetchRemoteDeivceWithYKCId:(NSString *)ykcId
                    remoteDeviceId:(NSString *)remoteDeviceId
                        completion:(void (^__nullable)(YKRemoteDevice *remote, NSError *error))completion;


/**
 发码给遥控中心

 @param ykcId 遥控中心 id
 @param datas 遥控码对象数组
 @param completion 发码结果回调
 */
+ (void)sendRemoteWithYKCId:(NSString *)ykcId
                      datas:(NSArray *)datas
        completion:(void (^__nullable)(id result, NSError *error))completion;

@end

NS_ASSUME_NONNULL_END
