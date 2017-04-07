//
//  YKDeviceTypeViewController.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/17.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKDeviceTypeViewController.h"
#import <YKCenterSDK/YKCenterSDK.h>
#import "YKCenterCommon.h"
#import "YKBrandTableViewController.h"

@interface YKDeviceTypeViewController ()

@property (nonatomic, strong) NSArray<YKRemoteDeviceType *> *typeList;

@end

@implementation YKDeviceTypeViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    __weak __typeof(self)weakSelf = self;
    [YKCenterSDK fetchRemoteDeviceTypeWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                                     completion:^(NSArray<YKRemoteDeviceType *> * _Nonnull types,
                                                  NSError * _Nonnull error)
     {
         __strong __typeof(weakSelf)strongSelf = weakSelf;
         strongSelf.typeList = types;
         [strongSelf.tableView reloadData];
     }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)cancel:(id)sender {
    [self.navigationController dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark - Table view data source

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.typeList.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"YKDeviceTypeIdentifier" forIndexPath:indexPath];
    
    // Configure the cell...
    YKRemoteDeviceType *deviceType = self.typeList[indexPath.row];
    cell.textLabel.text = deviceType.name;
    
    return cell;
}

#pragma mark - Navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.destinationViewController isKindOfClass:[YKBrandTableViewController class]]) {
        YKBrandTableViewController *vc = segue.destinationViewController;
        UITableViewCell *cell = sender;
        NSIndexPath *indexPath = [self.tableView indexPathForCell:cell];
        YKRemoteDeviceType *deviceType = self.typeList[indexPath.row];
        vc.deviceType = deviceType;
    }
}

@end
