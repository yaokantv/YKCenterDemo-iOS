//
//  GizDeviceGroupCenter.h
//  GizWifiSDK
//
//  Created by Tom on 2017/1/11.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <GizWifiSDK/GizDeviceGroup.h>

@class GizWifiDevice;

@protocol GizDeviceGroupCenterDelegate <NSObject>
@optional

/**
 设备分组列表回调。创建组、删除组、同步更新组列表、组列表变化上报都使用该回调接口
 @param groupOwner 触发回调的GizWifiDevice对象
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功同时groupList为最新的组列表；其他为失败并且groupList大小为0
 @param groupList 组列表，是GizDeviceGroup对象数组
 @see 触发函数 [GizDeviceGroupCenter addGroup:groupType:groupName:groupDevices:]
 @see 触发函数 [GizDeviceGroupCenter removeGroup:group:]
 @see 触发函数 [GizDeviceGroupCenter updateGroups:]
 @see GizWifiErrorCode
 */
- (void)didUpdateGroups:(GizWifiDevice * _Nullable)groupOwner result:(NSError * _Nonnull)result groupList:(NSArray <GizDeviceGroup *>* _Nullable)groupList;

@end

@interface GizDeviceGroupCenter : NSObject

/**
 GizDeviceGroupCenter委托
 @see GizDeviceGroupCenterDelegate
 */
@property (class, weak, nonatomic) id <GizDeviceGroupCenterDelegate> _Nullable delegate;

/**
 获取中控设备下的设备分组列表，这个组列表缓存了GizDeviceGroup对象
 @param groupOwner 中控设备，此参数不能填nil
 @return 分组列表。参数值为nil或无效设备时返回空数组
 */
+ (NSArray <GizDeviceGroup *>* _Nullable)getGroupListGateway:(GizWifiDevice * _Nonnull)groupOwner;

/**
 创建设备分组。创建成功后会被分配一个组ID，创建成功时返回最新的设备分组列表，创建失败时返回错误信息
 @param groupOwner 组的管理者，参见GizDeviceGroup类中groupOwner变量的描述。此参数不能填nil
 @param groupType 组类型即productKey，设备的产品唯一标识，参见GizDeviceGroup类中groupType变量的描述。此参数不能填nil或无效值
 @param groupName 组名称。此参数为选填参数，如果不指定组名称此参数填nil，App也可以在成功创建组以后再修改组名称
 @param groupDevices 组设备列表，是GizWifiDevice对象数组。此参数为选填参数，如果不添加组设备此参数填nil或空数组，App也可以在成功创建组以后再添加组设备
 @see 回调 [GizDeviceGroupCenterDelegate didUpdateGroups:result:groupList:]
 */
+ (void)addGroup:(GizWifiDevice * _Nonnull)groupOwner groupType:(NSString * _Nonnull)groupType groupName:(NSString * _Nonnull)groupName groupDevices:(NSArray <GizWifiDevice *>* _Nonnull)groupDevices;

/**
 删除设备分组。删除成功时返回最新的组列表，删除失败时返回错误信息
 @param groupOwner 组的管理者，参见GizDeviceGroup类中groupOwner变量的描述。此参数不能填nil
 @param group 待删除的组。此参数不能填nil
 @see 回调 [GizDeviceGroupCenterDelegate didUpdateGroups:result:groupList:]
 */
+ (void)removeGroup:(GizWifiDevice * _Nonnull)groupOwner group:(GizDeviceGroup * _Nonnull)group;

/**
 更新设备分组列表。更新成功时返回最新的组列表，更新失败时返回错误信息
 @param groupOwner 组的管理者，参见GizDeviceGroup类中groupOwner变量的描述。此参数不能填nil
 @see 回调 [GizDeviceGroupCenterDelegate didUpdateGroups:result:groupList:]
 */
+ (void)updateGroups:(GizWifiDevice * _Nonnull)groupOwner;

@end
