//
//  GizDeviceScene.h
//  GizWifiSDK
//
//  Created by Tom on 2017/1/16.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <GizWifiSDK/GizDeviceSceneItem.h>

@class GizWifiDevice;
@class GizDeviceScene;

@protocol GizDeviceSceneDelegate <NSObject>
@optional

/**
 场景信息更新回调。编辑场景信息、场景信息变化上报使用该回调接口
 @param scene 触发回调的场景
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS表示成功，其他为失败
 @see 触发函数 [GizDeviceScene editSceneInfo:]
 @see GizWifiErrorCode
 */
- (void)scene:(GizDeviceScene * _Nonnull)scene didUpdateSceneInfo:(NSError * _Nonnull)result;

/**
 场景项列表更新回调。编辑场景项、同步更新场景项、场景项列表变化上报使用该回调接口
 @param scene 触发回调的场景
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功同时sceneItemList为最新的场景项列表；其他为失败并且sceneItemList大小为0
 @param sceneItemList 场景项列表，为GizDeviceSceneItem对象数组
 @see 触发函数 [GizDeviceScene editSceneItems:]
 @see 触发函数 [GizDeviceScene updateSceneItems]
 @see GizWifiErrorCode
 */
- (void)scene:(GizDeviceScene * _Nonnull)scene didUpdateSceneItems:(NSError * _Nonnull)result sceneItemList:(NSArray <GizDeviceSceneItem *>* _Nullable)sceneItemList;

/**
 场景项启动或取消结果回调。启动或取消场景项使用该回调接口
 @param scene 触发回调的场景
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param sn 启动或取消场景的操作序号
 @see 触发函数 [GizDeviceScene executeScene:sn:]
 @see GizWifiErrorCode
 */
- (void)scene:(GizDeviceScene * _Nonnull)scene didExecuteScene:(NSError * _Nonnull)result sn:(int)sn;

/**
场景项启动或取消结果回调。场景的启动或取消状态上报和更新使用该回调接口
@param scene 触发回调的场景
@param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功
@param status 场景的启动或取消状态
@see 触发函数 [GizDeviceScene updateSceneStatus]
@see GizWifiErrorCode
*/
- (void)scene:(GizDeviceScene * _Nonnull)scene didUpdateSceneStatus:(NSError * _Nonnull)result status:(GizDeviceSceneStatus)status;

@end

@interface GizDeviceScene : NSObject

/** 场景ID，是sceneOwner创建场景时分配的唯一标识 */
@property (strong, nonatomic, readonly) NSString * _Nonnull sceneID;
/** 场景的管理者，这个管理者是设备对象，用来创建、删除、维护场景信息。目前sceneOwner只支持中控设备 */
@property (strong, nonatomic, readonly) GizWifiDevice * _Nonnull sceneOwner;
/** 场景名称 */
@property (strong, nonatomic, readonly) NSString * _Nonnull sceneName;
/** 场景项列表，GizDeviceSceneItem对象数组。场景项列表缓存了添加到场景里的场景项 */
@property (strong, nonatomic, readonly) NSArray <GizDeviceSceneItem *>* _Nonnull sceneItemList;

/**
 GizDeviceScene委托
 @see GizDeviceSceneDelegate
 */
@property (weak, nonatomic) id <GizDeviceSceneDelegate> _Nullable delegate;

- (_Nullable instancetype)init NS_UNAVAILABLE;

/**
 编辑场景信息。编辑成功时返回最新的场景信息，编辑失败时返回错误信息。目前场景信息只能修改场景名称
 @param sceneName 待修改的场景名称。此参数不能填nil
 @see 回调 [GizDeviceSceneDelegate scene:didUpdateSceneInfo:]
 */
- (void)editSceneInfo:(NSString * _Nonnull)sceneName;

/**
 编辑场景项列表，此接口只支持中控。编辑成功时返回最新的场景项列表，失败时返回错误信息
 @param sceneItems 包含待编辑场景项的全部场景项列表，GizDeviceSceneItem对象数组。这个列表必须能符合预期的修改结果，列表中应包括新添加的、待修改的、不修改的，如果有待删除的要移除掉。此参数不能填nil或空数组
 @see 回调 [GizDeviceSceneDelegate scene:didUpdateSceneItems:sceneItemList:]
 */
- (void)editSceneItems:(NSArray <GizDeviceSceneItem *>* _Nonnull)sceneItems;

/**
 更新场景项列表，此接口只支持中控。更新成功时返回最新的场景项列表，失败时返回错误信息
 @see 回调 [GizDeviceSceneDelegate scene:didUpdateSceneItems:sceneItemList:]
 */
- (void)updateSceneItems;

/**
 启动或取消场景
 @param sceneStartup 启动或取消
 @param sn 操作序号。如果App需要对应操作执行顺序，sn就要指定为一个正整数。如果App不关心操作执行顺序，sn填0
 @see 回调 [GizDeviceSceneDelegate scene:didExecuteScene:sn:]
 */
- (void)executeScene:(BOOL)sceneStartup sn:(int)sn;

/**
 更新场景启动状态
 @see 回调 [GizDeviceSceneDelegate scene:didUpdateSceneStatus:status:]
 */
- (void)updateSceneStatus;

@end
