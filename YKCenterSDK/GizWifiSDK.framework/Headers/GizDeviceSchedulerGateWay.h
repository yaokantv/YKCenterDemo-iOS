//
//  GizDeviceSchedulerGateWay.h
//  GizWifiSDK
//
//  Created by Tom on 2017/6/19.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <GizWifiSDK/GizDeviceSchedulerSuper.h>
#import <GizWifiSDK/GizDeviceSchedulerTask.h>

@class GizDeviceSchedulerGateway;

@protocol GizDeviceSchedulerGatewayDelegate <NSObject>
@optional

- (void)scheduler:(GizDeviceSchedulerGateway * _Nullable)scheduler didUpdateSchedulerInfo:(NSError * _Nonnull)result;
- (void)scheduler:(GizDeviceSchedulerGateway * _Nullable)scheduler didUpdateSchedulerTasks:(NSError * _Nonnull)result taskList:(NSArray <GizDeviceSchedulerTask *>* _Nonnull)taskList;

- (void)scheduler:(GizDeviceSchedulerGateway * _Nullable)scheduler didEnableScheduler:(NSError * _Nonnull)result sn:(int)sn;
- (void)scheduler:(GizDeviceSchedulerGateway * _Nullable)scheduler didUpdateSchedulerEnableStatus:(NSError * _Nonnull)result enableStatus:(BOOL)enableStatus;

@end

@interface GizDeviceSchedulerGateway : GizDeviceSchedulerSuper

- (instancetype _Nullable)init NS_UNAVAILABLE;

/**
 GizDeviceScheduler构造函数，用于在中控上创建延时任务
 @param delayTime 延时时间，单位秒。延时任务将在延时时间倒计时为0时执行。如果填0，则任务下发后马上执行
 */
+ (instancetype _Nullable)schedulerDelayByGateway:(unsigned int)delayTime name:(NSString * _Nullable)name;

/**
 GizDeviceScheduler构造函数，用于在中控上创建一次性定时任务
 @param date 定时任务的预设日期，格式形如：1990-10-03。定时任务将在预设日期这一天到达时执行。此参数不能填nil或空串，如果填写了过去日期或者不符合约定格式，无法在中控上创建定时任务
 @param time 定时任务的预设时间，24小时制，格式形如：07:08。定时任务将在预设时间到达时执行。此参数不能填nil或空串，必须符合约定格式，否则无法在中控上创建定时任务
 @param enabled 定时任务是否开启。true表示开启，false表示不开启
 @param name 定时任务名称。此参数可选填，可填nil
 */
+ (instancetype _Nullable)schedulerOneTime:(NSString * _Nonnull)date time:(NSString * _Nonnull)time enabled:(BOOL)enabled name:(NSString * _Nullable)name;

/**
 GizDeviceScheduler构造函数，用于在中控上创建按周重复定时任务
 @param time 定时任务的预设时间，24小时制，格式形如：07:08。此参数不能填nil或空串，必须符合约定格式。定时任务将在预设时间到达时执行
 @param weekDays 按周重复，GizScheduleWeekday数组。定时任务可以预设为每周的某几天重复执行。此参数不能填nil或空数组，数组中重复的值会被合并，无效值会被滤除，如果滤除后数组大小为0按空数组处理
 @param enabled 定时任务是否开启。true表示开启，false表示不开启
 @param name 定时任务名称。此参数可选填，可填nil
 */
+ (instancetype _Nullable)schedulerWeekRepeat:(NSString * _Nonnull)time weekDays:(NSArray <NSNumber *>* _Nonnull)weekDays enabled:(BOOL)enabled name:(NSString * _Nullable)name;

/**
 GizDeviceScheduler构造函数，用于在云端创建按天重复定时任务
 @param time 定时任务的预设时间，24小时制，格式形如：07:08。此参数不能填nil或空串，必须符合约定格式，否则无法创建定时任务。定时任务将在预设时间到达时执行
 @param monthDays 按天重复，NSNumber数组，在1～31范围内选择。定时任务可以预设为每月的某几天重复执行。此参数不能填nil或空数组，数组中重复的值会被合并，无效值会被滤除，如果滤除后数组大小为0按空数组处理
 @param enabled 定时任务是否开启。true表示开启，false表示不开启
 @param name 定时任务名称。此参数可选填，可传nil
 */
+ (instancetype _Nullable)schedulerDayRepeat:(NSString * _Nonnull)time monthDays:(NSArray <NSNumber *>* _Nonnull)monthDays enabled:(BOOL)enabled name:(NSString * _Nullable)name;

/**
 GizDeviceSchedulerGateway委托
 @see GizDeviceSchedulerGatewayDelegate
 */
@property (weak, nonatomic) id<GizDeviceSchedulerGatewayDelegate> _Nullable delegate;

/** 中控延时任务当前剩余的延时时间，单位秒 */
@property (assign, nonatomic, readonly) unsigned int delayTime;
/** 中控任务项列表，GizDeviceSchedulerTask对象数组 */
@property (strong, nonatomic, readonly) NSArray <GizDeviceSchedulerTask *>* _Nonnull taskList;
/** 中控定时任务名称 */
@property (strong, nonatomic, readonly) NSString * _Nullable name;

/** 修改延时时间 */
- (void)setDelayTime:(unsigned int)delayTime;
/** 修改中控定时任务名称 */
- (void)setName:(NSString * _Nullable)name;

/**
 修改定时任务信息，此接口可用于修改云端或中控的定时任务信息。请注意，必须要先修改对应的变量值，然后再调用此接口完成修改。修改成功时返回最新的定时任务信息，修改失败时返回错误信息
 @param type 定时任务类型，GizSchedulerType枚举，详细见变量schedulerType说明。此参数不能填无效值
 @see 回调 [GizDeviceSchedulerDelegate scheduler:didUpdateSchedulerInfo:]
 */
- (void)editSchedulerInfo:(GizSchedulerType)type;

/**
 修改任务项列表，此接口只支持中控。修改成功时返回最新的定时任务项列表，修改失败时返回错误信息
 @param tasks 待修改的定时任务项列表，GizDeviceSchedulerTask对象数组。这个列表必须能符合预期的修改结果，列表中应包括新添加的、待修改的、不修改的，如果有待删除的要移除掉。此参数不能填nil或空数组
 @see 回调 [GizDeviceSchedulerDelegate didUpdateTasks:result:taskList:]
 */
- (void)editSchedulerTasks:(NSArray <GizDeviceSchedulerTask *>* _Nullable)tasks;

/**
 同步更新任务项列表，此接口只支持中控。需要与中控同步获取最新的任务项列表时调用此接口。同步成功时返回最新的定时任务项列表，同步失败时返回错误信息
 @see 回调 [GizDeviceSchedulerDelegate didUpdateTasks:result:taskList:]
 */
- (void)updateSchedulerTasks;

/**
 开启或关闭定时任务，此接口只支持中控。定时任务创建时是默认开启的，在创建后也可以关闭或开启
 @param enable 开启或关闭
 @param sn 执行开启的命令序号。如果App需要对应操作执行顺序，sn就要指定为一个正整数。如果App不关心操作执行顺序，sn填0
 @see 回调 [GizDeviceSchedulerDelegate didEnableScheduler:result:sn:]
 */
- (void)enableScheduler:(BOOL)enable sn:(int)sn;

/**
 更新定时任务的开启状态，此接口只支持中控
 @see [GizDeviceScheduler didUpdateSchedulerEnableStatus:result:enableStatus:]
 @see GizWifiErrorCode
 */
- (void)updateSchedulerEnableStatus;

@end
