//
//  YKLoginViewController.m
//  YKCenterDemo
//
//  Created by Don on 2017/3/9.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKLoginViewController.h"
#import "YKCenterCommon.h"
#import "YKTextCell.h"
#import "YKPasswordCell.h"
#import "YKViewController.h"
#import <MBProgressHUD/MBProgressHUD.h>
#import <YKCenterSDK/YKCenterSDK.h>

@interface YKLoginViewController () <UITextFieldDelegate, UITableViewDataSource, UITableViewDelegate>

@property (assign, nonatomic) IBOutlet UIView *loginBtnsBar;
@property (assign, nonatomic) IBOutlet UIView *loginQQBtn;
@property (assign, nonatomic) IBOutlet UIView *loginWechatBtn;
@property (assign, nonatomic) IBOutlet UIView *loginWeiboBtn;
@property (assign, nonatomic) IBOutlet UIView *loginSkipBtn;
@property (weak, nonatomic) IBOutlet UIButton *loginBtn;

@property (strong, nonatomic) YKTextCell *textCell;
@property (strong, nonatomic) YKPasswordCell *passwordCell;
@property (assign, nonatomic) CGFloat top;

@end

@implementation YKLoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    CAShapeLayer *shapeLayer = [CAShapeLayer layer];
    [shapeLayer setBounds:self.view.bounds];
    [shapeLayer setPosition:self.view.center];
    [shapeLayer setFillColor:[[UIColor clearColor] CGColor]];
    [shapeLayer setStrokeColor:[[UIColor colorWithRed:210/255.0 green:210/255.0 blue:210/255.0 alpha:1.0f] CGColor]];
    [shapeLayer setLineWidth:1.0f];
    [shapeLayer setLineJoin:kCALineJoinRound];
    [shapeLayer setLineDashPattern:
     [NSArray arrayWithObjects:[NSNumber numberWithInt:3], [NSNumber numberWithInt:2],nil]];
    CGMutablePathRef path = CGPathCreateMutable();
    CGPathMoveToPoint(path, NULL, 0, 0);
    CGPathAddLineToPoint(path, NULL, self.view.frame.size.width,0);
    [shapeLayer setPath:path];
    CGPathRelease(path);
    [[self.loginBtnsBar layer] addSublayer:shapeLayer];
    
    [self.loginSkipBtn addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(loginSkipBtnPressed)]];
    
    [self.loginWeiboBtn addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(regYKOnlyBtnPressed)]];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    if ([[YKCenterCommon sharedInstance] loginStatus] == YKLoginUser) {
        [self toDeviceListWithoutLogin:YES];
        return;
    }
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    NSString *username = [[NSUserDefaults standardUserDefaults] objectForKey:@"username"];
    NSString *password = [[NSUserDefaults standardUserDefaults] objectForKey:@"password"];
    if (username && [username length] > 0 && password && [password length] > 0) {
        self.textCell.textInput.text = username;
        self.passwordCell.textPassword.text = password;
    }
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

#pragma mark - view animation
- (void)setViewY:(CGFloat)y {
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationsEnabled:YES];
    CGRect rc = self.view.frame;
    rc.origin.y = y;
    self.view.frame = rc;
    [UIView commitAnimations];
}

- (void)setShowText:(BOOL)isShow {
    UITextField *textPassword = self.passwordCell.textPassword;
    textPassword.secureTextEntry = !isShow;
    self.passwordCell.btnShowText.selected = isShow;
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
    [self setViewY:self.top];
    [self.passwordCell.textPassword resignFirstResponder];
}

- (void)loginSkipBtnPressed {
    [self toDeviceListWithoutLogin:YES];
}

- (void)regYKOnlyBtnPressed {
    [self performSegueWithIdentifier:@"AddRemote" sender:self];
}

- (void)toDeviceListWithoutLogin:(BOOL)animated {
    UINavigationController *navCtrl = [[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateInitialViewController];
    YKViewController *devListCtrl = navCtrl.viewControllers.firstObject;
    devListCtrl.parent = self;
    //        devListCtrl.needRefresh = YES;
    [self.navigationController pushViewController:devListCtrl animated:animated];
}

- (void)userLogin:(BOOL)automatic {
    [YKCenterCommon sharedInstance].loginStatus = YKLoginNone;
    NSString *username = nil;
    NSString *password = nil;
    if (automatic) {
        username = [[NSUserDefaults standardUserDefaults] objectForKey:@"username"];
        password = [[NSUserDefaults standardUserDefaults] objectForKey:@"password"];
    }
    else {
        username = self.textCell.textInput.text;
        password = self.passwordCell.textPassword.text;
    }
    
    if([username isEqualToString:@""]) {
        [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"Username can not be empty", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
        return;
    }
    if (password.length < 6) {
        [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"The password must be at least six characters", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
        return;
    }
    
    [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    [[YKCenterCommon sharedInstance] saveUserDefaults:username password:password uid:nil token:nil];

    
    __weak __typeof(self)weakSelf = self;
    if ([YKCenterCommon isMobileNumber:username]) {
        [[YKCenterSDK sharedInstance] login:username
                                   password:password
         accountType:(YKUserAccountTypePhone)
                                    handler:^(NSError * _Nonnull result, NSString * _Nonnull uid, NSString * _Nonnull token)
         {
             __strong __typeof(weakSelf)strongSelf = weakSelf;
             [MBProgressHUD hideHUDForView:strongSelf.view animated:YES];
             if (result.code == 0) {
                 [[YKCenterCommon sharedInstance] setUid:uid];
                 [[YKCenterCommon sharedInstance] setToken:token];
                 [YKCenterCommon sharedInstance].loginStatus  = YKLoginUser;
                 dispatch_async(dispatch_get_main_queue(), ^{
                     [strongSelf toDeviceListWithoutLogin:YES];
                 });
             }
             else {
                 NSString *info = [NSString stringWithFormat:@"%@\n%@ - %@", NSLocalizedString(@"Login failed", nil), @(result.code), [result.userInfo objectForKey:@"NSLocalizedDescription"]];
                 [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:info delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
             }
         }];
    }
    else {
        [[YKCenterSDK sharedInstance] login:username
                                   password:password
                                    handler:^(NSError * _Nonnull result, NSString * _Nonnull uid, NSString * _Nonnull token)
         {
             __strong __typeof(weakSelf)strongSelf = weakSelf;
             [MBProgressHUD hideHUDForView:strongSelf.view animated:YES];
             if (result.code == 0) {
                 [[YKCenterCommon sharedInstance] setUid:uid];
                 [[YKCenterCommon sharedInstance] setToken:token];
                 [YKCenterCommon sharedInstance].loginStatus  = YKLoginUser;
                 [strongSelf toDeviceListWithoutLogin:YES];
             }
             else {
                 NSString *info = [NSString stringWithFormat:@"%@\n%@ - %@", NSLocalizedString(@"Login failed", nil), @(result.code), [result.userInfo objectForKey:@"NSLocalizedDescription"]];
                 [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:info delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil, nil] show];
             }
         }];
    }
}

- (IBAction)userLoginBtnPressed:(id)sender {
    [self userLogin:NO];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    if (textField == self.textCell.textInput) {
        [self.passwordCell.textPassword becomeFirstResponder];
    } else {
        [self.passwordCell.textPassword resignFirstResponder];
        [self setViewY:self.top];
    }
    return NO;
}
@end
