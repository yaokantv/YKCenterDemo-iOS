//
//  GizWifiGroup.h
//  GizWifiSDK
//
//  Created by GeHaitong on 15/7/9.
//  Copyright (c) 2015年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GizWifiGroup;

/*
 GizWifiGroupDelegate 是 GizWifiGroup 类的委托协议，为 APP 开发者处理子设备添加、子设备删除、获取子设备列表提供委托函数
 */
@protocol GizWifiGroupDelegate <NSObject>
@optional

/*
 分组设备列表回调
 @param group 触发回调的设备分组对象
 @param result 详细见 GizWifiErrorCode 枚举定义。result.code 为 GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，deviceList大小为0
 @param deviceList 分组设备列表，用以下键值对唯一标识一个子设备：
     {
         "did": [value]     //父设备标识码
         "sdid": [value],   //子设备标识码
     }
 
 @see 触发函数：[GizWifiGroup getDevices]、[GizWifiGroup addDevice:withSubDevice:]、[GizWifiGroup removeDevice:withSubDevice:]
 @see GizWifiErrorCode
 */
- (void)group:(GizWifiGroup *)group didGetDevices:(NSError *)result deviceList:(NSArray *)deviceList DEPRECATED_ATTRIBUTE;

/*
 @deprecated 此接口已废弃，不再提供支持。请使用替代接口：[GizWifiGroupDelegate group:didGetDevices:deviceList:]
 */
- (void)XPGWifiGroup:(GizWifiGroup *)group didGetDevices:(NSArray *)deviceList result:(int)result DEPRECATED_ATTRIBUTE;

@end

/*
 GizWifiGroup 类为 APP 开发者提供中控子设备的设备分组操作，包括获取分组内的设备、往分组内添加设备、删除分组内的设备等功能
 */
NS_CLASS_DEPRECATED_IOS(1_0, 2_0, "GizWifiGroupDelegate is deprecated.")
@interface GizWifiGroup : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*
 NSString类型。设备分组的组标识 ID
 */
@property (strong, nonatomic, readonly) NSString *gid;

/*
 NSString类型。设备分组的组名称
 */
@property (strong, nonatomic, readonly) NSString *groupName;

/*
 NSString类型。设备分组的组类型（根据设备的产品标识码来区别）
 */
@property (strong, nonatomic, readonly) NSString *groupType;

/*
 @deprecated 此变量已废弃，不再提供支持。替代变量为 groupType
 */
@property (strong, nonatomic, readonly) NSString *productKey DEPRECATED_ATTRIBUTE;

/*
 使用委托获取对应事件。GizWifiGroup 对应的回调接口在 GizWifiGroupDelegate 定义，需要用到哪个接口，实现对应的回调即可
 */
@property (weak, nonatomic) id <GizWifiGroupDelegate>delegate;

/*
 获取分组设备列表
 @see 对应的回调接口：[GizWifiGroupDelegate group:didGetDevices:deviceList:]
 */
- (void)getDevices;

/*
 往设备分组内添加设备。设备的产品类型与组类型相同，才能添加到组里
 @param did 父设备的设备标识
 @param sdid 子设备的设备标识
 @see 对应的回调接口：[GizWifiGroupDelegate group:didGetDevices:deviceList:]
 */
- (void)addDevice:(NSString *)did withSubDevice:(NSString *)subdid;

/*
 从设备分组内删除设备
 @param did 父设备的设备标识
 @param sdid 子设备的设备标识
 @see 对应的回调接口：[GizWifiGroupDelegate group:didGetDevices:deviceList:]
 */
- (void)removeDevice:(NSString *)did withSubDevice:(NSString *)subdid;

@end
