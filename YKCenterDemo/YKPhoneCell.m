//
//  YKPhoneCell.m
//  YKCenterDemo
//
//  Created by Don on 2017/9/6.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKPhoneCell.h"

@implementation YKPhoneCell

- (void)awakeFromNib {
    [super awakeFromNib];
    
    self.selectionStyle = UITableViewCellSelectionStyleNone;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (void)onTap {
    NSURL *url = [NSURL URLWithString:@"prefs:root=WIFI"];
    if ([[UIApplication sharedApplication] canOpenURL:url]) {
        [[UIApplication sharedApplication] openURL:url];
    } else {
        [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:@"请手动点击桌面的 '设置' 图标，然后选择 '无线局域网'。" delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil] show];
    }
    
    [self setSelected:NO animated:NO];
}

- (IBAction)sendCodeBtnPressed:(id)sender {
    [self.delegate didSendCodeBtnPressed];
}

@end
