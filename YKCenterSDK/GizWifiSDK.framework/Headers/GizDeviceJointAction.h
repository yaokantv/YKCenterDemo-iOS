//
//  GizDeviceJointAction.h
//  GizWifiSDK
//
//  Created by Tom on 2017/6/20.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <GizWifiSDK/GizDeviceJointActionRule.h>

@class GizWifiDevice;
@class GizDeviceJointAction;

@protocol GizDeviceJointActionDelegate <NSObject>
@optional

/**
 联动名称更新回调。编辑联动信息、联动信息变化上报使用该回调接口
 @param jointAction 触发回调的联动
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS表示成功，其他为失败
 @see 触发函数 [GizDeviceJointAction editJointActionInfo:]
 @see GizWifiErrorCode
 */
- (void)jointAction:(GizDeviceJointAction * _Nullable)jointAction didUpdateJointActionInfo:(NSError * _Nonnull)result;

/**
 联动开启或关闭状态更新回调。开启或关闭联动、联动开启状态变化上报使用该回调接口
 @param jointAction 触发回调的联动
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS表示成功，其他为失败
 @see 触发函数 [GizDeviceJointAction enableJointAction:]
 @see GizWifiErrorCode
 */
- (void)jointAction:(GizDeviceJointAction * _Nullable)jointAction didUpdateJointActionStatus:(NSError * _Nonnull)result;

/**
 联动规则更新回调。修改联动规则、联动规则变化上报使用该回调接口
 @param jointActionRule 触发回调的联动规则
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS表示成功，其他为失败
 @see 触发函数 [GizDeviceJointAction editJointActionRule:conditionCombType:resultEvents:]
 @see GizWifiErrorCode
 */
- (void)jointAction:(GizDeviceJointAction * _Nullable)jointAction didUpdateJointActionRule:(NSError * _Nonnull)result;

@end

@interface GizDeviceJointAction : NSObject

/** 联动ID，是jointActionOwner创建场景时分配的唯一标识 */
@property (strong, nonatomic, readonly) NSString * _Nonnull JointActionID;
/** 联动的管理者，这个管理者是设备对象，用来创建、删除、维护联动信息。目前jointActionOwner只支持中控设备 */
@property (strong, nonatomic, readonly) GizWifiDevice * _Nullable jointActionOwner;
/** 联动名称 */
@property (strong, nonatomic, readonly) NSString * _Nonnull jointActionName;
/** 是否开启联动。YES为开启，NO为关闭 */
@property (assign, nonatomic, readonly) BOOL enabled;
 /** 联动规则，GizDeviceJointActionRule对象 */
@property (strong, nonatomic, readonly) GizDeviceJointActionRule * _Nullable jointActionRule;

/**
 GizDeviceJointAction委托
 @see GizDeviceJointActionDelegate
 */
@property (weak, nonatomic) id<GizDeviceJointActionDelegate> _Nullable delegate;

/**
 修改联动信息。
 @param jointActionName 修改后的联动名称。此参数不能填nil
 @see 回调 [GizDeviceJointActionDelegate didUpdateJointActionInfo:result:jointActionList:]
 */
- (void)editJointActionInfo:(NSString * _Nonnull)jointActionName;

/**
 开启或关闭联动
 @param enabled 联动开启或关闭
 @see 回调 [GizDeviceJointActionDelegate jointAction:didUpdateJointActionStatus:]
 */
- (void)enableJointAction:(BOOL)enabled;

/**
 修改联动规则
 @param conditions 包含待编辑的全部条件列表，GizDeviceJointActionRuleCondition对象数组。这个列表必须能符合预期的修改结果，列表中应包括新添加的、待修改的、不修改的，如果有待删除的要移除掉。此参数不能填nil或空数组
 @param conditionCombType 条件组合类型。只有一个条件时此参数无效
 @param resultEvents 包含待编辑的全部结果列表，GizDeviceJointActionRuleResultEvent对象数组。这个列表必须能符合预期的修改结果，列表中应包括新添加的、待修改的、不修改的，如果有待删除的要移除掉。此参数不能填nil或空数组
 @see 回调 [GizDeviceJointActionDelegate jointAction:didUpdateJointActionRule:]
 */
- (void)editJointActionRule:(NSArray * _Nonnull)conditions conditionCombType:(GizLogicalOperator)conditionCombType resultEvents:(NSArray * _Nonnull)resultEvents;

/**
 查询联动规则
 @see 回调 [GizDeviceJointActionDelegate jointAction:didUpdateJointActionRule:]
 */
- (void)updateJointActionRule;

@end
