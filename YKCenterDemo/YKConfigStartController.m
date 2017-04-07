//
//  YKConfigStartController.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/16.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKConfigStartController.h"
#import "YKSSIDCell.h"
#import "YKPasswordCell.h"
#import "YKCenterCommon.h"

@interface YKConfigStartController () <UITableViewDataSource, UITableViewDelegate,
UITextFieldDelegate, UIAlertViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;

@property (strong, nonatomic) YKSSIDCell *ssidCell;
@property (strong, nonatomic) YKPasswordCell *passwordCell;

@property (assign, nonatomic) CGFloat top;

@property (weak, nonatomic) IBOutlet UIButton *nextBtn;

@end

@implementation YKConfigStartController

- (void)didEnterBackground {
    [self.passwordCell.textPassword resignFirstResponder];
}

- (void)didBecomeActive {
    if ([UIDevice currentDevice].systemVersion.floatValue < 8.0) {
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            usleep(500000);
            dispatch_async(dispatch_get_main_queue(), ^{
                [self.passwordCell.textPassword becomeFirstResponder];
            });
        });
    } else {
        [self.passwordCell.textPassword becomeFirstResponder];
    }
    [self getCurrentConfig];
}

- (void)getCurrentConfig {
    NSString *ssid = YKGetCurrentSSID();
    self.ssidCell.textSSID.text = ssid;
    self.passwordCell.textPassword.text = [[YKCenterCommon sharedInstance] getPasswrodFromSSID:ssid];
    
    if (0 < self.passwordCell.textPassword.text.length) {
        [self setShowText:NO];
    } else {
        [self setShowText:YES];
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];

    self.tableView.scrollEnabled = NO;
    self.top = self.navigationController.navigationBar.translucent ? 0 : 64;
    [self.navigationController.navigationBar setHidden:NO];
    
    if (0 == YKGetCurrentSSID().length) {
        [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"No open Wi-Fi", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil] show];
    }
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didBecomeActive) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didEnterBackground) name:UIApplicationDidEnterBackgroundNotification object:nil];
    [self.tableView reloadData];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [self onTap];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationDidEnterBackgroundNotification object:nil];

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
                [self getCurrentConfig];
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
    if ([[UIScreen mainScreen] bounds].size.height == 480) {
        [self setViewY:-118];
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

#pragma mark - alert view
- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    if (1 == buttonIndex) {
//        if (ALERT_TAG_CANCEL_CONFIG == alertView.tag) {

//        } else if (ALERT_TAG_EMPTY_PASSWORD == alertView.tag) {
//            [self onPushToNextPage];
//        }
    }
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

- (void)onPushToNextPage {
    YKCenterCommon *dataCommon = [YKCenterCommon sharedInstance];
    [dataCommon saveSSID:self.ssidCell.textSSID.text
                     key:self.passwordCell.textPassword.text];
    dataCommon.ssid = self.ssidCell.textSSID.text;
    [self performSegueWithIdentifier:@"showConfig2" sender:nil];
}

- (IBAction)onNext:(id)sender {
    if (0 == self.passwordCell.textPassword.text.length) {
        // password is empty
    } else {
        [self onPushToNextPage];
    }
}

- (IBAction)onTap {
    [self setViewY:self.top];
    [self.passwordCell.textPassword resignFirstResponder];
}

- (IBAction)onCancel:(id)sender {
//    SHOW_ALERT_CANCEL_CONFIG(self);
}

@end
