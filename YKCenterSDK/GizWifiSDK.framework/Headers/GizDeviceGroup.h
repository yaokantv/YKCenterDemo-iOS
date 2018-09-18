//
//  GizDeviceGroup.h
//  GizWifiSDK
//
//  Created by Tom on 2017/1/11.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GizWifiDevice;
@class GizDeviceGroup;

@protocol GizDeviceGroupDelegate <NSObject>
@optional

/**
 设备分组信息更新回调。修改组信息、组信息变化上报使用该回调接口
 @param group 触发回调的组
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS表示成功，其他为失败
 @see 触发函数 [GizDeviceGroup editGroupInfo:]
 @see GizWifiErrorCode
 */
- (void)group:(GizDeviceGroup * _Nonnull)group didUpdateGroupInfo:(NSError * _Nonnull)result;

/**
 组设备列表更新回调。同步更新组设备、组设备列表变化上报使用该回调接口
 @param group 触发回调的组
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功同时groupDeviceList为最新的组列表；其他为失败并且groupDeviceList大小为0
 @param groupDeviceList 组设备列表，为GizWifiDevice对象数组
 @see 触发函数 [GizDeviceGroup addGroupDevice:]
 @see 触发函数 [GizDeviceGroup removeGroupDevice:]
 @see 触发函数 [GizDeviceGroup updateGroupDevices]
 @see GizWifiErrorCode
 */
- (void)group:(GizDeviceGroup * _Nonnull)group didUpdateGroupDevices:(NSError * _Nonnull)result groupDeviceList:(NSArray <GizWifiDevice *>* _Nullable)groupDeviceList;

/**
 组操作回调。执行组操作时触发该回调接口
 @param group 触发回调的组
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS表示成功，其他为失败
 @param sn 执行组操作的操作序号
 @see 触发函数 [GizDeviceGroup write:sn:]
 @see GizWifiErrorCode
 */
- (void)group:(GizDeviceGroup * _Nonnull)group didWrite:(NSError * _Nonnull)result sn:(int)sn;

@end

@interface GizDeviceGroup : NSObject

/** 组ID，是groupOwner创建设备分组时分配的唯一标识 */
@property (strong, nonatomic, readonly) NSString * _Nonnull groupID;
/** 组的管理者，这个管理者是设备对象，用来创建、删除、维护组信息。目前groupOwner只支持中控设备 */
@property (strong, nonatomic, readonly) GizWifiDevice * _Nonnull groupOwner;
/** 组类型，即设备的productKey。由于组是由同类型设备组成，所以组类型就是设备的产品类别唯一标识 */
@property (strong, nonatomic, readonly) NSString * _Nonnull groupType;
/** 组名称 */
@property (strong, nonatomic, readonly) NSString * _Nonnull groupName;
/** 组设备列表，GizWifiDevice对象数组。组设备列表缓存了添加到组里的设备 */
@property (strong, nonatomic, readonly) NSArray <GizWifiDevice *>* _Nonnull groupDeviceList;

/**
 GizDeviceGroup委托
 @see GizDeviceGroupDelegate
 */
@property (weak, nonatomic) id <GizDeviceGroupDelegate> _Nullable delegate;

/**
 修改设备分组信息。修改成功时返回最新的组信息，修改失败时返回错误信息。目前组信息只能修改组名称
 @param groupName 待修改的组名称。此参数不能填nil
 @see 回调 [GizDeviceGroupDelegate group:didUpdateGroupInfo:]
 */
- (void)editGroupInfo:(NSString * _Nonnull)groupName;

/**
 添加组设备。添加成功时返回最新的组设备列表，添加失败时返回错误信息
 @param groupDevices 待添加的组设备，为GizWifiDevice对象数组。此参数不能填nil或空数组
 @see 回调 [GizDeviceGroupDelegate group:didUpdateGroupDevices:groupDeviceList:]
 */
- (void)addGroupDevice:(NSArray <GizWifiDevice *>* _Nonnull)groupDevices;

/**
 删除组设备。删除成功时返回最新的组设备列表，删除失败时返回错误信息
 @param groupDevices 待删除的组设备，为GizWifiDevice对象数组。此参数不能填nil或空数组
 @see 回调 [GizDeviceGroupDelegate group:didUpdateGroupDevices:groupDeviceList:]
 */
- (void)removeGroupDevice:(NSArray <GizWifiDevice *>* _Nonnull)groupDevices;

/**
 同步更新组设备。更新成功时返回最新的组设备列表，更新失败时返回错误信息
 @see 回调 [GizDeviceGroupDelegate group:didUpdateGroupDevices:groupDeviceList:]
 */
- (void)updateGroupDevices;

/**
 执行组操作
 @param data 待执行的组操作，数据点键值对字典，键值对为{数据点名称：数据点值}。数据点名称和值的类型要符合设备的数据点定义，透传数据的数据点名称要填"binary"，数据点值的类型要用NSData，不符合格式的数据点参数可能无法下发。此参数不能填nil或空字典，
 @param sn 操作序号。如果App需要对应操作执行顺序，sn就要指定为一个正整数。如果App不关心操作执行顺序，sn填0。负数默认按照0处理
 @see 回调 [GizDeviceGroup group:didWrite:sn:]
 */
- (void)write:(NSDictionary <NSString *, id>* _Nonnull)data sn:(int)sn;

@end
