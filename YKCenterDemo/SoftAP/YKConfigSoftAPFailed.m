//
//  GizConfigSoftAPFailed.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/16.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKConfigSoftAPFailed.h"
#import "YKCenterCommon.h"

@interface YKConfigSoftAPFailed () <UIAlertViewDelegate>

@property (weak, nonatomic) IBOutlet UIButton *retryBtn;

@end

@implementation YKConfigSoftAPFailed

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)onCancel:(id)sender {
    SHOW_ALERT_CANCEL_CONFIG(self);
}

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    switch (buttonIndex) {
        case 1:
//            [[YKCenterCommon sharedInstance] onCancel];
            break;
        default:
            break;
    }
}

- (IBAction)retryAction:(id)sender {
    [self.navigationController popToRootViewControllerAnimated:YES];
}

@end
