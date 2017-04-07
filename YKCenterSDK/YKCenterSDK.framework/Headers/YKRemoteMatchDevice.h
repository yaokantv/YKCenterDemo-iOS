//
//  YKRemoteMatchDevice.h
//  Pods
//
//  Created by Don on 2017/1/18.
//
//

#import <Foundation/Foundation.h>

@class YKRemoteMatchDeviceKey;

@interface YKRemoteMatchDevice : NSObject

@property (nonatomic, copy)     NSString *model;            // be_rmodel 被遥控型号
@property (nonatomic, copy)     NSString *rid;              // rid
@property (nonatomic, copy)     NSString *rmodel;           // rmodel 遥控型号
@property (nonatomic, copy)     NSString *name;             // name
@property (nonatomic, assign)   NSInteger order;            // order
@property (nonatomic, assign)   NSInteger v;                // 遥控码版本
@property (nonatomic, assign)   NSInteger typeId;           // 设备类型 id

@property (nonatomic, strong)   NSArray<YKRemoteMatchDeviceKey *> *matchKeys;   // 匹配的按键数组

@end
