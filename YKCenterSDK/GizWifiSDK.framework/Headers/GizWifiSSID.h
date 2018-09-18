//
//  GizWifiSSID.h
//  GizWifiSDK
//
//  Created by Tom on 15/7/9.
//  Copyright (c) 2015年 gizwits. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 GizWifiSSID类为APP开发者提供获取设备在SoftAP模式下能搜索出的wifi信息
 */
@interface GizWifiSSID : NSObject

- (instancetype _Nullable )init NS_UNAVAILABLE;

/*
 SSID名。我们连接一个Wi-Fi热点时，可以搜索到的名字
 */
@property (strong, nonatomic, readonly) NSString * _Nullable ssid;

/*
 热点对应的信号强度。取值范围 0-100
 */
@property (assign, nonatomic, readonly) NSInteger rssi;

/** @deprecated 此变量已废弃，不再提供支持。替代变量为 ssid */
@property (strong, nonatomic, readonly) NSString * _Null_unspecified name DEPRECATED_MSG_ATTRIBUTE("Please use ssid instead") NS_SWIFT_UNAVAILABLE("");

@end
