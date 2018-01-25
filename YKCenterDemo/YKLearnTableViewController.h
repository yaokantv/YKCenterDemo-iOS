//
//  YKLearnTableViewController.h
//  YKCenterDemo
//
//  Created by dong on 2017/11/28.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, YKLearnType) {
    YKLearnTypeIR,
    YKLearnTypeRF,
};

@interface YKLearnTableViewController : UITableViewController

@property (nonatomic, assign) YKLearnType learnType;

@end
