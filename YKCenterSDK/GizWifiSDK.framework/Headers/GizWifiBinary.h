//
//  GizWifiBinary.h
//  GizWifiSDK
//
//  Created by Tom on 16/3/4.
//  Copyright © 2016年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_CLASS_DEPRECATED_IOS(1_0, 2_0, "不再提供支持，无替代类") NS_SWIFT_UNAVAILABLE("")
@interface GizWifiBinary : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (NSData *)decode:(NSString *)str DEPRECATED_MSG_ATTRIBUTE("不再提供支持，无替代接口") NS_EXTENSION_UNAVAILABLE_IOS("");
+ (NSString *)encode:(NSData *)data DEPRECATED_MSG_ATTRIBUTE("不再提供支持，无替代接口") NS_EXTENSION_UNAVAILABLE_IOS("");

@end
