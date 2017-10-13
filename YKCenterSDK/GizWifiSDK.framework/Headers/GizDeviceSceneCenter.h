//
//  GizDeviceSceneCenter.h
//  GizWifiSDK
//
//  Created by Tom on 2017/1/11.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <GizWifiSDK/GizDeviceScene.h>

@class GizWifiDevice;
@class GizDeviceScene;

@protocol GizDeviceSceneCenterDelegate <NSObject>
@optional

/**
 场景列表回调。添加场景、删除场景、同步更新场景列表、场景列表变化上报都使用该回调接口
 @param sceneOwner 触发回调的GizWifiDevice对象
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功同时sceneList为最新的场景列表；其他为失败并且sceneList大小为0
 @param sceneList 场景列表，是GizDeviceScene对象数组
 @see 触发函数 [GizDeviceSceneCenter addScene:sceneName:sceneItems:]
 @see 触发函数 [GizDeviceGroupCenter removeScene:scene:]
 @see 触发函数 [GizDeviceGroupCenter updateScenes:]
 @see GizWifiErrorCode
 */
- (void)didUpdateScenes:(GizWifiDevice * _Nullable)sceneOwner result:(NSError * _Nonnull)result sceneList:(NSArray <GizDeviceScene *>* _Nullable)sceneList;

@end

@interface GizDeviceSceneCenter : NSObject

/**
 GizDeviceSceneCenterDelegate委托
 */
@property (class, weak, nonatomic) id <GizDeviceSceneCenterDelegate> _Nullable delegate;

/**
 获取中控设备下的场景列表，这个组列表缓存了GizDeviceScene对象
 @param sceneOwner 中控设备，此参数不能填nil
 @return 场景列表。参数值为nil或无效设备时返回空数组
 */
+ (NSArray <GizDeviceScene *>* _Nullable)getSceneListGateway:(GizWifiDevice * _Nonnull)sceneOwner;

/**
 添加场景。添加成功后会被分配一个场景ID，此时会返回最新的场景列表，失败时返回错误信息
 @param sceneOwner 场景的管理者，参见GizDeviceScene类中sceneOwner变量的描述。此参数不能填nil
 @param sceneName 场景名称。此参数为选填参数，如果不指定场景名称此参数填nil，App也可以在成功添加场景以后再修改场景名称
 @param sceneItems 场景项列表，是GizDeviceSceneItem对象数组。此参数为选填参数，如果不指定场景项此参数填nil或空数组，App也可以在成功添加场景以后再添加场景项
 @see 回调 [GizDeviceSceneCenterDelegate didUpdateScenes:result:sceneList:]
 */
+ (void)addScene:(GizWifiDevice * _Nonnull)sceneOwner sceneName:(NSString * _Nullable)sceneName sceneItems:(NSArray <GizDeviceSceneItem *>* _Nullable)sceneItems;

/**
 删除场景。删除成功时返回最新的场景列表，删除失败时返回错误信息
 @param sceneOwner 场景的管理者，参见GizDeviceScene类中sceneOwner变量的描述。此参数不能填nil
 @param scene 待删除的场景。参见GizDeviceScene类中scene变量的描述。此参数不能填nil
 @see 回调 [GizDeviceSceneCenterDelegate didUpdateScenes:result:sceneList:]
 */
+ (void)removeScene:(GizWifiDevice * _Nonnull)sceneOwner scene:(GizDeviceScene * _Nonnull)scene;

/**
 更新场景列表。更新成功时返回最新的场景列表，更新失败时返回错误信息
 @param sceneOwner 场景的管理者，参见GizDeviceScene类中sceneOwner变量的描述。此参数不能填nil
 @see 回调 [GizDeviceSceneCenterDelegate didUpdateScenes:result:sceneList:]
 */
+ (void)updateScenes:(GizWifiDevice * _Nonnull)sceneOwner;

@end
