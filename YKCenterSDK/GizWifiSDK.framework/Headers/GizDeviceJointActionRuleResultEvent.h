//
//  GizDeviceJointActionRuleResultEvent.h
//  GizWifiSDK
//
//  Created by Tom on 2017/6/20.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDefinitions.h>

@class GizWifiDevice;
@class GizDeviceGroup;
@class GizDeviceScene;
@class GizDeviceSchedulerSuper;

@interface GizDeviceJointActionRuleResultEvent : NSObject

/** 联动规则中的中控子设备，如果resultEventType是设备事件，需要关心此变量 */
@property (strong, nonatomic, readonly) GizWifiDevice * _Nullable device;
/** 联动规则中的中控分组，如果resultEventType是组事件，需要关心此变量  */
@property (strong, nonatomic, readonly) GizDeviceGroup * _Nullable group;
/** 设备或组要执行的操作键值对字典：{操作名字: 操作值}，resultEventType是设备或组事件需要关心此变量 */
@property (strong, nonatomic, readonly) NSDictionary <NSString *, id>* _Nullable data;
/** 结果事件类型。设备事件只需要关心device、data；组事件只需要关心group、data */
@property (assign, nonatomic, readonly) GizJointActionRuleEventType resultEventType;
/** 联动规则中的场景，如果resultEventType是场景事件，需要关心此变量 */
@property (strong, nonatomic, readonly) GizDeviceScene * _Nullable scene;
/** 联动规则中的定时任务，如果resultEventType是定时任务事件，需要关心此变量 */
@property (strong, nonatomic, readonly) GizDeviceSchedulerSuper * _Nullable scheduler;
/** 场景或定时任务事件是否开启 */
@property (assign, nonatomic, readonly) BOOL enabled;


- (instancetype _Nullable)init NS_UNAVAILABLE;

/**
 构造函数，用于创建联动规则要执行的设备事件。目前只支持中控
 @param device 设备事件的中控子设备。此参数不能填nil
 @param data 要执行的操作键值对字典：{操作名字: 操作值}，此参数不能填nil或空字典。请注意：无效数据点无法让设备执行命令
 */
+ (id _Nullable)jointActionRuleResultEventByDevice:(GizWifiDevice * _Nonnull)device data:(NSDictionary <NSString *, id>* _Nonnull)data;

/**
 构造函数，用于创建联动规则要执行的组事件。目前只支持中控
 @param group 组事件的中控分组。此参数不能填nil
 @param data 要执行的操作键值对字典：{操作名字: 操作值}，此参数不能填nil或空字典。请注意：无效数据点无法让组执行命令
 */
+ (id _Nullable)jointActionRuleResultEventByGroup:(GizDeviceGroup * _Nonnull)group data:(NSDictionary <NSString *, id>* _Nonnull)data;

/**
 构造函数，用于创建联动规则要执行的场景事件。目前只支持中控
 @param scene 场景事件。此参数不能填nil
 @param enabled 是否开启
 */
+ (id _Nullable)jointActionRuleResultEventByScene:(GizDeviceScene * _Nonnull)scene enabled:(BOOL)enabled;

/**
 构造函数，用于创建联动规则要执行的定时任务事件。目前只支持中控
 @param scheduler 定时任务事件的中控定时任务。此参数不能填nil
 @param enabled 是否开启
 */
+ (id _Nullable)jointActionRuleResultEventByScheduler:(GizDeviceSchedulerSuper * _Nonnull)scheduler enabled:(BOOL)enabled;

@end
