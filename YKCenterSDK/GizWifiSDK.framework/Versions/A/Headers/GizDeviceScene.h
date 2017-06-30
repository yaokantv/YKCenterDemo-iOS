//
//  GizDeviceScene.h
//  GizWifiSDK
//
//  Created by Tom on 2017/1/16.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDefinitions.h>

/*此功能暂不支持*/

@class GizWifiDevice;

@protocol GizDeviceSceneDelegate <NSObject>
@optional

- (void)didUpdateSceneItems:(NSString *)sceneID result:(NSError *)result sceneItemList:(NSArray *)sceneItemList;
- (void)didExecuteScene:(NSString *)sceneID result:(NSError *)result sn:(int)sn;
- (void)didUpdateSceneStatus:(NSString *)sceneID result:(NSError *)result status:(GizDeviceSceneStatus)status;

@end

@interface GizDeviceScene : NSObject

@property (strong, nonatomic, readonly) NSString *sceneID;
@property (strong, nonatomic, readonly) GizWifiDevice *sceneOwner;
@property (strong, nonatomic, readonly) NSString *sceneName;
@property (strong, nonatomic, readonly) NSArray *sceneItemList;

@property (weak, nonatomic) id <GizDeviceSceneDelegate>delegate;

- (instancetype)init NS_UNAVAILABLE;

- (void)editSceneItems:(NSArray *)sceneItems;

- (void)updateSceneItems;

- (void)executeScene:(GizDeviceSceneStatus)status sn:(int)sn;
- (void)updateSceneStatus;

@end
