//
//  GizMessage.h
//  GizWifiSDK
//
//  Created by Tom on 2016/12/7.
//  Copyright © 2016年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 GizMessage类是机智云消息类。
 */
@interface GizMessage : NSObject

/*
 NSString类型，只读不可写。消息ID
 */
@property (strong, nonatomic, readonly) NSString *id;
/*
 GizMessageType枚举类型，只读不可写。消息类型，是系统消息还是分享消息
 */
@property (assign, nonatomic, readonly) GizMessageType type;
/*
 GizMessageStatus枚举类型，只读不可写。消息状态，是否是已读、未读或已删除消息
 */
@property (assign, nonatomic, readonly) GizMessageStatus status;
/*
 NSString类型，只读不可写。消息生成时间
 */
@property (strong, nonatomic, readonly) NSString *createdAt;
/*
 NSString类型，只读不可写。消息更新时间
 */
@property (strong, nonatomic, readonly) NSString *updatedAt;
/*
 NSString类型，只读不可写。消息内容
 */
@property (strong, nonatomic, readonly) NSString *content;

@end
