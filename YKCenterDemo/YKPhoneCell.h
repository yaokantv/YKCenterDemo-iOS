//
//  YKPhoneCell.h
//  YKCenterDemo
//
//  Created by Don on 2017/9/6.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol YKPhoneCellDelegate <NSObject>
@required
- (void)didSendCodeBtnPressed;
@end


@interface YKPhoneCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UITextField *textInput;
@property (weak, nonatomic) IBOutlet UIButton *getVerifyCodeBtn;
@property (assign, nonatomic) id delegate;

@end

