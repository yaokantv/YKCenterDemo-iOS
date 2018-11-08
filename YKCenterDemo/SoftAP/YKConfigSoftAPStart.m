//
//  YKConfigSoftAPStart.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/16.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKConfigSoftAPStart.h"
#import "YKSoftAPDetection.h"
#import "YKCenterCommon.h"
#import "UIImageView+PlayGIF.h"

@interface YKConfigSoftAPStart () <YKSoftAPDetectionDelegate, UIAlertViewDelegate>

@property (strong) YKSoftAPDetection *softapDetection;
@property (weak, nonatomic) IBOutlet UIButton *btnAutoJump;
@property (weak, nonatomic) IBOutlet UIButton *btnHelp;
@property (weak, nonatomic) IBOutlet UIImageView *imgSoftapTips;

@property (weak, nonatomic) IBOutlet UIButton *connectToSoftApBtn;

@end

@implementation YKConfigSoftAPStart

- (void)viewDidLoad {
    [super viewDidLoad];
    
//    self.connectToSoftApBtn.backgroundColor = [YKCenterCommon sharedInstance].buttonColor;
//    [self.connectToSoftApBtn setTitleColor:[YKCenterCommon sharedInstance].buttonTextColor forState:UIControlStateNormal];
    
    // Do any additional setup after loading the view.
    // 为按钮添加下划线
    NSString *str = self.btnHelp.titleLabel.text;
    NSMutableAttributedString *mstr = [[NSMutableAttributedString alloc] initWithString:str];
    [mstr addAttribute:NSUnderlineStyleAttributeName value:@(NSUnderlineStyleSingle) range:NSMakeRange(0, str.length)];
    [self.btnHelp setAttributedTitle:mstr forState:UIControlStateNormal];

    self.imgSoftapTips.gifPath = [[NSBundle mainBundle] pathForResource:@"04-softap-tips" ofType:@"gif"];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.imgSoftapTips startGIF];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    [self.imgSoftapTips stopGIF];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (BOOL)didSoftAPModeDetected:(NSString *)ssid {
    NSLog(@"ssid:%s", ssid.UTF8String);
    
    if (nil == ssid) {
        return NO;
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        UILocalNotification *notification = [[UILocalNotification alloc] init];
        notification.fireDate = [NSDate date];
        notification.timeZone = [NSTimeZone defaultTimeZone];
        notification.alertBody = NSLocalizedString(@"Connect successfully, click to return App", nil);
        notification.soundName = UILocalNotificationDefaultSoundName;
        
        [[UIApplication sharedApplication] scheduleLocalNotification:notification];

    });
    
    return YES;
}

- (void)willEnterForeground {
    // 检测到 soft ap 模式，则跳转页面
    if ([YKGetCurrentSSID() hasPrefix:SSID_PREFIX]) {
        [self onPushToConfigurePage];
    }
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationWillEnterForegroundNotification object:nil];
}

- (void)didBecomeActive {
    self.softapDetection = nil;
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationDidBecomeActiveNotification object:nil];
}

- (IBAction)onOpenConfig:(id)sender {
    // 开启后台 SoftAP 状态检测
    
    self.softapDetection = [[YKSoftAPDetection alloc] initWithSoftAPSSID:SSID_PREFIX delegate:self];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(willEnterForeground) name:UIApplicationWillEnterForegroundNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didBecomeActive) name:UIApplicationDidBecomeActiveNotification object:nil];

    NSArray* urlStrings = @[@"prefs:root=WIFI", @"App-Prefs:root=WIFI"];
    for(NSString* urlString in urlStrings){
        NSURL* url = [NSURL URLWithString:urlString];
        if([[UIApplication sharedApplication] canOpenURL:url]){
            [[UIApplication sharedApplication] openURL:url];
            break;
        }
    }
//    NSURL *url = [NSURL URLWithString:@"prefs:root=WIFI"];
//    if ([[UIApplication sharedApplication] canOpenURL:url]) {
//        [[UIApplication sharedApplication] openURL:url];
//    } else {
//        [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"Manually click \"Settings\" icon on your desktop, then select \"Wi-Fi\"", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil] show];
//    }
}

- (void)onPushToConfigurePage {
    [self.btnAutoJump sendActionsForControlEvents:UIControlEventTouchUpInside];
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

@end
