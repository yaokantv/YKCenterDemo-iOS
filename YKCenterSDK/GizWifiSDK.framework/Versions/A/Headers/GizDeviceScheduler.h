//
//  GizDeviceScheduler.h
//  GizWifiSDK
//
//  Created by GeHaitong on 16/8/9.
//  Copyright © 2016年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDefinitions.h>

@class GizWifiDevice;

@protocol GizDeviceSchedulerDelegate <NSObject>
@optional

- (void)didUpdateTasks:(NSString *)schedulerID result:(NSError *)result taskList:(NSArray *)taskList;
- (void)didEnableScheduler:(NSString *)schedulerID result:(NSError *)result sn:(int)sn;
- (void)didUpdateSchedulerEnableStatus:(NSString *)schedulerID result:(NSError *)result enableStatus:(BOOL)enableStatus;

@end

/*
 GizDeviceScheduler类是基于设备的定时任务类，可设置一次性定时任务、按月重复的定时任务、按周重复的定时任务。
 一次性定时任务是指只执行一次定时任务，按月重复定时任务是指在每月特定日期执行定时任务，按周重复定时任务是指在每周特定时间执行定时任务。
 */
@interface GizDeviceScheduler : NSObject

- (GizDeviceScheduler *)init;

@property (weak, nonatomic, readonly) GizWifiDevice *schedulerOwner;
/*
 NSString类型，只读不可写。定时任务ID，定时任务创建成功时会被分配一个ID
 */
@property (strong, nonatomic, readonly) NSString *schedulerID;
/*
 NSString类型，只读不可写。定时任务的创建时间
 */
@property (strong, nonatomic, readonly) NSString *createdDateTime;
@property (strong, nonatomic, readonly) NSArray *taskList;
/*
 NSString类型，可读写。定时任务的执行日期，年月日以“－”符号分割，例如：2017-01-30。此变量默认值为nil
 */
@property (strong, nonatomic) NSString *date;
/*
 NSString类型，可读写。定时任务的执行时间，24小时制，例如：06:30。无论是一次性定时任务还是按周、按月重复的定时任务，必须指定执行时间，此变量必须有值
 */
@property (strong, nonatomic) NSString *time;
/*
 GizScheduleWeekday枚举类型数组，可读写。此变量为nil，表示定时任务不需要按周重复。需要按周重复时，此变量可填写为一周中的某一天或者某几天，例如：想在周一和周三执行定时任务，就把GizScheduleMonday、GizScheduleWednesday这两个值放到数组里。此变量默认值为nil。
 说明：定时任务是按周重复还是按月重复，只能二选一。如果定时任务是按周重复，则忽略按月重复。例如：weekdays和monthDays都被赋值时，会优先取weekdays的值
 */
@property (strong, nonatomic) NSArray *weekdays;
/*
 NSInteger类型数组，可读写。此变量为nil，表示定时任务不需要按月重复。需要按月重复时，此变量可填写为一个月中的某一天或某几天。例如，想在一个月的1号和15号执行定时任务，可把1、15这两个值放到数组里。此变量默认值为nil。
 说明：定时任务是按周重复还是按月重复，只能二选一。如果定时任务是按月重复，需要把按周重复变量weekdays清空，按月重复才能生效
 */
@property (strong, nonatomic) NSArray *monthDays;
/*
 BOOL类型，可读写。值为TRUE表示启动定时任务，默认值为TRUE
 */
@property (assign, nonatomic) BOOL enabled;
/*
 NSString类型，可读写。定时任务备注信息，默认值为nil
 */
@property (strong, nonatomic) NSString *remark;//只用于普通设备
/*
 NSString类型，可读写。定时任务启动日期，年月日以“－”符号分割。格式为：2017-01-29。默认值为nil
 */
@property (strong, nonatomic) NSString *startDate;//只用于普通设备
/*
 NSString类型，可读写。定时任务启动日期，年月日以“－”符号分割。格式为：2017-01-29。默认值为nil
 */
@property (strong, nonatomic) NSString *endDate;//只用于普通设备
/*
 NSDictionary类型，可读写。定时任务要执行的动作，为数据点名称和值的键值对。定时任务必须指定要执行的动作，否则无法创建定时任务。此变量必须有值
 */
@property (strong, nonatomic) NSDictionary *attrs;//只用于普通设备

@property (strong, nonatomic) NSString *name; //只用于中控设备
@property (assign, nonatomic) BOOL delay; //只用于中控设备

@property (assign, nonatomic) GizScheduleRepeatRule repeatRule DEPRECATED_ATTRIBUTE;
@property (assign, nonatomic) NSInteger repeatCount DEPRECATED_ATTRIBUTE;

@property (weak, nonatomic) id<GizDeviceSchedulerDelegate> delegate;

- (void)editTasks:(NSArray *)tasks;
- (void)updateTasks;
- (void)enableScheduler:(BOOL)enable sn:(int)sn;
- (void)updateSchedulerEnableStatus;

@end
