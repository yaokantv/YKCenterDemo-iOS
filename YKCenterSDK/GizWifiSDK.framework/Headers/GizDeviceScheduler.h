//
//  GizDeviceScheduler.h
//  GizWifiSDK
//
//  Created by Tom on 16/8/9.
//  Copyright © 2016年 gizwits. All rights reserved.
//

#import <GizWifiSDK/GizDeviceSchedulerSuper.h>
#import <GizWifiSDK/GizDeviceSchedulerGateWay.h>

@class GizDeviceScheduler;

@protocol GizDeviceSchedulerDelegate <NSObject>
@optional

/**
 定时任务信息更新回调。修改定时任务信息、定时任务信息变化上报使用该回调接口
 @param scheduler 触发回调的定时任务
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS表示成功，其他为失败
 @see 回调 [GizDeviceScheduler editSchedulerInfo:token:]
 */
- (void)scheduler:(GizDeviceScheduler * _Nullable)scheduler didUpdateSchedulerInfo:(NSError * _Nonnull)result;

/**
 开启定时任务结果回调
 @param scheduler 触发回调的定时任务
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param sn 执行开启或关闭操作的操作序号
 @see 触发函数 [GizDeviceScheduler enableScheduler:sn:]
 @see GizWifiErrorCode
 */
- (void)scheduler:(GizDeviceScheduler * _Nullable)scheduler didEnableScheduler:(NSError * _Nonnull)result sn:(int)sn;

@end

/*
 GizDeviceScheduler类是基于设备的定时任务类，可设置一次性定时任务、按月重复的定时任务、按周重复的定时任务。
 一次性定时任务是指只执行一次定时任务，按月重复定时任务是指在每月特定日期执行定时任务，按周重复定时任务是指在每周特定时间执行定时任务。
 */
@interface GizDeviceScheduler : GizDeviceSchedulerSuper

/**
GizDeviceScheduler构造函数，用于在云端创建一次性定时任务
@param attrs 定时任务操作键值对字典：{操作名字: 操作值}，请注意不支持透传数据。此参数不能填nil或空字典
@param date 定时任务的预设日期，格式形如：1990-10-03。定时任务将在预设日期这一天到达时执行。此参数不能填nil或空串，如果填写了过去日期或者不符合约定格式，无法在云端创建定时任务
@param time 定时任务的预设时间，24小时制，格式形如：07:08。定时任务将在预设时间到达时执行。此参数不能填nil或空串，必须符合约定格式，否则无法在云端创建定时任务
@param enabled 定时任务是否开启。true表示开启，false表示不开启
@param remark 定时任务备注信息。此参数可选填，可填nil
*/
+ (instancetype _Nullable)schedulerOneTime:(NSDictionary <NSString *, id>* _Nonnull)attrs date:(NSString * _Nonnull)date time:(NSString * _Nonnull)time enabled:(BOOL)enabled remark:(NSString * _Nullable)remark;

/**
 GizDeviceScheduler构造函数，用于在云端创建按周重复定时任务
 @param attrs 定时任务操作键值对字典：{操作名字: 操作值}，请注意不支持透传数据。此参数不能为nil或空字典
 @param time 定时任务的预设时间，24小时制，格式形如：07:08。此参数不能填nil或空串，必须符合约定格式，否则无法在云端创建定时任务。定时任务将在预设时间到达时执行
 @param weekDays 按周重复，GizScheduleWeekday数组。定时任务可以预设为每周的某几天重复执行。此参数不能填nil或空数组，数组中重复的值会被合并，无效值会被滤除，如果滤除后数组大小为0按空数组处理
 @param enabled 定时任务是否开启。true表示开启，false表示不开启
 @param remark 定时任务备注信息。此参数可选填，可填nil
 */
+ (instancetype _Nullable)schedulerWeekRepeat:(NSDictionary <NSString *, id>* _Nonnull)attrs time:(NSString * _Nonnull)time weekDays:(NSArray <NSNumber *>* _Nonnull)weekDays enabled:(BOOL)enabled remark:(NSString * _Nullable)remark;

/**
 GizDeviceScheduler构造函数，用于在云端创建按天重复定时任务
 @param attrs 定时任务操作键值对字典：{操作名字: 操作值}，请注意不支持透传数据。此参数不能为nil或空字典
 @param time 定时任务的预设时间，24小时制，格式形如：07:08。此参数不能填nil或空串，必须符合约定格式，否则无法创建定时任务。定时任务将在预设时间到达时执行
 @param monthDays 按天重复，GizScheduleWeekday数组。定时任务可以预设为每周的某几天重复执行。此参数不能填nil或空数组，数组中重复的值会被合并，无效值会被滤除，如果滤除后数组大小为0按空数组处理
 @param enabled 定时任务是否开启。true表示开启，false表示不开启
 @param remark 定时任务备注信息。此参数可选填，可传nil
 */
+ (instancetype _Nullable)schedulerDayRepeat:(NSDictionary <NSString *, id>* _Nonnull)attrs time:(NSString * _Nonnull)time monthDays:(NSArray <NSNumber *>* _Nonnull)monthDays enabled:(BOOL)enabled remark:(NSString * _Nullable)remark;

/** 云端定时任务的创建时间 */
@property (strong, nonatomic, readonly) NSString * _Nonnull createdDateTime;
/** 云端定时任务的备注信息 */
@property (strong, nonatomic, getter=lastRemark) NSString * _Nullable remark;//只用于普通设备
/** 云端定时任务预设的起始时间，格式与date相同 */
@property (strong, nonatomic, getter=lastStartDate) NSString * _Nullable startDate;//只用于普通设备
/** 云端定时任务预设的结束时间，格式与date相同 */
@property (strong, nonatomic, getter=lastEndDate) NSString * _Nullable endDate;//只用于普通设备
/** 云端定时任务操作项（不支持透传数据） */
@property (strong, nonatomic, getter=lastAttrs) NSDictionary <NSString *, id>* _Nullable attrs;//只用于普通设备

/**
 GizDeviceScheduler委托
 @see GizDeviceSchedulerDelegate
 */
@property (weak, nonatomic) id<GizDeviceSchedulerDelegate> _Nullable delegate;

/**
 修改定时任务信息，此接口可用于修改云端或中控的定时任务信息。请注意，必须要先修改对应的变量值，然后再调用此接口完成修改。修改成功时返回最新的定时任务信息，修改失败时返回错误信息
 @param uid 用户uid。此参数必填，不能填空串或无效值
 @param token 用户token。此参数必填，不能填空串或无效值
 @param type 定时任务类型，GizSchedulerType枚举，详细见变量schedulerType说明。此参数不能填无效值
 @see 回调 [GizDeviceSchedulerDelegate scheduler:didUpdateSchedulerInfo:]
 */
- (void)editSchedulerInfo:(NSString * _Nonnull)uid token:(NSString * _Nonnull)token type:(GizSchedulerType)type;

/**
 开启或关闭定时任务。定时任务创建时是默认开启的，在创建后可以关闭或开启
 @param enable 开启或关闭
 @param sn 执行开启的命令序号。如果App需要对应操作执行顺序，sn就要指定为一个正整数。如果App不关心操作执行顺序，sn填0
 @see 回调 [GizDeviceSchedulerDelegate didEnableScheduler:result:sn:]
 */
- (void)enableScheduler:(BOOL)enable sn:(int)sn;

/**
 @deprecated 此接口已废弃，将在2.09.09版本后不再提供支持，请尽快替换对应的构造函数
 @see [GizDeviceScheduler initSchedulerOneTime:date:time:enabled:remark:startDate:endDate:]
 @see [GizDeviceScheduler initSchedulerWeekRepeat:time:weekDays:enabled:remark:startDate:endDate:]
 @see [GizDeviceScheduler initSchedulerMonthRepeat:time:monthDays:enabled:remark:startDate:endDate:]
 */
- (GizDeviceScheduler * _Nullable)init DEPRECATED_MSG_ATTRIBUTE("Please use initSchedulerOneTime:date:time:enabled:remark:startDate:endDate:, initSchedulerWeekRepeat:time:weekDays:enabled:remark:startDate:endDate:, initSchedulerMonthRepeat:time:monthDays:enabled:remark:startDate:endDate: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持。 */
@property (assign, nonatomic) GizScheduleRepeatRule repeatRule DEPRECATED_MSG_ATTRIBUTE("No longer supported.") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** @deprecated 此接口已废弃，不再提供支持。 */
@property (assign, nonatomic) NSInteger repeatCount DEPRECATED_MSG_ATTRIBUTE("No longer supported.") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");
/** 修改定时任务是否开启。true表示开启，false表示关闭 */
- (void)setEnabled:(BOOL)enabled DEPRECATED_MSG_ATTRIBUTE("Please use enableScheduler:sn: instead") NS_EXTENSION_UNAVAILABLE_IOS("") NS_SWIFT_UNAVAILABLE("");

@end

