//
//  YKLearnTableViewController.m
//  YKCenterDemo
//
//  Created by dong on 2017/11/28.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKLearnTableViewController.h"
#import <YKCenterSDK/YKCenterSDK.h>
#import "YKCenterCommon.h"

@interface YKLearnTableViewController ()

@property (nonatomic, strong) NSMutableArray <YKRemoteMatchDeviceKey *> *learnedCodes;
@property (nonatomic, assign) BOOL isLearning;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *learnBarButtonItem;

@end

@implementation YKLearnTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.learnedCodes = [NSMutableArray array];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)startLearn:(id)sender {
    if (self.isLearning) {
        [YKCenterSDK stopLearnCode:[[YKCenterCommon sharedInstance] currentYKCId]];
        self.isLearning = NO;
        self.learnBarButtonItem.title = @"开始学习";
    }
    else {
        if (self.learnType == YKLearnTypeIR) {
            [self learnIR];
        }
        else if (self.learnType == YKLearnTypeRF) {
            [self learnRF];
        }
        
        self.isLearning = YES;
        self.learnBarButtonItem.title = @"退出学习";
    }
}

- (void)learnIR {
    __weak __typeof(self)weakSelf = self;
    [YKCenterSDK learnCodeWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                         completion:^(BOOL result, NSString * _Nullable code)
     {
         NSLog(@"result:%ld, code:%@", (long)result, code);
         
         if (result) {
             __strong __typeof(weakSelf)strongSelf = weakSelf;
             strongSelf.isLearning = NO;
             strongSelf.learnBarButtonItem.title = @"开始学习";
             
             YKRemoteMatchDeviceKey *key = [[YKRemoteMatchDeviceKey alloc] init];
             key.src = code;
             key.zip = 2;
             [strongSelf.learnedCodes addObject:key];
             [strongSelf.tableView reloadData];
         }
     }];
}

- (void)learnRF {
    __weak __typeof(self)weakSelf = self;
    [YKCenterSDK learnRFCodeWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                           completion:^(BOOL result, NSString * _Nullable code)
     {
         NSLog(@"result:%ld, code:%@", (long)result, code);
         
         if (result) {
             __strong __typeof(weakSelf)strongSelf = weakSelf;
             strongSelf.isLearning = NO;
             strongSelf.learnBarButtonItem.title = @"开始学习";
             
             YKRemoteMatchDeviceKey *key = [[YKRemoteMatchDeviceKey alloc] init];
             key.src = code;
             key.zip = 2;
             [strongSelf.learnedCodes addObject:key];
             [strongSelf.tableView reloadData];
         }
     }];
}

- (void)sendIRKey:(YKRemoteMatchDeviceKey *)key {
    [YKCenterSDK sendRemoteWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                               datas:@[key]
                          completion:^(BOOL result, NSError * _Nonnull error) {
                              NSLog(@"result=%s, error=%@", result ? "true" : "false", error);
                          }];
}

- (void)sendRFKey:(YKRemoteMatchDeviceKey *)key {
    [YKCenterSDK sendRFCodeWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                                code:key.src
                          completion:^(BOOL result, NSError * _Nonnull error) {
                              NSLog(@"result=%s, error=%@", result ? "true" : "false", error);
                          }];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.learnedCodes.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"CodeCell" forIndexPath:indexPath];
    
    YKRemoteMatchDeviceKey *key = self.learnedCodes[indexPath.row];
    cell.textLabel.text = key.src;
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    YKRemoteMatchDeviceKey *key = self.learnedCodes[indexPath.row];
    
    if (self.learnType == YKLearnTypeIR) {
        [self sendIRKey:key];
    }
    else if (self.learnType == YKLearnTypeRF) {
        [self sendRFKey:key];
    }
}

@end
