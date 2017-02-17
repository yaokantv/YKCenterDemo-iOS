//
//  YKMatchDeviceTableViewController.h
//  YKCenterDemo
//
//  Created by Don on 2017/1/17.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@class YKRemoteDeviceType;
@class YKRemoteDeviceBrand;

@interface YKMatchDeviceTableViewController : UITableViewController

@property (nonatomic, strong) YKRemoteDeviceType *deviceType;
@property (nonatomic, strong) YKRemoteDeviceBrand *deviceBrand;

@end
