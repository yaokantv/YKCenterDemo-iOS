//
//  YKConfigTipsController.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/16.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKConfigTipsController.h"
#import "UIImageView+PlayGIF.h"

@interface YKConfigTipsController ()

@property (weak, nonatomic) IBOutlet UIButton *btnNext;
@property (weak, nonatomic) IBOutlet UIImageView *imgAirlink;

@end

@implementation YKConfigTipsController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.

    self.imgAirlink.gifPath = [[NSBundle mainBundle] pathForResource:@"02-airlink" ofType:@"gif"];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.imgAirlink startGIF];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    [self.imgAirlink stopGIF];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)onRadioButtonTouched:(UIButton *)sender {
    if (sender.isSelected) {
        if (self.btnNext.enabled) {
            sender.selected = NO;
            self.btnNext.enabled = NO;
            self.btnNext.backgroundColor = [UIColor lightGrayColor];
        } else {
            self.btnNext.enabled = YES;
            self.btnNext.backgroundColor = [UIColor blueColor];
        }
    }
}

- (IBAction)next:(id)sender {
    [self performSegueWithIdentifier:@"showConfigSearch" sender:nil];
}

@end
