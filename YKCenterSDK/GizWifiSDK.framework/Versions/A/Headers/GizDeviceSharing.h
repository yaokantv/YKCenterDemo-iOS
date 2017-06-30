//
//  GizDeviceSharing.h
//  GizWifiSDK
//
//  Created by Tom on 2016/12/7.
//  Copyright © 2016年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <GizWifiSDK/GizDeviceSharingInfo.h>
#import <GizWifiSDK/GizMessage.h>

@protocol GizDeviceSharingDelegate <NSObject>
@optional

/*
 获取设备已绑定用户的回调
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败。失败时，bindUsers回调参数为 nil
 @param deviceID 发起查询的设备ID
 @param bindUsers NSString类型数组，设备的已绑定用户列表。失败时为nil
 @see 触发函数：[GizDeviceSharing getBindingUsers:deviceID:];
 @see GizWifiErrorCode
 */
- (void)didGetBindingUsers:(NSError *)result deviceID:(NSString *)deviceID bindUsers:(NSArray *)bindUsers;

/*
 解绑设备已绑用户的回调
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param deviceID 解绑用户的设备ID
 @param guestUID 解绑的用户ID
 @see 触发函数：[GizDeviceSharing unbindUser:deviceID:guestUID:];
 @see GizWifiErrorCode
 */
- (void)didUnbindUser:(NSError *)result deviceID:(NSString *)deviceID guestUID:(NSString *)guestUID;

/*
 获取分享邀请列表的回调
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param deviceID 查询分享邀请的设备ID
 @param deviceSharingInfos GizDeviceSharingInfo类对象数组，分享邀请列表。如果失败，此参数为nil
 @see 触发函数：[GizDeviceSharing getDeviceSharingInfos:sharingType:deviceID:];
 @see GizWifiErrorCode
 */
- (void)didGetDeviceSharingInfos:(NSError *)result deviceID:(NSString *)deviceID deviceSharingInfos:(NSArray *)deviceSharingInfos;

/*
 创建分享邀请的回调
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param deviceID 创建分享邀请的设备ID
 @param sharingID 分享邀请创建成功时被分配的ID。失败时该参数为nil
 @param QRCodeImage 二维码图片内容。二维码邀请创建失败或者账号分享时，该参数为nil
 @see 触发函数：[GizDeviceSharing sharingDevice:deviceID:sharingWay:guestUser:guestUserType:];
 @see GizWifiErrorCode
 */
- (void)didSharingDevice:(NSError *)result deviceID:(NSString *)deviceID sharingID:(NSInteger)sharingID QRCodeImage:(UIImage *)QRCodeImage;

/*
 撤回分享邀请的回调
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param sharingID 撤回的分享邀请ID
 @see 触发函数：[GizDeviceSharing revokeDeviceSharing:sharingID:];
 @see GizWifiErrorCode
 */
- (void)didRevokeDeviceSharing:(NSError *)result sharingID:(NSInteger)sharingID;

/*
 接受分享邀请的回调
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param sharingID 接受或拒绝的邀请ID
 @see 触发函数：[GizDeviceSharing acceptDeviceSharing:sharingID:accept:];
 @see GizWifiErrorCode
 */
- (void)didAcceptDeviceSharing:(NSError *)result sharingID:(NSInteger)sharingID;

/*
 查看二维码邀请信息的回调
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param userName 创建分享邀请的owner用户名
 @param productName 设备的产品名称
 @param deviceAlias 设备的别名
 @param expiredAt 分享邀请的过期时间
 @see 触发函数：[GizDeviceSharing checkDeviceSharingInfoByQRCode:QRCode:];
 @see GizWifiErrorCode
 */
- (void)didCheckDeviceSharingInfoByQRCode:(NSError *)result userName:(NSString *)userName productName:(NSString *)productName deviceAlias:(NSString *)deviceAlias expiredAt:(NSString *)expiredAt;

/*
 扫码接受分享邀请的回调
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @see 触发函数：[GizDeviceSharing acceptDeviceSharingByQRCode:QRCode:];
 @see GizWifiErrorCode
 */
- (void)didAcceptDeviceSharingByQRCode:(NSError *)result;

/*
 修改分享邀请别名的回调
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param messageList 修改别名的分享邀请ID
 @see 触发函数：[GizDeviceSharing modifySharingInfo:sharingID:sharingAlias:];
 @see GizWifiErrorCode
 */
- (void)didModifySharingInfo:(NSError *)result sharingID:(NSInteger)sharingID;

/*
 查询消息列表的回调
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param messageList 查询的消息列表
 @see 触发函数：[GizDeviceSharing queryMessageList:messageType:];
 @see GizWifiErrorCode
 */
- (void)didQueryMessageList:(NSError *)result messageList:(NSArray *)messageList;

/*
 标记或删除消息的回调
 @param result 详细见 GizWifiErrorCode 枚举定义。GIZ_SDK_SUCCESS 表示成功，其他为失败
 @param messageID 标记已读或删除的消息ID
 @see 触发函数：[GizDeviceSharing markMessageStatus:messageID:messageStatus:];
 @see GizWifiErrorCode
 */
- (void)didMarkMessageStatus:(NSError *)result messageID:(NSString *)messageID;

@end

/*
 GizDeviceSharing类为 APP 开发者提供设备分享功能，用户绑定设备后，其他人可以通过设备分享的方式使用设备。与设备分享的有关的用户分为四类：normal、specail、owner、guest，下面简单介绍这几类用户的权限：
 normal：设备没有被分享过时，任何已绑定的用户都是normal用户，设备仍然可以被其他用户绑定；
 special：只有第一个绑定设备的用户才可以分享设备，并成为owner
 owner：用户有owner后，其他用户不可以再绑定设备，只能通过分享的方式使用设备。owner用户可以解绑所有其他已绑定用户
 guest：接受分享邀请的用户是guest用户
 */
@interface GizDeviceSharing : NSObject

/*
 设置定时任务委托
 @param delegate 设备分享的委托
 */
+ (void)setDelegate:(id <GizDeviceSharingDelegate>)delegate;

/*
 查询设备的已绑定用户列表。只有owner用户才能查询设备的已绑用户
 @param token 用户token
 @param deviceID 要查询的设备did
 @see 对应的回调接口：[GizDeviceSharingDelegate didGetBindingUsers:deviceID:bindUsers:];
 */
+ (void)getBindingUsers:(NSString *)token deviceID:(NSString *)deviceID;

/*
 解绑设备的已绑定用户。只有owner才能解绑其他已绑用户
 @param token 用户token
 @param deviceID 要解绑用户的设备ID
 @see 对应的回调接口：[GizDeviceSharingDelegate didUnbindUser:deviceID:guestUID:];
 */
+ (void)unbindUser:(NSString *)token deviceID:(NSString *)deviceID guestUID:(NSString *)guestUID;

/*
 查询设备的分享邀请列表。可以查询自己发起的分享邀请，或者查询分享给自己的分享邀请，owner和guest用户都可以查询
 @param token 用户token
 @param sharingType 要查询的分享邀请类型是分享给自己的还是自己分享给别人的，见枚举定义GizDeviceSharingType
 @param deviceID 查询分享邀请的设备ID。如果是guest用户，可查询所有邀请。如果是owner用户，可以指定设备ID查询，也可以不指定设备ID查询
 @see 对应的回调接口：[GizDeviceSharingDelegate didGetDeviceSharingInfos:deviceID:deviceSharingInfos:];
 */
+ (void)getDeviceSharingInfos:(NSString *)token sharingType:(GizDeviceSharingType)sharingType deviceID:(NSString *)deviceID;

/*
 创建分享邀请。special和owner用户可以通过账号分享或二维码分享的方式分享设备。账号分享邀请24小时后失效，二维码邀请15分钟后失效
 @param token 用户token
 @param deviceID 创建分享邀请的设备ID
 @param sharingWay 分享邀请是通过账号分享还是二维码分享，见GizDeviceSharingWay枚举定义
 @param guestUser 如果是账号分享，要指定用户名，用户名可以是普通用户名、手机号、邮箱、用户的uid。如果是二维码分享，该参数可传nil
 @param guestUserType 账号分享时，该参数需要指定用户名是哪种类型，见GizUserAccountType枚举定义。如果是通过用户的uid分享的，此变量应为GizUserOther，其他按照对应的用户类型传值
 @see 对应的回调接口：[GizDeviceSharingDelegate didSharingDevice:deviceID:sharingID:QRCodeImage:];
 */
+ (void)sharingDevice:(NSString *)token deviceID:(NSString *)deviceID sharingWay:(GizDeviceSharingWay)sharingWay guestUser:(NSString *)guestUser guestUserType:(GizUserAccountType)guestUserType;

/*
 撤回分享邀请。只有owner才能撤回自己的分享邀请，已经发出的分享邀请，可以随时撤回。一旦撤回成功，guest用户会被解绑不能使用该设备
 @param token 用户token
 @param sharingID 要撤回的分享邀请ID
 @see 对应的回调接口：[GizDeviceSharingDelegate didRevokeDeviceSharing:sharingID:];
 */
+ (void)revokeDeviceSharing:(NSString *)token sharingID:(NSInteger)sharingID;

/*
 接受分享邀请。owner用户以账号方式分享设备后，guest账号可以接受或拒绝邀请
 @param token 用户token
 @param sharingID 要接受的分享邀请ID
 @param accept 接受或拒绝邀请。YES表示接受，NO表示拒绝
 @see 对应的回调接口：[GizDeviceSharingDelegate didAcceptDeviceSharing:sharingID:];
 */
+ (void)acceptDeviceSharing:(NSString *)token sharingID:(NSInteger)sharingID accept:(BOOL)accept;

/*
 查看二维码邀请信息。owner用户不能查看二维码邀请信息
 @param token 用户token
 @param QRCode 二维码邀请内容。App扫描邀请二维码时，按照以下格式解析出type和code内容：type=share&code=xxxxxxxxxx。把解析出来的code内容传入此参数
 @see 对应的回调接口：[GizDeviceSharingDelegate didCheckDeviceSharingInfoByQRCode:userName:productName:deviceAlias:expiredAt:];
 */
+ (void)checkDeviceSharingInfoByQRCode:(NSString *)token QRCode:(NSString *)QRCode;

/*
 接受二维码分享邀请。owner用户不能调用此接口
 @param token 用户token
 @param QRCode 二维码邀请内容。App扫描邀请二维码时，按照以下格式解析出type和code内容：type=share&code=xxxxxxxxxx。把解析出来的code内容传入此参数
 @see 对应的回调接口：[GizDeviceSharingDelegate didAcceptDeviceSharingByQRCode:];
 */
+ (void)acceptDeviceSharingByQRCode:(NSString *)token QRCode:(NSString *)QRCode;

/*
 修改分享邀请别名
 @param token 用户token
 @param sharingID 要修改的分享邀请ID
 @param sharingAlias 要修改的分享邀请别名
 @see 对应的回调接口：[GizDeviceSharingDelegate didModifySharingInfo:sharingID:];
 */
+ (void)modifySharingInfo:(NSString *)token sharingID:(NSInteger)sharingID sharingAlias:(NSString *)sharingAlias;

/*
 查询消息列表。可查询分享消息
 @param token 用户token
 @param messageType 要查询的消息类型，见GizMessageType枚举定义
 @see 对应的回调接口：[GizDeviceSharingDelegate didQueryMessageList:messageList:];
 */
+ (void)queryMessageList:(NSString *)token messageType:(GizMessageType)messageType;

/*
 标记消息已读或删除
 @param token 用户token
 @param messageID 要标记或删除的消息ID
 @param messageStatus 标记为已读或者删除，见GizMessageStatus枚举定义
 @see 对应的回调接口：[GizDeviceSharingDelegate didMarkMessageStatus:messageID:];
 */
+ (void)markMessageStatus:(NSString *)token messageID:(NSString *)messageID messageStatus:(GizMessageStatus)messageStatus;

@end
