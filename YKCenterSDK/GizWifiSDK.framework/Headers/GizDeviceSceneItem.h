//
//  GizDeviceSceneItem.h
//  GizWifiSDK
//
//  Created by Tom on 2017/1/11.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDefinitions.h>

@class GizWifiDevice;
@class GizDeviceGroup;

@interface GizDeviceSceneItem : NSObject

- (instancetype _Nullable)init NS_UNAVAILABLE;

/**
 构造函数，用于创建设备场景项对象。目前只支持中控
 @param device 执行设备场景项的中控子设备。此参数不能填nil
 @param data 要执行的操作键值对字典：{操作名字: 操作值}，此参数不能填nil或空字典。请注意：无效数据点无法成功创建设备场景项
 */
+ (instancetype _Nullable)sceneItemWithDevice:(GizWifiDevice * _Nonnull)device data:(NSDictionary <NSString *, id>* _Nonnull)data;

/**
 构造函数，用于创建组场景项对象。目前只支持中控
 @param group 执行组场景项的中控分组。此参数不能填nil
 @param data 要执行的操作键值对字典：{操作名字: 操作值}，此参数不能填nil或空字典。请注意：无效数据点无法成功创建组场景项
 */
+ (instancetype _Nullable)sceneItemWithGroup:(GizDeviceGroup * _Nonnull)group data:(NSDictionary <NSString *, id>* _Nonnull)data;

/**
 构造函数，用于创建延时场景项对象。目前只支持中控
 @param delayTime 延时时间
 */
+ (instancetype _Nullable)sceneItemWithDelay:(unsigned int)delayTime;

/** 设备场景项的中控子设备，如果sceneItemType是设备场景项，需要关心此变量 */
@property (strong, nonatomic, readonly) GizWifiDevice * _Nullable device;
/** 组场景项的中控子设备，如果sceneItemType是组场景项，需要关心此变量  */
@property (strong, nonatomic, readonly) GizDeviceGroup * _Nullable group;
/** 设备或组要执行的操作键值对字典：{操作名字: 操作值}，如果sceneItemType是设备场景项或组场景项，需要关心此变量 */
@property (strong, nonatomic, readonly) NSDictionary <NSString *, id>* _Nullable data;
/** 延时的毫秒数，如果sceneItemType是延时场景项，需要关心此变量。延时场景项不关注其他变量 */
@property (assign, nonatomic, readonly) unsigned int delayTime;
/** 场景项类型，见GizSceneItemType。如果是设备场景项只需要关心device和data；如果是组场景项只需要关心group和data；如果是延时场景项只需要关心delayTime */
@property (assign, nonatomic, readonly) GizSceneItemType sceneItemType;

@end
