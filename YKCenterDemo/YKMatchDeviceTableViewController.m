//
//  YKMatchDeviceTableViewController.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/17.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKMatchDeviceTableViewController.h"
#import <YKCenterSDK/YKCenterSDK.h>
#import "YKCenterCommon.h"
#import "YKMatchKeyTableViewController.h"
#import "YKOneKeyMatchViewController.h"

@interface YKMatchDeviceTableViewController ()

@property (nonatomic, strong) NSArray<YKRemoteMatchDevice *> *matchList;

@end

@implementation YKMatchDeviceTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    __weak __typeof(self)weakSelf = self;
    [YKCenterSDK fetchMatchRemoteDeviceWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                              remoteDeviceTypeId:self.deviceType.tid.integerValue
                             remoteDeviceBrandId:self.deviceBrand.bid
                                      completion:^(NSArray<YKRemoteMatchDevice *> * _Nonnull mathes, NSError * _Nonnull error)
     {
         __strong __typeof(weakSelf)strongSelf = weakSelf;
         strongSelf.matchList = mathes;
         [strongSelf.tableView reloadData];
     }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.matchList.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"YKRemoteMatchCellIdentifier"
                                                            forIndexPath:indexPath];
    YKRemoteMatchDevice *match = self.matchList[indexPath.row];
    cell.textLabel.text = match.name;
    cell.detailTextLabel.text = match.rmodel;
    
    return cell;
}

#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.destinationViewController isKindOfClass:[YKMatchKeyTableViewController class]]) {
        YKMatchKeyTableViewController *vc = segue.destinationViewController;
        
        UITableViewCell *cell = sender;
        NSIndexPath *indexPath = [self.tableView indexPathForCell:cell];
        YKRemoteMatchDevice *device = self.matchList[indexPath.row];
        
        vc.matchDevice = device;
    }
    else if ([segue.destinationViewController isKindOfClass:[YKOneKeyMatchViewController class]]) {
        YKOneKeyMatchViewController *vc = segue.destinationViewController;
        vc.deviceBrand = self.deviceBrand;
        vc.deviceType = self.deviceType;
    }
}


@end
