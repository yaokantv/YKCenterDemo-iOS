//
//  GizSchedulerInfo.h
//  GizWifiSDK
//
//  Created by GeHaitong on 16/8/9.
//  Copyright © 2016年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GizWifiDefinitions.h"

@interface GizSchedulerInfo : NSObject

- (GizSchedulerInfo *)init;

@property (strong, nonatomic, readonly) NSString *sid;
@property (strong, nonatomic, readonly) NSString *createdDateTime;
/*
 定时任务的执行状态（预留，暂不实现）
 */
@property (assign, nonatomic, readonly) BOOL status;

@property (strong, nonatomic) NSString *date;
@property (strong, nonatomic) NSString *time;
@property (strong, nonatomic) NSString *remark;
@property (strong, nonatomic) NSArray *taskList;
@property (assign, nonatomic) GizScheduleRepeatRule repeatRule;
@property (strong, nonatomic) NSArray *weekdays;
@property (strong, nonatomic) NSArray *monthDays;
@property (assign, nonatomic) NSInteger repeatCount;

@end
