//
//  YKRemoteDeviceBrand.h
//  Pods
//
//  Created by Don on 2017/1/17.
//
//

#import <Foundation/Foundation.h>

@interface YKRemoteDeviceBrand : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, assign) NSInteger common;     // 常用品牌标识    1: 常用 ， 0： 不常用
@property (nonatomic, assign) NSInteger bid;        // brand id

@end
