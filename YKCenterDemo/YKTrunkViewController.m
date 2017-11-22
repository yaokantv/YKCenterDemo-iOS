//
//  YKTrunkViewController.m
//  YKCenterDemo
//
//  Created by dong on 2017/11/17.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKTrunkViewController.h"
#import <YKCenterSDK/YKCenterSDK.h>
#import "YKCenterCommon.h"

@interface YKTrunkViewController ()

@property (weak, nonatomic) IBOutlet UITextField *inputField;
@property (weak, nonatomic) IBOutlet UITextView *receiveTextView;
@property (weak, nonatomic) IBOutlet UISwitch *hexSwitch;

@property (strong, nonatomic) NSData *trunkData;

@end

@implementation YKTrunkViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    __weak __typeof(self)weakSelf = self;
    [YKCenterSDK registerReceiveTrunkDataHandler:^(NSData * _Nonnull trunkData) {
        [weakSelf updateTextViewWithData:trunkData];
    }];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    // unregister
    [YKCenterSDK registerReceiveTrunkDataHandler:nil];
}

- (IBAction)sendTrunk:(id)sender {
    [YKCenterSDK sendTrunkWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                               data:[self.inputField.text dataUsingEncoding:NSUTF8StringEncoding]
                         completion:^(id  _Nonnull result, NSError * _Nonnull error)
     {
         NSLog(@"result:%@, error:%@", result, error);
     }];
}

- (void)updateTextViewWithData:(NSData *)data {
    self.trunkData = data;
    self.receiveTextView.text = self.hexSwitch.isOn ? data.description : [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
}

- (IBAction)switchHex:(UISwitch *)sender {
    [self updateTextViewWithData:self.trunkData];
}


- (NSString *)hexStringWithData:(NSData *)data {
    NSUInteger capacity = data.length * 2;
    NSMutableString *sbuf = [NSMutableString stringWithCapacity:capacity];
    const unsigned char *buf = data.bytes;
    NSInteger i;
    for (i=0; i<data.length; ++i) {
        [sbuf appendFormat:@"%02X", (NSUInteger)buf[i]];
    }
    
    return sbuf.copy;
}

@end
