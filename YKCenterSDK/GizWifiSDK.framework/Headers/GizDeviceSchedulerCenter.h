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
 获取中控设备下的定时任务列表，这个列表缓存了GizDeviceSchedulerGateWay对象
 @param schedulerOwner 中控设备，此参数不能填nil
 @return 定时任务列表。参数值为nil或无效设备时返回空数组
 */
+ (NSArray <GizDeviceSchedulerGateWay *>* _Nullable)getSchedulerListGateway:(GizWifiDevice * _Nonnull)schedulerOwner;

/*
 设备定时任务列表。GizWifiDevice 对象数组
 @param delegate 定时任务委托
 */
@property (class, weak, nonatomic) id <GizDeviceSchedulerCenterDelegate> _Nullable delegate;

/*
 创建设备定时任务。每一个定时任务创建成功后都会被分配一个定时任务ID，SDK通过回调接口didUpdateSchedulers给App返回创建结果。创建成功时返回最新的定时任务列表，创建失败时返回错误信息
 @param uid 用户uid
 @param token 用户token
 @param schedulerOwner 执行定时任务的设备对象
 @param scheduler 定时任务内容。需要创建一个GizDeviceScheduler类对象，填写好定时任务内容，在接口调用时传这个GizDeviceScheduler对象
 @see 对应的回调接口：[GizDeviceSchedulerCenterDelegate didUpdateSchedulers:result:schedulerList:];
 */
+ (void)createScheduler:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token schedulerOwner:(GizWifiDevice * _Null_unspecified)schedulerOwner scheduler:(GizDeviceScheduler * _Null_unspecified)scheduler DEPRECATED_ATTRIBUTE;
+ (void)createScheduler:(NSString * _Nullable)uid token:(NSString * _Nullable)token schedulerOwner:(GizWifiDevice * _Nonnull)schedulerOwner scheduler:(GizDeviceSchedulerSuper * _Nonnull)scheduler schedulerTasks:(NSArray <GizDeviceSchedulerTask *>* _Nullable)schedulerTasks;

/*
 删除设备定时任务。在定时任务列表中找到要删除的定时任务ID，就可以删除了，SDK通过回调接口didUpdateSchedulers给App返回删除结果。删除成功时返回最新的定时任务列表，删除失败时返回错误信息
 @param uid 用户uid
 @param token 用户token
 @param schedulerOwner 删除定时任务的设备对象
 @param schedulerID 要删除的定时任务ID
 @see 对应的回调接口：[GizDeviceSchedulerCenterDelegate didUpdateSchedulers:result:schedulerList:];
 */
+ (void)deleteScheduler:(NSString * _Nullable)uid token:(NSString * _Nullable)token schedulerOwner:(GizWifiDevice * _Nonnull)schedulerOwner scheduler:(GizDeviceSchedulerSuper * _Nonnull)scheduler;
+ (void)deleteScheduler:(NSString * _Nullable)uid token:(NSString * _Nullable)token schedulerOwner:(GizWifiDevice * _Nonnull)schedulerOwner schedulerID:(NSString * _Nonnull)schedulerID DEPRECATED_ATTRIBUTE;

/*
 修改设备定时任务。要修改的定时任务必须是已经创建过的，App编辑好修改内容后，SDK通过回调接口didUpdateSchedulers给App返回修改结果。修改成功时返回最新的定时任务列表，修改失败时返回错误信息
 @param uid 用户uid
 @param token 用户token
 @param schedulerOwner 修改定时任务的设备对象
 @param schedulerID 要修改的定时任务对象。App在已经得到的定时任务列表中找到要修改的定时任务对象，修改好内容后，在接口调用时传这个对象
 @see 对应的回调接口：[GizDeviceSchedulerCenterDelegate didUpdateSchedulers:result:schedulerList:];
 */
+ (void)editScheduler:(NSString * _Null_unspecified)uid token:(NSString * _Null_unspecified)token schedulerOwner:(GizWifiDevice * _Null_unspecified)schedulerOwner schedulerID:(NSString * _Null_unspecified)schedulerID DEPRECATED_ATTRIBUTE;

/*
 同步更新设备定时任务列表。App调用此接口可以与当前设备上所有定时任务列表保持同步
 @param uid 用户uid
 @param token 用户token
 @param schedulerOwner 同步更新定时任务列表的设备对象
 @see 对应的回调接口：[GizDeviceSchedulerCenterDelegate didUpdateSchedulers:result:schedulerList:];
 */
+ (void)updateSchedulers:(NSString * _Nullable)uid token:(NSString * _Nullable)token schedulerOwner:(GizWifiDevice * _Nonnull)schedulerOwner;

@end
