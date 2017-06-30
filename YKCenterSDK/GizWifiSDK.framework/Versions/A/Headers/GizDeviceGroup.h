//
//  GizDeviceGroup.h
//  GizWifiSDK
//
//  Created by Tom on 2017/1/11.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>

/*此功能暂不支持*/

@class GizWifiDevice;

@protocol GizDeviceGroupDelegate <NSObject>
@optional

- (void)didUpdateGroupDevices:(NSString *)groupID result:(NSError *)result groupDeviceList:(NSArray *)groupDeviceList;
- (void)didWrite:(NSString *)groupID result:(NSError *)result sn:(int)sn;

@end

@interface GizDeviceGroup : NSObject

@property (strong, nonatomic, readonly) NSString *groupID;
@property (strong, nonatomic, readonly) GizWifiDevice *groupOwner;
@property (strong, nonatomic, readonly) NSString *groupType;
@property (strong, nonatomic, readonly) NSString *groupName;
@property (strong, nonatomic, readonly) NSArray *groupDeviceList;
@property (weak, nonatomic) id <GizDeviceGroupDelegate>delegate;

- (void)addDevice:(NSArray *)groupDevices;
- (void)removeDevice:(NSArray *)groupDevices;
- (void)updateGroupDevices;

- (void)write:(NSDictionary *)data sn:(int)sn;

@end
