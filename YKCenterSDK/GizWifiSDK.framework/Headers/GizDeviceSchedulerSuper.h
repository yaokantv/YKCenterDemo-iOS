//
//  GizDeviceSchedulerSuper.h
//  GizWifiSDK
//
//  Created by Tom on 2017/6/19.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDefinitions.h>

@class GizWifiDevice;

@interface GizDeviceSchedulerSuper : NSObject

- (id _Nullable)init NS_UNAVAILABLE;

/** 定时任务ID，是定时任务创建时被分配的唯一标识 */
@property (strong, nonatomic, readonly) NSString * _Nonnull schedulerID;
/** 管理定时任务的设备，是用于创建、删除、维护定时任务信息的 */
@property (weak, nonatomic, readonly) GizWifiDevice * _Nullable schedulerOwner;
/** 定时任务的预设日期，格式形如：1990-10-03。定时任务会在预设日期这一天到达时执行 */
@property (strong, nonatomic, readonly) NSString * _Nullable date;
/** 定时任务的预设时间，24小时制，格式形如：07:08。定时任务会在预设时间到达时执行 */
@property (strong, nonatomic, readonly) NSString * _Nullable time;
/** 按周重复，GizScheduleWeekday数组。定时任务会每周重复执行 */
@property (strong, nonatomic, readonly) NSArray <NSNumber *>* _Nullable weekdays;
/** 按天重复，NSNumber数组，范围是1～31。定时任务会每月重复执行 */
@property (strong, nonatomic, readonly) NSArray <NSNumber *>* _Nullable monthDays;
/** 定时任务是否开启。YES表示开启，NO表示关闭 */
@property (assign, nonatomic, readonly) BOOL enabled;

/** 修改定时任务日期，格式形如1990-10-03 */
- (void)setDate:(NSString * _Nullable)date;
/** 修改定时任务时间，24小时制格式形如07:08 */
- (void)setTime:(NSString * _Nullable)time;
/** 修改按周重复，GizScheduleWeekday数组 */
- (void)setWeekdays:(NSArray <NSNumber *>* _Nullable)weekdays;
/** 修改按天重复，Integer对象数组，在日期1～31之间选择 */
- (void)setMonthDays:(NSArray <NSNumber *>* _Nullable)monthDays;

/**
 定时任务类型。见GizSchedulerType。每种类型涉及的信息如下：
 如果是云端定时任务，一次性定时任务需要关心schedulerID、createdDateTime、schedulerOwner、date、time、enabled，以及子类GizDeviceScheduler中的attrs，startDate、endDate、remark；
 如果是云端定时任务，按周重复定时任务需要关心schedulerID、createdDateTime、schedulerOwner、time、enabled，以及子类GizDeviceScheduler中的attrs、weekdays，startDate、endDate、remark；
 如果是云端定时任务，按天重复定时任务需要关心schedulerID、createdDateTime、schedulerOwner、time、enabled，以及子类GizDeviceScheduler中的attrs、monthdays，startDate、endDate、remark；
 如果是中控定时任务，延时任务需要关心schedulerID、schedulerOwner，以及子类GizDeviceSchedulerGateway中的delayTime、tasList，name；
 如果是中控定时任务，一次性定时任务需要关心schedulerID、schedulerOwner、date、time、enabled，以及子类GizDeviceSchedulerGateway中的tasList，name；
 如果是中控定时任务，按周重复定时任务需要关心schedulerID、schedulerOwner、time、enabled、weekdays，以及子类GizDeviceSchedulerGateway中的tasList，name；
 如果是中控定时任务，按天重复定时任务需要关心schedulerID、schedulerOwner、time、enabled、monthdays，以及子类GizDeviceSchedulerGateway中的tasList，name
 */
@property (assign, nonatomic, readonly) GizSchedulerType schedulerType;

@end

