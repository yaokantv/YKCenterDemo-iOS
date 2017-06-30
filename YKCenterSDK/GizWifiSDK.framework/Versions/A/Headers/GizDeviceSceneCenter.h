//
//  GizDeviceSceneCenter.h
//  GizWifiSDK
//
//  Created by Tom on 2017/1/11.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>

/*此功能暂不支持*/

@class GizWifiDevice;

@protocol GizDeviceSceneCenterDelegate <NSObject>
@optional

- (void)didUpdateScenes:(GizWifiDevice *)sceneOwner result:(NSError *)result sceneList:(NSArray *)sceneList;

@end

@interface GizDeviceSceneCenter : NSObject

+ (void)setDelegate:(id <GizDeviceSceneCenterDelegate>)delegate;
+ (void)addScene:(GizWifiDevice *)sceneOwner sceneName:(NSString *)sceneName sceneItems:(NSArray *)sceneItems;

+ (void)editScene:(GizWifiDevice *)sceneOwner sceneID:(NSString *)sceneID sceneName:(NSString *)sceneName;
+ (void)removeScene:(GizWifiDevice *)sceneOwner sceneID:(NSString *)sceneID;
+ (void)updateScenes:(GizWifiDevice *)sceneOwner;

@end
