//
//  YKBrandTableViewController.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/17.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKBrandTableViewController.h"
#import <YKCenterSDK/YKCenterSDK.h>
#import "YKCenterCommon.h"
#import "YKMatchDeviceTableViewController.h"

@interface YKBrandTableViewController ()
@property (nonatomic, strong) NSArray<YKRemoteDeviceBrand *> *brandList;
@end

@implementation YKBrandTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    __weak __typeof(self)weakSelf = self;
    [YKCenterSDK fetchRemoteDeviceBrandWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                              remoteDeviceTypeId:self.deviceType.tid.integerValue
                                     completion:^(NSArray<YKRemoteDeviceBrand *> * _Nonnull brands,
                                                  NSError * _Nonnull error)
    {
         __strong __typeof(weakSelf)strongSelf = weakSelf;
         strongSelf.brandList = brands;
         [strongSelf.tableView reloadData];
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.brandList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"YKBrandCellIdentifier"
                                                            forIndexPath:indexPath];
    
    // Configure the cell...
    YKRemoteDeviceBrand *brand = self.brandList[indexPath.row];
    cell.textLabel.text = brand.name;
    return cell;
}

#pragma mark - Navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    
    if ([segue.destinationViewController isKindOfClass:[YKMatchDeviceTableViewController class]]) {
        YKMatchDeviceTableViewController *vc = segue.destinationViewController;
        
        UITableViewCell *cell = sender;
        NSIndexPath *indexPath = [self.tableView indexPathForCell:cell];
        YKRemoteDeviceBrand *brand = self.brandList[indexPath.row];
        
        vc.deviceType = self.deviceType;
        vc.deviceBrand = brand;
    }
}


@end
