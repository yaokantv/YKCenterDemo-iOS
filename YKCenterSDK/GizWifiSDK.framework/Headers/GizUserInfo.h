//
//  GizUserInfo.h
//  GizWifiSDK
//
//  Created by Tom on 15/11/3.
//  Copyright © 2015年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDefinitions.h>

/**
 GizUserInfo 类为开发者提供用户信息存取属性
 */
@interface GizUserInfo : NSObject
/**
 NSString类型。用户登录后得到的uid，提供get方法
 */
@property (strong, nonatomic, readonly) NSString * _Nullable uid;
/**
 NSString类型。用户名：手机号或者邮箱，只读不可写
 */
@property (strong, nonatomic, readonly) NSString * _Nullable username;
/**
 NSString类型。用户邮箱，只读不可写
 */
@property (strong, nonatomic, readonly) NSString * _Nullable email;
/**
 NSString类型。用户手机号，只读不可写
 */
@property (strong, nonatomic, readonly) NSString * _Nullable phone;
/**
 BOOL类型。是否为匿名用户，只读不可写
 */
@property (assign, nonatomic, readonly) BOOL isAnonymous;
/**
 NSString类型。此变量只用于表示用户绑定设备的时间
 */
@property (strong, nonatomic, readonly) NSString * _Nullable deviceBindTime;
/**
 NSString类型。用户昵称，可写
 */
@property (strong, nonatomic) NSString * _Nullable name;
/**
 GizUserGenderType类型。用户性别，可写
 @see GizUserGenderType
 */
@property (assign, nonatomic) GizUserGenderType userGender;
/**
 NSDate类型。用户生日，可写
 */
@property (strong, nonatomic) NSDate * _Nullable birthday;
/**
 NSString类型。用户家庭住址，可写
 */
@property (strong, nonatomic) NSString * _Nullable address;
/**
 NSString类型。用户的语言环境，只读不可写
 */
@property (strong, nonatomic, readonly) NSString * _Nonnull lang;
/**
 NSString类型。用户的备注信息，可写
 */
@property (strong, nonatomic) NSString * _Nullable remark;

/** @deprecated 此变量已废弃，不再提供支持。替代变量为 userGender */
@property (assign, nonatomic) XPGUserGenderType gender DEPRECATED_MSG_ATTRIBUTE("Please use userGender instead") NS_SWIFT_UNAVAILABLE("");

@end
