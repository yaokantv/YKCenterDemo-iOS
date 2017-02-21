//
//  YKViewController.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/12.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKViewController.h"
#import <YKCenterSDK/YKCenterSDK.h>
#import "MBProgressHUD.h"
#import "YKDeviceListCell.h"

#import "YKCenterCommon.h"

@interface YKViewController () <UIActionSheetDelegate>

@property (nonatomic, strong) NSArray *deviceListArray;

@end

@implementation YKViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [self getBoundDevice];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    [self getBoundDevice];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)refreshBtnPressed:(id)sender {
    [MBProgressHUD showHUDAddedTo:self.navigationController.view animated:YES];
    [self getBoundDevice];
}

- (IBAction)actionSheet:(id)sender {
    UIActionSheet *actionSheet = [[UIActionSheet alloc]
                                                initWithTitle:nil
                                                delegate:self
                                                cancelButtonTitle:NSLocalizedString(@"Cancel", nil)
                                                destructiveButtonTitle:nil
                                                otherButtonTitles:NSLocalizedString(@"Add Device", nil), NSLocalizedString(@"Setting", nil), nil];
    actionSheet.actionSheetStyle = UIBarStyleBlackTranslucent;
    [actionSheet showInView:self.view];
}


- (void)getBoundDevice {
    __weak __typeof(self)weakSelf = self;
    [YKCenterSDK fetchBoundYKC:^(NSArray<GizWifiDevice *> * _Nonnull devices, NSError *error) {
        __strong __typeof(weakSelf)strongSelf = weakSelf;
        [MBProgressHUD hideHUDForView:strongSelf.navigationController.view animated:YES];
        if (error) {
            NSLog(@"error:%@", error.localizedDescription);
            return;
        }

        strongSelf.deviceListArray = devices;
        [strongSelf.tableView reloadData];
    }];
}

#pragma mark - actionSheetDelegate
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    NSInteger offset = 0;
    //    if (![GizCommon sharedInstance].isLogin) {
    //        offset = -1;
    //    }
   if (buttonIndex == 0) {
        [self toAirLink:nil];
   } else if(buttonIndex == offset+1) {
        [self showAbout];
   }
}

- (IBAction)toAirLink:(id)sender {
    if (YKGetCurrentSSID().length > 0) {
        [self performSegueWithIdentifier:@"toAirLink" sender:nil];
    } else {
        SHOW_ALERT_CANCEL(NSLocalizedString(@"Please switch to Wifi environment", nil), nil);
    }
}

- (void)showAbout {
//    UINavigationController *nav = [[UIStoryboard storyboardWithName:@"GosSettings" bundle:nil] instantiateInitialViewController];
//    GosSettingsViewController *settingsVC = nav.viewControllers.firstObject;
//    [self.navigationController pushViewController:settingsVC animated:YES];
}

#pragma mark - table view
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
//    if ([[self.deviceListArray objectAtIndex:indexPath.section] count] == 0) {
//        return 60;
//    }
    return 80;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.deviceListArray.count;
}

//- (nullable NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
//    if (section == 0) return NSLocalizedString(@"Bound devices", nil);
//    else if (section == 1) return NSLocalizedString(@"Discovery of new devices", nil);
//    else return NSLocalizedString(@"Offline devices", nil);
//}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    YKDeviceListCell *cell = [tableView dequeueReusableCellWithIdentifier:@"CellIdentifier"];
    if (cell == nil) {
        //        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"CellIdentifier"];
        cell = [[[NSBundle mainBundle] loadNibNamed:@"YKDeviceListCell" owner:self options:nil] lastObject];
        //        UILabel *lanLabel = [[UILabel alloc] initWithFrame:CGRectMake([[UIScreen mainScreen] bounds].size.width - 110, 0, 74, 80)];
        //        lanLabel.textAlignment = NSTextAlignmentRight;
        //        lanLabel.tag = 99;
        //        [cell addSubview:lanLabel];
    }
    
    NSArray *devArr = self.deviceListArray;
    
    cell.accessoryType = UITableViewCellAccessoryNone;
    if ([devArr count] > 0) {
        GizWifiDevice *dev = [devArr objectAtIndex:indexPath.row];
        NSString *devName = dev.alias;
        if (devName == nil || devName.length == 0) {
            devName = dev.productName;
        }
        cell.title.text = devName;
        [self customCell:cell device:dev];
        cell.imageView.hidden = NO;
        cell.textLabel.text = @"";
    }
    else {
        cell.textLabel.text = NSLocalizedString(@"No device", nil);
        cell.mac.text = @"";
        cell.lan.text = @"";
        [cell.imageView setImage:nil];
    }
    return cell;
}

- (void)customCell:(YKDeviceListCell *)cell device:(GizWifiDevice *)dev {
    // 添加左边的图片
    UIGraphicsBeginImageContext(CGSizeMake(60, 60));
    UIImage *blankImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    UIImageView *subImageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"08-icon-Device"]];
    CGRect frame = subImageView.frame;
    
    //将图片居中
    frame.origin = CGPointMake(4, 9);
    subImageView.frame = frame;
    
    [cell.imageView addSubview:subImageView];
    cell.imageView.image = blankImage;
    cell.imageView.layer.cornerRadius = 10;
    
    cell.mac.text = dev.macAddress;
    
    if (dev.netStatus == GizDeviceOnline || dev.netStatus == GizDeviceControlled) {
        cell.imageView.backgroundColor = [UIColor brownColor];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.lan.text = dev.isLAN?NSLocalizedString(@"Lan", nil):NSLocalizedString(@"Remote", nil);
        if (!dev.isBind) {
            cell.lan.text = NSLocalizedString(@"unbound", nil);
        }
    }
    else {
        cell.imageView.backgroundColor = [UIColor lightGrayColor];
        cell.lan.text = @"";
    }
}

-(void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath
{

}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    GizWifiDevice *dev = self.deviceListArray[indexPath.row];
    [[YKCenterCommon sharedInstance] setCurrentYKCId:dev.macAddress];
    [self performSegueWithIdentifier:@"YKRemoteList" sender:nil];
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.section == 1) {
        return NO;
    }
    return YES;
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(nonnull NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
    }
}

- (NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath{
    return NSLocalizedString(@"Unbinding", nil);
}


@end
