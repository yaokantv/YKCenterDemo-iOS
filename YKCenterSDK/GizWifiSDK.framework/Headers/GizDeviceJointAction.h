//
//  GizDeviceJointAction.h
//  GizWifiSDK
//
//  Created by Tom on 2017/6/20.
//  Copyright © 2017年 gizwits. All rights reserved.
//

#import <GizWifiSDK/GizDeviceJointActionRule.h>

@class GizWifiDevice;

@interface GizDeviceJointAction : NSObject

/** 联动ID，是jointActionOwner创建场景时分配的唯一标识 */
@property (strong, nonatomic, readonly) NSString * _Nonnull JointActionID;
/** 联动的管理者，这个管理者是设备对象，用来创建、删除、维护联动信息。目前jointActionOwner只支持中控设备 */
@property (strong, nonatomic, readonly) GizWifiDevice * _Nullable jointActionOwner;
/** 联动名称 */
@property (strong, nonatomic, readonly) NSString * _Nonnull jointActionName;
/** 是否开启联动。YES为开启，NO为关闭 */
@property (assign, nonatomic, readonly) BOOL enabled;
 /** 联动规则，GizDeviceJointActionRule对象 */
@property (strong, nonatomic, readonly) GizDeviceJointActionRule * _Nullable jointActionRule;

@end
