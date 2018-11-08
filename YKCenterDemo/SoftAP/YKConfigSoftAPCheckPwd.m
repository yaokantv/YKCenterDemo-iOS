//
//  YKConfigSoftAPCheckPwd.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/16.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKConfigSoftAPCheckPwd.h"
#import "YKSSIDCell.h"
#import "YKPasswordCell.h"
#import "YKCenterCommon.h"
#import "YKConfigSoftAPStart.h"

@interface YKConfigSoftAPCheckPwd () <UITableViewDataSource, UITableViewDelegate, UITextFieldDelegate, UIAlertViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;

@property (strong, nonatomic) YKSSIDCell *ssidCell;
@property (strong, nonatomic) YKPasswordCell *passwordCell;

@property (assign, nonatomic) CGFloat top;
@property (assign) BOOL isFirstRun;//检查密码有区分是第一次还是其他，第一次一定显示的是上次配置的ssid和密码

@property (weak, nonatomic) IBOutlet UIButton *nextBtn;

@end

@implementation YKConfigSoftAPCheckPwd

- (void)willEnterForeground {
    NSString *ssid = @"";
    
    if (self.isFirstRun) {
        self.isFirstRun = NO;
        ssid = [YKCenterCommon sharedInstance].ssid;
    } else {
        ssid = YKGetCurrentSSID();
    }
    
    self.ssidCell.textSSID.text = ssid;
    self.passwordCell.textPassword.text = [[YKCenterCommon sharedInstance] getPasswrodFromSSID:ssid];
    [self.passwordCell.textPassword becomeFirstResponder];
    [self setShowText:YES];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.tableView.scrollEnabled = NO;
    self.top = self.navigationController.navigationBar.translucent ? 0 : 64;
    self.isFirstRun = YES;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(willEnterForeground) name:UIApplicationWillEnterForegroundNotification object:nil];
    [self.tableView reloadData];
}

- (void)viewWillDisappear:(BOOL)animated {

    [super viewWillDisappear:animated];
    [self onTap];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationWillEnterForegroundNotification object:nil];
    
    [self.passwordCell.textPassword resignFirstResponder];
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

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    switch (indexPath.row) {
        case 0:
            if (nil == self.ssidCell) {
                self.ssidCell = YKGetControllerWithClass([YKSSIDCell class], tableView, @"ssidCell");
                self.ssidCell.textSSID.delegate = self;
                self.ssidCell.textSSID.returnKeyType = UIReturnKeyNext;
                self.ssidCell.textSSID.enabled = NO;
            }
            return self.ssidCell;
        case 1:
            if (nil == self.passwordCell) {
                self.passwordCell = YKGetControllerWithClass([YKPasswordCell class], tableView, @"passwordCell");
                self.passwordCell.textPassword.delegate = self;
                self.passwordCell.textPassword.returnKeyType = UIReturnKeyDone;
//                [self.passwordCell.btnClearPassword addTarget:self action:@selector(onClearPassword) forControlEvents:UIControlEventTouchUpInside];
                [self.passwordCell.btnShowText addTarget:self action:@selector(onShowText) forControlEvents:UIControlEventTouchUpInside];
                
                //加载初始化的信息
                [self willEnterForeground];
            }
            return self.passwordCell;
        default:
            break;
    }
    return nil;
}

- (BOOL)tableView:(UITableView *)tableView shouldHighlightRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.row == 0) {
        return YES;
    }
    return NO;
}

#pragma mark - text field
- (void)textFieldDidBeginEditing:(UITextField *)textField {
    if (textField == self.ssidCell.textSSID) {
        [self setViewY:self.top];
    } else {
        [self setViewY:self.top];
    }
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    if (textField == self.ssidCell.textSSID) {
        [self.passwordCell.textPassword becomeFirstResponder];
    } else {
        [self.passwordCell.textPassword resignFirstResponder];
        [self setViewY:self.top];
    }
    return NO;
}

#pragma mark - alert
- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    if (1 == buttonIndex) {
        [self onPushToSoftAPStart];
    }
}

#pragma mark - view animation
- (void)setViewY:(CGFloat)y {
    //4s 可能出现问题，先屏蔽
//    [UIView beginAnimations:nil context:nil];
//    [UIView setAnimationsEnabled:YES];
//    CGRect rc = self.view.frame;
//    rc.origin.y = y;
//    self.view.frame = rc;
//    [UIView commitAnimations];
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

- (void)onPushToSoftAPStart {
    if (self.navigationController.viewControllers.lastObject != self) {
        return;
    }
    
    NSMutableArray *mCtrls = [self.navigationController.viewControllers mutableCopy];
    for (NSInteger i = mCtrls.count; i > 0; i--) {
        UIViewController *viewController = mCtrls[i-1];
        if ([viewController isMemberOfClass:[YKConfigSoftAPStart class]]) {
            break;
        }
        [mCtrls removeObject:viewController];
    }
    
    YKCenterCommon *dataCommon = [YKCenterCommon sharedInstance];
    dataCommon.ssid = self.ssidCell.textSSID.text;
    if (nil == dataCommon.ssid) {
        dataCommon.ssid = @"";
    }
    
    [dataCommon saveSSID:dataCommon.ssid key:self.passwordCell.textPassword.text];
    
    [self.navigationController setViewControllers:mCtrls animated:YES];
}

- (IBAction)onNext:(id)sender {
    if (0 == self.passwordCell.textPassword.text.length) {
        SHOW_ALERT_EMPTY_PASSWORD(self);
    } else {
        [self onPushToSoftAPStart];
    }
}

- (IBAction)onBack:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}

@end
