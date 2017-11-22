//
//  YKOneKeyMatchViewController.h
//  YKCenterDemo
//
//  Created by Don on 2017/10/25.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
@class YKRemoteDeviceBrand;
@class YKRemoteDeviceType;

@interface YKOneKeyMatchViewController : UITableViewController
@property (nonatomic, strong) YKRemoteDeviceType *deviceType;
@property (nonatomic, strong) YKRemoteDeviceBrand *deviceBrand;
@end
