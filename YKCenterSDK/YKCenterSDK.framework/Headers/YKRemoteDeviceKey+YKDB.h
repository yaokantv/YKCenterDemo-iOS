//
//  YKRemoteDeviceKey+YKDB.h
//  YKCenterSDK
//
//  Created by Don on 2017/6/29.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import <YKCenterSDK/YKCenterSDK.h>

static NSString *KeyPowerOn = @"on";
static NSString *KeyPowerOff = @"off";

static NSString *ACModelAuto   = @"a";    // 自动
static NSString *ACModelCool   = @"r";    // 制冷
static NSString *ACModelDry    = @"d";    // 抽湿
static NSString *ACModelWind   = @"w";    // 送风
static NSString *ACModelHot    = @"h";    // 制热

@interface YKRemoteDeviceKey (YKDB)

+ (YKRemoteDeviceKey *)remoteDeviceKeyInRemoteDevice:(YKRemoteDevice *)remote
                                                 key:(NSString *)key;

+ (NSArray<YKRemoteDeviceKey *> *)asteriskKeysWithRemote:(YKRemoteDevice *)remote;

+ (YKRemoteDeviceKey *)remoteDeviceKeyWith:(NSArray<YKRemoteDeviceKey *> *)asteriskKeys
                                upDownWind:(NSUInteger)wind;

+ (YKRemoteDeviceKey *)remoteDeviceKeyWith:(NSArray<YKRemoteDeviceKey *> *)asteriskKeys
                             leftRightWind:(NSUInteger)wind;

+ (BOOL)supportLRSweepInRemoteDevice:(YKRemoteDevice *)remote;
+ (BOOL)supportUDSweepInRemoteDevice:(YKRemoteDevice *)remote;
@end
