//
//  GizDeviceJointActionRule.h
//  GizWifiSDK
//
//  Created by Tom on 2017/6/20.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <GizWifiSDK/GizDeviceJointActionRuleCondition.h>
#import <GizWifiSDK/GizDeviceJointActionRuleResultEvent.h>

@interface GizDeviceJointActionRule : NSObject

/** 设备联动规则的触发条件，GizDeviceJointActionRuleCondition对象数组 */
@property (strong, nonatomic, readonly) NSArray <GizDeviceJointActionRuleCondition *>* _Nullable conditionList;
/** 联动规则的触发条件组合类型。GizLogicalAnd类型代表并列条件，即conditionList中所有条件必须同时满足；GizLogicalOr类型代表任意条件，即conditionList中有一个条件满足即可；如果conditionList中只有一个条件，可忽略此变量 */
@property (assign, nonatomic, readonly) GizLogicalOperator conditionCombType;
/** 设备联动规则的结果事件，GizDeviceJointActionRuleResultEvent对象数组 */
@property (strong, nonatomic, readonly) NSArray <GizDeviceJointActionRuleResultEvent *>* _Nullable resultEventList;

/**
 构造函数，用于创建联动规则对象，目前只支持中控
 @param conditions 条件列表，GizDeviceJointActionRuleCondition对象数组。此参数不能填nil或空数组，可以设置一个或多个条件
 @param conditionCombType 条件组合类型。conditions中只有一个条件时，忽略此变量。详细见类中的只读变量conditionCombType说明
 @param resultEvents 结果事件集合，GizDeviceJointActionRuleResultEvent对象数组。此参数不能填nil或空数组，可以填一个或多个事件
 */
+ (id _Nullable)jointActionRule:(NSArray <GizDeviceJointActionRuleCondition *>* _Nonnull)conditions conditionCombType:(GizLogicalOperator)conditionCombType resultEvents:(NSArray <GizDeviceJointActionRuleResultEvent *>* _Nonnull)resultEvents;

@end
