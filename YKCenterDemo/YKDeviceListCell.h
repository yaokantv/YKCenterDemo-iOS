//
//  YKDeviceListCell.h
//  YKCenterDemo
//
//  Created by Don on 2017/1/12.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface YKDeviceListCell : UITableViewCell

@property (nonatomic, weak) IBOutlet UILabel *title;
@property (nonatomic, weak) IBOutlet UILabel *mac;
@property (nonatomic, weak) IBOutlet UILabel *lan;

@end
