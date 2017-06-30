//
//  GizWifiBinary.h
//  GizWifiSDK
//
//  Created by GeHaitong on 16/3/4.
//  Copyright © 2016年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 @deprecated GizWifiBinary 类已废弃，不再提供支持，无替代类
 */
NS_CLASS_DEPRECATED_IOS(1_0, 2_0, "GizWifiBinary is deprecated.")
@interface GizWifiBinary : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*
 @deprecated 此接口已废弃，不再提供支持，无替代接口
 */
+ (NSData *)decode:(NSString *)str DEPRECATED_ATTRIBUTE;

/*
 @deprecated 此接口已废弃，不再提供支持，无替代接口
 */
+ (NSString *)encode:(NSData *)data DEPRECATED_ATTRIBUTE;

@end
