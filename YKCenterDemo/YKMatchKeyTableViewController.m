//
//  YKMatchKeyTableViewController.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/17.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKMatchKeyTableViewController.h"
#import <YKCenterSDK/YKCenterSDK.h>
#import "YKCenterCommon.h"

@interface YKMatchKeyTableViewController ()

@end

@implementation YKMatchKeyTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.matchDevice.matchKeys.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"YKRemoteMatchKeyIdentifier"
                                                            forIndexPath:indexPath];
    
    YKRemoteMatchDeviceKey *key = self.matchDevice.matchKeys[indexPath.row];
    cell.textLabel.text = key.kn;
    cell.detailTextLabel.text = key.shortCMD;
    
    return cell;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    YKRemoteMatchDeviceKey *key = self.matchDevice.matchKeys[indexPath.row];
    
    [YKCenterSDK sendRemoteWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                               datas:@[key]
                          completion:^(id  _Nonnull result, NSError * _Nonnull error) {
                              
                          }];
}

- (IBAction)save:(id)sender {
    __weak __typeof(self)weakSelf = self;
    [YKCenterSDK fetchRemoteDeivceWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                             remoteDeviceId:self.matchDevice.rid
                                 completion:^(YKRemoteDevice * _Nonnull remote, NSError * _Nonnull error)
     {
         if (error == nil) {
             [weakSelf.navigationController dismissViewControllerAnimated:YES completion:nil];
         }
     }];
}

@end
