//
//  YKRegisterViewController.m
//  YKCenterDemo
//
//  Created by Don on 2017/3/10.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKRegisterViewController.h"
#import "YKPasswordCell.h"
#import "YKTextCell.h"
#import "YKCenterCommon.h"
#import <MBProgressHUD/MBProgressHUD.h>
#import <YKCenterSDK/YKCenterSDK.h>

@interface YKRegisterViewController () <UITextFieldDelegate, UITableViewDelegate, UITableViewDataSource>

@property (strong, nonatomic) YKPasswordCell *passwordCell;
@property (strong, nonatomic) YKTextCell *textCell;
@property (weak, nonatomic) IBOutlet UIButton *registerBtn;

@end

@implementation YKRegisterViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


#pragma mark - table view
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 2;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    //    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"CellIdentifier"];
    //
    //    if (cell == nil) {
    //        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"CellIdentifier"];
    //    }
    //    cell.textLabel.text = @"";
    //    return cell;
    
    switch (indexPath.row) {
        case 0:
            if (nil == self.textCell) {
                self.textCell = YKGetControllerWithClass([YKTextCell class], tableView, @"textCell");
                self.textCell.textInput.delegate = self;
                self.textCell.textInput.returnKeyType = UIReturnKeyNext;
            }
            return self.textCell;
        case 1:
            if (nil == self.passwordCell) {
                self.passwordCell = YKGetControllerWithClass([YKPasswordCell class], tableView, @"passwordCell");
                self.passwordCell.textPassword.delegate = self;
                self.passwordCell.textPassword.returnKeyType = UIReturnKeyDone;
                [self.passwordCell.btnShowText addTarget:self action:@selector(onShowText) forControlEvents:UIControlEventTouchUpInside];
                
            }
            return self.passwordCell;
        default:
            break;
    }
    return nil;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

#pragma mark - IBAction
/**
 发送手机验证码
 */
- (void)didSendCodeBtnPressed {
    if([YKCenterCommon isMobileNumber:self.textCell.textInput.text]) {
        [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        [YKCenterSDK sendPhoneSMSCode:self.textCell.textInput.text
                           completion:^(NSError * _Nonnull result, NSString * _Nonnull token) {
                               [MBProgressHUD hideHUDForView:self.view animated:YES];
                           }];
    }
    else {
        [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"the phone number is incorrect", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
    }
}

#pragma mark - Event
- (void)onClearPassword {
    self.passwordCell.textPassword.text = @"";
}

- (void)onShowText {
    [self onTap];
    [self setShowText:self.passwordCell.textPassword.secureTextEntry];
}

- (IBAction)onTap {
    [self.passwordCell.textPassword resignFirstResponder];
}

- (void)setShowText:(BOOL)isShow {
    UITextField *textPassword = self.passwordCell.textPassword;
    textPassword.secureTextEntry = !isShow;
    self.passwordCell.btnShowText.selected = isShow;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [self.passwordCell.textPassword resignFirstResponder];
    return NO;
}

- (IBAction)registerBtnPressed:(id)sender {
    if(self.textCell.textInput.text.length < 1) {
        [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"Username can not be empty", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
    }
    else if (self.passwordCell.textPassword.text.length < 6) {
        [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"The password must be at least six characters", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
        return;
    }

    [MBProgressHUD showHUDAddedTo:self.view animated:YES];

    // 注意：此方法是普通用户名注册，非手机或邮箱注册
    [[YKCenterSDK sharedInstance] reg:self.textCell.textInput.text
                             password:self.passwordCell.textPassword.text
                              handler:^(NSError * _Nonnull result, NSString * _Nonnull uid, NSString * _Nonnull token)
     {
         [MBProgressHUD hideHUDForView:self.view animated:YES];
         if (result.code == 0) {
             [YKCenterCommon sharedInstance].loginStatus  = YKLoginUser;
             [self.navigationController popViewControllerAnimated:YES];
         }
         else {
             NSString *info = [NSString stringWithFormat:@"%@\n%@ - %@", NSLocalizedString(@"Registration failed", nil), @(result.code), [result.userInfo objectForKey:@"NSLocalizedDescription"]];
             [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:info delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
         }
     }];
}


@end
