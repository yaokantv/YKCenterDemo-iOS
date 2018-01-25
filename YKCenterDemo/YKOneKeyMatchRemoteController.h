//
//  YKOneKeyMatchRemoteController.h
//  YKCenterDemo
//
//  Created by dong on 2017/11/30.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
@class YKRemoteMatchDevice;

@interface YKOneKeyMatchRemoteController : UITableViewController
@property (nonatomic, strong) NSArray <YKRemoteMatchDevice *> *devices;
@end
