//
//  GizConfigSoftAPWaiting.m
//  NewFlow
//
//  Created by Don on 2017/1/16.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKConfigSoftAPWaiting.h"
#import "YKCenterCommon.h"
#import <YKCenterSDK/YKCenterSDK.h>
#import <GizWifiSDK/GizWifiSDK.h>
#import "UAProgressView.h"

#define CONFIG_TIMEOUT      60

@interface YKConfigSoftAPWaiting () <UIAlertViewDelegate>

@property (strong, nonatomic) NSTimer *timer;
@property (assign, nonatomic) NSInteger timeout;

@property (weak, nonatomic) IBOutlet UILabel *textTimeoutTips;
@property (weak, nonatomic) IBOutlet UIButton *btnAutoJump;
@property (weak, nonatomic) IBOutlet UIButton *btnAutoJump2;

@property (weak, nonatomic) IBOutlet UAProgressView *progressView;

@end

@implementation YKConfigSoftAPWaiting

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 60.0, 20.0)];
    [label setTextAlignment:NSTextAlignmentCenter];
    label.userInteractionEnabled = NO; // Allows tap to pass through to the progress view.
    self.progressView.centralView = label;
    self.progressView.progressChangedBlock = ^(UAProgressView *progressView, CGFloat progress) {
        [(UILabel *)progressView.centralView setText:[NSString stringWithFormat:@"%2.0f%%", progress * 100]];
    };
    [self.progressView setProgress:0.1];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    YKCenterCommon *dataCommon = [YKCenterCommon sharedInstance];
    
    self.timeout = CONFIG_TIMEOUT;
    self.timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(onTimer) userInfo:nil repeats:YES];
    
    NSString *key = [dataCommon getPasswrodFromSSID:dataCommon.ssid];
    
    
    [YKCenterSDK configSoftAPWithSSID:dataCommon.ssid
                             password:key
                           completion:^(NSError * _Nullable error, NSString * _Nullable deviceMac)
     {
         if (!error) {
             [self onConfigSucceed:nil];
         } else {
             if ([YKGetCurrentSSID() hasPrefix:SSID_PREFIX]) {
                 [self onConfigFailed];
             } else {
                 if (GIZ_SDK_DEVICE_CONFIG_SSID_NOT_MATCHED == error.code) {
                     [self onConfigSSIDMotMatched];
                 } else {
                     [self onConfigFailed];
                 }
             }
         }
     }];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWillEnterForeground) name:UIApplicationWillEnterForegroundNotification object:nil];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [self.timer invalidate];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationWillEnterForegroundNotification object:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)setTimeout:(NSInteger)timeout {
    _timeout = timeout;
    
    float timeNow = (CONFIG_TIMEOUT-timeout);
    float secOffset = 0.0333*timeNow+(0.5*1.0/-1800)*timeNow*timeNow;
    [self.progressView setProgress:secOffset animated:YES];
    
//    [self.progressView setProgress:(CONFIG_TIMEOUT-timeout)/((float)(CONFIG_TIMEOUT)) animated:YES];
    if (timeout == 58) {
        self.textTimeoutTips.hidden = NO;
    }
}

- (void)onTimer {
    self.timeout--;
    if (0 == self.timeout) {
        [self.timer invalidate];
    }
}

- (void)onConfigSucceed:(GizWifiDevice *)device {
    [self.timer invalidate];
    
//    [[YKCenterCommon sharedInstance] cancelAlertViewDismiss];
    
    __block UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"" message:NSLocalizedString(@"Configuration success", nil) delegate:nil cancelButtonTitle:nil otherButtonTitles:nil];
    [alertView show];
//    [[YKCenterCommon sharedInstance] onSucceed:device];
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        sleep(1);
        dispatch_async(dispatch_get_main_queue(), ^{
            [alertView dismissWithClickedButtonIndex:alertView.cancelButtonIndex animated:YES];
            [self.navigationController.presentingViewController dismissViewControllerAnimated:YES completion:nil];
        });
    });
}

- (void)onConfigSSIDMotMatched {
    [[YKCenterCommon sharedInstance] cancelAlertViewDismiss];
    double delayInSeconds = 1.0;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [self.btnAutoJump2 sendActionsForControlEvents:UIControlEventTouchUpInside];
    });
}

- (void)onConfigFailed {
    [[YKCenterCommon sharedInstance] cancelAlertViewDismiss];
    double delayInSeconds = 1.0;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [self.btnAutoJump sendActionsForControlEvents:UIControlEventTouchUpInside];
    });
}

- (void)onWillEnterForeground {
//    [self onConfigFailed];
}

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    switch (buttonIndex) {
        case 1:
//            [[GosCommon sharedInstance] onCancel];
            break;
        default:
            break;
    }
}

- (IBAction)onCancel:(id)sender {
//    SHOW_ALERT_CANCEL_CONFIG(self);
    [[YKCenterCommon sharedInstance] showAlertCancelConfig:self];
}

@end
