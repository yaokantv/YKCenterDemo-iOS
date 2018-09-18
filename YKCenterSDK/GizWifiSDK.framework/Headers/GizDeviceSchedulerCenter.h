//
//  GizDeviceSchedulerCenter.h
//  GizWifiSDK
//
//  Created by Tom on 2016/12/5.
//  Copyright © 2016年 gizwits. All rights reserved.
//

#import <GizWifiSDK/GizDeviceScheduler.h>

@class GizWifiDevice;

@protocol GizDeviceSchedulerCenterDelegate <NSObject>
@optional

/*
 定时任务列表回调接口。创建定时任务、修改定时任务信息、删除定时任务、同步更新定时任务列表都使用该回调接口。
 @param schedulerOwner 触发回调的 GizWifiDevice设备对象
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，此时schedulerList为定时任务列表；其他为失败，此时schedulerList大小为0
 @param schedulerList 设备定时任务列表。GizWifiDevice 对象数组
 @see 触发函数：[GizDeviceSchedulerCenter createScheduler:token:schedulerOwner:scheduler:];
 [GizDeviceSchedulerCenter deleteScheduler:token:schedulerOwner:schedulerID:];
 [GizDeviceSchedulerCenter editScheduler:token:schedulerOwner:scheduler:];
 [GizDeviceSchedulerCenter updateSchedulers:token:schedulerOwner:];
 @see GizWifiErrorCode
 */
- (void)didUpdateSchedulers:(GizWifiDevice * _Nullable)schedulerOwner result:(NSError * _Nonnull)result schedulerList:(NSArray <GizDeviceSchedulerSuper *>* _Nullable)schedulerList;

@end

/*
 GizDeviceSchedulerCenter类为 APP 开发者提供设备定时任务管理功能，管理用户在设备上设置的定时任务。
 */
@interface GizDeviceSchedulerCenter : NSObject

/**
 获取云端定时任务列表，这个列表缓存了GizDeviceScheduler对象
 @param schedulerOwner 执行定时任务的设备，此参数不能填nil
 @return 定时任务列表。参数值为nil或无效设备时返回空数组
 */
+ (NSArray <GizDeviceScheduler *>* _Nullable)getSchedulerListCloud:(GizWifiDevice * _Nonnull)schedulerOwner;

/**
 获取中控设备下的定时任务列表，这个列表缓存了GizDeviceSchedulerGateway对象
 @param schedulerOwner 中控设备，此参数不能填nil
 @return 定时任务列表。参数值为nil或无效设备时返回空数组
 */
+ (NSArray <GizDeviceSchedulerGateway *>* _Nullable)getSchedulerListGateway:(GizWifiDevice * _Nonnull)schedulerOwner;

/*
 设备定时任务列表。GizWifiDevice 对象数组
 @param delegate 定时任务委托
 */
@property (class, weak, nonatomic) id <GizDeviceSchedulerCenterDelegate> _Nullable delegate;

/**
 创建定时任务。创建成功会被分配一个定时任务ID，同时通过回调接口didUpdateSchedulers给App返回定时任务列表，创建失败时返回错误信息
 @param uid 登录用户的ID。创建云端定时任务时此参数必填，空串和无效值无法创建云端定时任务；创建中控定时任务时此参数必须填nil
 @param token 登录用户的token。创建云端定时任务时此参数必填，空串和无效值无法创建云端定时任务；创建中控定时任务时此参数必须填nil
 @param schedulerOwner 管理定时任务的设备，此参数必填，填nil无法创建定时任务
 @param scheduler 定时任务对象，用于填写定时任务内容的，此参数不能填nil。云端定时任务对象通过GizDeviceScheduler类构造函数创建，中控定时任务对象通过GizDeviceSchedulerGateway类构造函数创建。GizDeviceScheduler类有三种对象构造方法，GizDeviceSchedulerGateway有四种对象构造方法，App根据需要选择对应的方法创建对象
 @param schedulerTasks 任务项列表，用于填写中控定时任务要执行的操作，GizDeviceSchedulerTask对象数组。此参数为选填，可填nil。App可在创建时预设，也可以在创建成功后填写或修改。云端定时任务不需要填写此参数
 @see 对应的回调接口：[GizDeviceSchedulerCenterDelegate didUpdateSchedulers:result:schedulerList:]
 */
+ (void)createScheduler:(NSString * _Nullable)uid token:(NSString * _Nullable)token schedulerOwner:(GizWifiDevice * _Nonnull)schedulerOwner scheduler:(GizDeviceSchedulerSuper * _Nonnull)scheduler schedulerTasks:(NSArray <GizDeviceSchedulerTask *>* _Nullable)schedulerTasks;

/**
 删除设备定时任务。删除成功时通过回调接口didUpdateSchedulers给App返回最新的定时任务列表，删除失败时返回错误信息
 @param uid 用户uid。删除云端定时任务时此参数必填，空串和无效值无法创建云端定时任务；删除中控定时任务时此参数选填，可填nil
 @param token 用户token。删除云端定时任务时此参数必填，空串和无效值无法创建云端定时任务；删除中控定时任务时此参数选填，可填nil
 @param schedulerOwner 管理定时任务的设备，此参数必填，填nil无法删除定时任务
 @param scheduler 待删除的定时任务对象，是从定时任务列表中得到的GizDeviceScheduler或GizDeviceSchedulerGateway对象，此参数必填，不能填nil
 @see 对应的回调接口：[GizDeviceSchedulerCenterDelegate didUpdateSchedulers:result:schedulerList:]
 */
+ (void)deleteScheduler:(NSString * _Nullable)uid token:(NSString * _Nullable)token schedulerOwner:(GizWifiDevice * _Nonnull)schedulerOwner scheduler:(GizDeviceSchedulerSuper * _Nonnull)scheduler;

/*
 同步更新设备定时任务列表。App调用此接口可以与当前设备上所有定时任务列表保持同步
 @param uid 用户uid
 @param token 用户token
 @param schedulerOwner 同步更新定时任务列表的设备对象
 @see 对应的回调接口：[GizDeviceSchedulerCenterDelegate didUpdateSchedulers:result:schedulerList:];
 */
+ (void)updateSchedulers:(NSString * _Nullable)uid token:(NSString * _Nullable)token schedulerOwner:(GizWifiDevice * _Nonnull)schedulerOwner;

/** @deprecated 此接口已废弃，替代接口：[createScheduler :token:schedulerOwner:scheduler:schedulerTasks:] */
+ (void)createScheduler:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token schedulerOwner:(GizWifiDevice * _Null_unspecified)schedulerOwner scheduler:(GizDeviceScheduler * _Null_unspecified)scheduler DEPRECATED_MSG_ATTRIBUTE("Please use createScheduler:token:schedulerOwner:scheduler:schedulerTasks: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，替代接口：[GizDeviceScheduler deleteScheduler:token:schedulerOwner:scheduler:] */
+ (void)deleteScheduler:(NSString * _Nullable)uid token:(NSString * _Nullable)token schedulerOwner:(GizWifiDevice * _Nonnull)schedulerOwner schedulerID:(NSString * _Nonnull)schedulerID DEPRECATED_MSG_ATTRIBUTE("Please use deleteScheduler:token:schedulerOwner:scheduler: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，替代接口：[GizDeviceScheduler editSchedulerInfo:token:] */
+ (void)editScheduler:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token schedulerOwner:(GizWifiDevice * _Null_unspecified)schedulerOwner schedulerID:(NSString * _Null_unspecified)schedulerID DEPRECATED_MSG_ATTRIBUTE("Please use editSchedulerInfo:token:type: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");

@end
