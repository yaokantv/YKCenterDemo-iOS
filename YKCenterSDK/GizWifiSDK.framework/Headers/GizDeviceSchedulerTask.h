//
//  GizDeviceSchedulerTask.h
//  GizWifiSDK
//
//  Created by Tom on 2017/2/13.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDefinitions.h>

@class GizWifiDevice;
@class GizDeviceGroup;
@class GizDeviceScene;

/**
 * 只有中控才支持任务项设置。任务项分为设备任务项、组任务项和场景任务项三种类型，分别由中控的子设备或组或场景来执行。设备任务项和组任务项必须要设置数据点操作，场景任务项不需要设置数据点操作，但要设置是否启动
 */
@interface GizDeviceSchedulerTask : NSObject

- (instancetype _Nullable)init NS_UNAVAILABLE;

/**
 构造函数，用于创建设备任务项对象。目前只支持中控
 @param device 执行设备任务项的中控子设备。此参数不能填nil
 @param data 要执行的操作键值对字典：{操作名字: 操作值}，此参数不能填nil或空字典。请注意：无效数据点无法成功创建设备任务项
 */
+ (instancetype _Nullable)schedulerTaskWithDevice:(GizWifiDevice * _Nonnull)device data:(NSDictionary <NSString *, id>* _Nonnull)data;

/**
 构造函数，用于创建组任务项对象。目前只支持中控
 @param group 执行组任务项的中控分组。此参数不能填nil
 @param data 要执行的操作键值对字典：{操作名字: 操作值}，此参数不能填nil或空字典。请注意：无效数据点无法成功创建组任务项
 */
+ (instancetype _Nullable)schedulerTaskWithGroup:(GizDeviceGroup * _Nonnull)group data:(NSDictionary <NSString *, id>* _Nonnull)data;

/**
 构造函数，用于创建场景任务项对象。目前只支持中控
 @param scene 执行场景任务项的中控场景。此参数不能填nil
 @param startUp 启动或取消
 */
+ (instancetype _Nullable)schedulerTaskWithScene:(GizDeviceScene * _Nonnull)scene startUp:(BOOL)startUp;

/** 执行设备任务项的设备对象。如果taskType是设备任务项，需要关心此变量 */
@property (strong, nonatomic) GizWifiDevice * _Nullable device;
/** 执行组任务项的分组对象。如果taskType是组任务项，需要关心此变量  */
@property (strong, nonatomic) GizDeviceGroup * _Nullable group;
/** 设备或组要执行的操作键值对字典：{操作名字: 操作值}，如果taskType是设备任务项或组任务项，需要关心此变量 */
@property (strong, nonatomic) NSDictionary <NSString *, id>* _Nullable data;
/** 执行场景任务项的场景对象。如果taskType是场景任务项，需要关心此变量 */
@property (strong, nonatomic) GizDeviceScene * _Nullable scene;
/** 场景是否启动，true为启动，false为取消。如果taskType是场景任务项，需要关心此变量 */
@property (assign, nonatomic) BOOL sceneStartup;
/** 任务项类型，见GizSchedulerTaskType。如果是设备任务项只需要关心device和data；如果是组任务项只需要关心group和data；如果是场景任务项只需要关心scene和sceneStartUp */
@property (assign, nonatomic, readonly) GizSchedulerTaskType taskType;

@end
