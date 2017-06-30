//
//  GizDeviceSharingInfo.h
//  GizWifiSDK
//
//  Created by Tom on 2016/12/7.
//  Copyright © 2016年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GizUserInfo;

/*
 GizDeviceSharingInfo类是设备分享信息类。
 */
@interface GizDeviceSharingInfo : NSObject

/*
 NSInteger类型，只读不可写。设备分享ID，设备分享创建成功时会被分配一个ID
 */
@property (assign, nonatomic, readonly) NSInteger id;
/*
 NSString类型，只读不可写。设备ID
 */
@property (strong, nonatomic, readonly) NSString *deviceID;
/*
 NSString类型，只读不可写。设备的产品名称
 */
@property (strong, nonatomic, readonly) NSString *productName;
/*
 NSString类型，只读不可写。设备的产品名称
 */
@property (strong, nonatomic, readonly) NSString *deviceAlias;
/*
 GizUserInfo类对象，只读不可写。这条分享邀请的账号信息，分享者或者被分享者的账号信息
 */
@property (strong, nonatomic, readonly) GizUserInfo *userInfo;
/*
 NSString类型，只读不可写。这条分享邀请的别名
 */
@property (strong, nonatomic, readonly) NSString *alias;
/*
 GizDeviceSharingType枚举类型，只读不可写。分享邀请是分享给自己的还是自己分享给别人的
 */
@property (assign, nonatomic, readonly) GizDeviceSharingType type;
/*
 GizDeviceSharingWay枚举类型，只读不可写。分享邀请是账号分享还是二维码分享
 */
@property (assign, nonatomic, readonly) GizDeviceSharingWay way;
/*
 GizDeviceSharingStatus枚举类型，只读不可写。分享邀请的状态，是被接受还是被拒绝的，或者还未接受
 */
@property (assign, nonatomic, readonly) GizDeviceSharingStatus status;
/*
 NSString类型，只读不可写。分享邀请的创建时间
 */
@property (strong, nonatomic, readonly) NSString *createdAt;
/*
 NSString类型，只读不可写。分享邀请的更新时间
 */
@property (strong, nonatomic, readonly) NSString *updatedAt;
/*
 NSString类型，只读不可写。分享邀请的超时时间
 */
@property (strong, nonatomic, readonly) NSString *expiredAt;

@end
