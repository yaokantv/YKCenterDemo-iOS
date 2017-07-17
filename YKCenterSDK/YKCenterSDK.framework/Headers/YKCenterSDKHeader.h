//
//  YKCenterSDKHeader.h
//  Pods
//
//  Created by Don on 2017/1/16.
//
//

#ifndef YKCenterSDKHeader_h
#define YKCenterSDKHeader_h

#import <YKCenterSDK/YKRemoteDeviceType.h>
#import <YKCenterSDK/YKRemoteDeviceBrand.h>
#import <YKCenterSDK/YKRemoteMatchDeviceKey.h>
#import <YKCenterSDK/YKRemoteMatchDevice.h>
#import <YKCenterSDK/YKRemoteDevice+YKDB.h>
#import <YKCenterSDK/YKRemoteDeviceKey+CoreDataClass.h>
#import "YKRemoteDeviceKey+YKDB.h"

typedef NS_ENUM(NSInteger, RemoteDeviceType){
    kDeviceTypeUnkown = -1,
    kDeviceTypeCustom = 0,          // 自定义
    kDeviceAVType = 1,              // 有线电视机顶盒
    kDeviceTVType = 2,              // 电视机
    kDeviceDVDType = 3,             // DVD播放机
    kDeviceIPTVType = 4,            // IPTV机顶盒
    kDevicePRType = 5,              // 投影仪
    kDeviceFANType = 6,             // 风扇
    kDeviceACType = 7,              // 空调
    kDeviceLightType = 8,           // 智能灯泡
    kDeviceNetAVBoxType = 10,       // 互联网机顶盒
    kDeviceSatelliteType = 11,      // 卫星电视
    kDeviceSweeperType =  12,       // 扫地机
    kDeviceSoundType = 13,          // 音响
    kDeviceCameraType = 14,         // 照相机
    kDeviceAirPurifierType = 15,    // 空气净化器
    kDeviceFootbathType = 16,       // 洗脚盆
    kDeviceCarAudioType = 17,       // 汽车音响
};


#endif /* YKCenterSDKHeader_h */
