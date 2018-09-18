//
//  GizDeviceJointActionRuleCondition.h
//  GizWifiSDK
//
//  Created by Tom on 2017/6/20.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDefinitions.h>

@class GizWifiDevice;

@interface GizDeviceJointActionRuleCondition : NSObject

/** 联动规则中的中控子设备 */
@property (strong, nonatomic, readonly) GizWifiDevice * _Nullable device;
/** 设备或组要执行的操作键值对字典：{操作名字: 操作值}，resultEventType是设备或组事件需要关心此变量 */
@property (strong, nonatomic, readonly) NSDictionary <NSString *, id>* _Nonnull data;

/** 条件运算符。此变量提供6种运算方法，用于把条件设定值与设备实际状态值做比较 */
@property (assign, nonatomic, readonly) GizConditionOperator conditionOperator;

/**
 构造函数，用于创建联动规则的触发条件。目前只支持中控
 @param device 触发条件中的中控子设备。此参数不能填nil
 @param data 触发条件中的设备状态阀值：{操作名字: 操作值}，此参数不能填nil或空字典。请注意：无效数据点无法触发结果事件的执行
 */
+ (id _Nullable)jointActionRuleCondition:(GizWifiDevice * _Nonnull)device data:(NSDictionary <NSString *, id>* _Nonnull)data conditionOperator:(GizConditionOperator)conditionOperator;

@end
