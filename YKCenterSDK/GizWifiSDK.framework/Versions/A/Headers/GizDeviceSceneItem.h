//
//  GizDeviceSceneItem.h
//  GizWifiSDK
//
//  Created by Tom on 2017/1/11.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>

/*此功能暂不支持*/

@interface GizDeviceSceneItem : NSObject

- (instancetype)init;

@property (strong, nonatomic) NSString *deviceID;
@property (strong, nonatomic) NSString *groupID;
@property (strong, nonatomic) NSDictionary *data;
@property (assign, nonatomic) NSInteger delayTime;

@end
