//
//  YKForgetViewController.m
//  YKCenterDemo
//
//  Created by Don on 2017/9/6.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKForgetViewController.h"
#import "YKCenterCommon.h"
#import "YKPasswordCell.h"
#import "YKPhoneCell.h"
#import "YKVerificationCell.h"
#import <MBProgressHUD/MBProgressHUD.h>
#import <YKCenterSDK/YKCenterSDK.h>

@interface YKForgetViewController () <UITextFieldDelegate>
@property (strong, nonatomic) YKPhoneCell *phoneCell;
@property (strong, nonatomic) YKVerificationCell *verfiyCell;
@property (strong, nonatomic) YKPasswordCell *passwordCell;

@property (assign, nonatomic) NSInteger verifyCodeCounter;
@property (strong, nonatomic) NSTimer *verifyTimer;

@property (weak, nonatomic) IBOutlet UIButton *forgetBtn;
@end

@implementation YKForgetViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.automaticallyAdjustsScrollViewInsets = false;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    [self.phoneCell.textInput becomeFirstResponder];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    [self.verifyTimer invalidate];
    self.verifyTimer = nil;
    self.verifyCodeCounter = 0;
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
    return 3;
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
            if (nil == self.phoneCell) {
                self.phoneCell = YKGetControllerWithClass([YKPhoneCell class], tableView, @"phoneCell");
                self.phoneCell.textInput.delegate = self;
                self.phoneCell.textInput.returnKeyType = UIReturnKeyNext;
                self.phoneCell.delegate = self;
            }
            return self.phoneCell;
        case 1:
            if (nil == self.verfiyCell) {
                self.verfiyCell = YKGetControllerWithClass([YKVerificationCell class], tableView, @"verfiyCell");
                self.verfiyCell.textInput.delegate = self;
                self.verfiyCell.textInput.returnKeyType = UIReturnKeyNext;
            }
            return self.verfiyCell;
        case 2:
            if (nil == self.passwordCell) {
                self.passwordCell = YKGetControllerWithClass([YKPasswordCell class], tableView, @"passwordCell");
                self.passwordCell.textPassword.delegate = self;
                self.passwordCell.textPassword.returnKeyType = UIReturnKeyDone;
                //                [self.passwordCell.btnClearPassword addTarget:self action:@selector(onClearPassword) forControlEvents:UIControlEventTouchUpInside];
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

- (void)didSendCodeBtnPressed {
    if([YKCenterCommon isMobileNumber:self.phoneCell.textInput.text]) {
        [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        [YKCenterSDK sendPhoneSMSCode:self.phoneCell.textInput.text
                           completion:^(NSError * _Nonnull result, NSString * _Nonnull token) {
                               [MBProgressHUD hideHUDForView:self.view animated:YES];
                               
                               if (token) {
                                   [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"Phone verification code sent successfully", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
                                   [self.phoneCell.textInput setEnabled:NO];
                                   [self.phoneCell.textInput setTextColor:[UIColor grayColor]];
                                   [self.verfiyCell.textInput becomeFirstResponder];
                                   
                                   self.verifyCodeCounter = 60;
                                   self.verifyTimer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(updateVerifyButton) userInfo:nil repeats:YES];
                               } else {
                                   NSString *info = [NSString stringWithFormat:@"%@\n%@ - %@", NSLocalizedString(@"Phone verification code sent failure", nil), @(result.code), [result.userInfo objectForKey:@"NSLocalizedDescription"]];
                                   [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:info delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
                               }
                           }];
    }
    else {
        [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"the phone number is incorrect", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
    }
}

- (IBAction)retsetBtnPressed:(id)sender {
    if(![YKCenterCommon isMobileNumber:self.phoneCell.textInput.text]) {
        [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"the phone number is incorrect", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
        return;
    }
    if (self.verfiyCell.textInput.text.length != 6) {
        [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"Verification code error", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
        return;
    }
    if (self.passwordCell.textPassword.text.length < 6) {
        [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"The password must be at least six characters", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
        return;
    }
    
    [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    [YKCenterSDK resetPassword:self.phoneCell.textInput.text
                    verifyCode:self.verfiyCell.textInput.text
                   newPassword:self.passwordCell.textPassword.text
                   accountType:YKUserAccountTypePhone
                    completion:^(NSError * _Nullable result)
     {
         if (result == nil) {
             [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"Reset success", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
             [[YKCenterCommon sharedInstance] saveUserDefaults:self.phoneCell.textInput.text password:self.passwordCell.textPassword.text uid:nil token:nil];
             [self.navigationController popViewControllerAnimated:YES];
         }
         else {
             NSString *info = [NSString stringWithFormat:@"%@\n%@ - %@", NSLocalizedString(@"Reset failed", nil), @(result.code), [result.userInfo objectForKey:@"NSLocalizedDescription"]];
             [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:info delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
         }
     }];
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

#pragma mark - Others
- (void)updateVerifyButton {
    if(self.verifyCodeCounter == 0) {
        [self.verifyTimer invalidate];
        self.phoneCell.getVerifyCodeBtn.enabled = true;
        [self.phoneCell.getVerifyCodeBtn setTitle:NSLocalizedString(@"Get verification code", nil) forState:UIControlStateNormal];
        self.phoneCell.getVerifyCodeBtn.backgroundColor = [UIColor colorWithRed:0.980 green:0.875 blue:0.275 alpha:1];
        [self.phoneCell.textInput setEnabled:YES];
        [self.phoneCell.textInput setTextColor:[UIColor blackColor]];
        return;
    }
    
    NSString *title = [NSString stringWithFormat:@"%i %@", (int)self.verifyCodeCounter, NSLocalizedString(@"Try again", nil)];
    self.phoneCell.getVerifyCodeBtn.enabled = true;
    self.phoneCell.getVerifyCodeBtn.backgroundColor = [UIColor lightGrayColor];
    [self.phoneCell.getVerifyCodeBtn setTitle:title forState:UIControlStateNormal];
    self.phoneCell.getVerifyCodeBtn.enabled = false;
    
    self.verifyCodeCounter--;
}

@end
