//
//  GizDeviceSchedulerTask.h
//  GizWifiSDK
//
//  Created by Tom on 2017/2/13.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GizWifiSDK/GizWifiDefinitions.h>

@class GizWifiDevice;

@interface GizDeviceSchedulerTask : NSObject

@property (strong, nonatomic) GizWifiDevice *device;
@property (strong, nonatomic) NSString *groupID;
@property (strong, nonatomic) NSDictionary *data;
@property (strong, nonatomic) NSString *sceneID;
@property (assign, nonatomic) GizDeviceSceneStatus sceneStatus;

@end
