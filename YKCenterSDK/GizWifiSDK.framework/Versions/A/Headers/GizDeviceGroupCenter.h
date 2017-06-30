//
//  GizDeviceGroupCenter.h
//  GizWifiSDK
//
//  Created by Tom on 2017/1/11.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>

/*此功能暂不支持*/

@class GizWifiDevice;

@protocol GizDeviceGroupCenterDelegate <NSObject>
@optional

- (void)didUpdateGroups:(GizWifiDevice *)groupOwner result:(NSError *)result groupList:(NSArray *)groupList;

@end

@interface GizDeviceGroupCenter : NSObject

+ (void)setDelegate:(id <GizDeviceGroupCenterDelegate>)delegate;

+ (void)addGroup:(GizWifiDevice *)groupOwner groupType:(NSString *)groupType groupName:(NSString *)groupName groupDevices:(NSArray *)groupDevices;
+ (void)editGroup:(GizWifiDevice *)groupOwner groupID:(NSString *)groupID groupName:(NSString *)groupName;
+ (void)removeGroup:(GizWifiDevice *)groupOwner groupID:(NSString *)groupID;
+ (void)updateGroups:(GizWifiDevice *)groupOwner;

@end
