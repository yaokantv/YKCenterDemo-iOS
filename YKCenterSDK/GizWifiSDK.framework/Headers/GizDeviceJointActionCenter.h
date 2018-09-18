//
//  GizDeviceJointActionCenter.h
//  GizWifiSDK
//
//  Created by Tom on 2017/6/20.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <GizWifiSDK/GizDeviceJointAction.h>

@class GizWifiDevice;

@protocol GizDeviceJointActionCenterDelegate <NSObject>
@optional

/**
 联动列表回调。添加联动、删除联动、同步更新联动列表、联动列表变化上报都使用该回调接口
 @param jointActionOwner 触发回调的GizWifiDevice对象
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功同时jointActionList为最新的联动列表；其他为失败并且jointActionList大小为0
 @param jointActionList 联动列表，是GizDeviceJointAction对象数组
 @see 触发函数 [GizDeviceJointActionCenter addJointAction:jointActionName:jointActionRule:]
 @see 触发函数 [GizDeviceJointActionCenter removeJointAction:jointAction:]
 @see 触发函数 [GizDeviceJointActionCenter updateJointActions:]
 @see GizWifiErrorCode
 */
- (void)didUpdateJointActions:(GizWifiDevice * _Nullable)jointActionOwner result:(NSError * _Nonnull)result jointActionList:(NSArray <GizDeviceJointAction *>* _Nullable)jointActionList;

@end

@interface GizDeviceJointActionCenter : NSObject

/**
 GizDeviceJointActionCenterDelegate委托
 */
@property (class, weak, nonatomic) id <GizDeviceJointActionCenterDelegate> _Nullable delegate;

/**
 * 获取中控设备下的设备联动列表，这个联动列表缓存了GizDeviceJointAction对象
 * @param jointActionOwner 中控设备，此参数不能填nil
 * @return 联动列表。参数为nil或无效设备时返回空数组
 */
+ (NSArray <GizDeviceJointAction *>* _Nullable)getJointActionListGateway:(GizWifiDevice * _Nonnull)jointActionOwner;

/**
 添加联动。添加成功后会被分配一个联动ID，此时会返回最新的联动列表，失败时返回错误信息
 @param jointActionOwner 联动的管理者设备。此参数不能填nil
 @param jointActionName 联动名称。此参数为选填参数，如果不指定名称此参数填nil，App可以在成功添加联动以后再修改名称
 @param enabled 是否开启联动。true为开启，false为关闭
 @param jointActionRule 联动规则，是GizDeviceJointActionRule对象。此参数不能填nil
 @see 回调 [GizDeviceJointActionCenterDelegate didUpdateJointActions:result:jointActionList:]
 */
+ (void)addJointAction:(GizWifiDevice * _Nonnull)jointActionOwner jointActionName:(NSString * _Nullable)jointActionName enabled:(BOOL)enabled jointActionRule:(GizDeviceJointActionRule * _Nullable)jointActionRule;

/**
 删除联动。删除成功时返回最新的联动列表，删除失败时返回错误信息
 @param jointActionOwner 联动的管理者，参见GizDeviceJointAction类中jointActionOwner变量的描述。此参数不能填nil
 @param jointAction 待删除的联动。参见GizDeviceJointAction类中jointAction变量的描述。此参数不能填nil
 @see 回调 [GizDeviceJointActionCenterDelegate didUpdateJointActions:result:jointActionList:]
 */
+ (void)removeJointAction:(GizWifiDevice * _Nonnull)jointActionOwner jointAction:(GizDeviceJointAction * _Nonnull)jointAction;

/**
 更新联动列表。更新成功时返回最新的联动列表，更新失败时返回错误信息
 @param jointActionOwner 联动的管理者，参见GizDeviceJointAction类中jointActionOwner变量的描述。此参数不能填nil
 @see 回调 [GizDeviceJointActionCenterDelegate didUpdateJointActions:result:jointActionList:]
 */
+ (void)updateJointActions:(GizWifiDevice * _Nonnull)jointActionOwner;

@end
