//
//  YKOneKeyMatchViewController.m
//  YKCenterDemo
//
//  Created by Don on 2017/10/25.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKOneKeyMatchViewController.h"
#import <YKCenterSDK/YKCenterSDK.h>
#import "YKCenterCommon.h"
#import <MBProgressHUD/MBProgressHUD.h>
#import "YKMatchKeyTableViewController.h"

@interface YKOneKeyMatchViewController ()
@property (strong, nonatomic) NSArray *keys;
@property (strong, nonatomic) UIAlertController *ac;
@property (nonatomic, copy) NSString *matchKey;
@end

@implementation YKOneKeyMatchViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.matchKey = @"power";
    
    [self retryAction:nil];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    [YKCenterSDK stopLearnCode:[[YKCenterCommon sharedInstance] currentYKCId]];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.destinationViewController isKindOfClass:[YKMatchKeyTableViewController class]]) {
        YKMatchKeyTableViewController *vc = segue.destinationViewController;
        YKRemoteMatchDevice *device = sender;
        
        vc.matchDevice = device;
    }
}

- (void)showAlert:(NSString *)message isLoading:(BOOL)loading {
    if (self.ac == nil) {
        UIAlertController *ac = [UIAlertController alertControllerWithTitle:nil
                                                                    message:nil
                                                             preferredStyle:UIAlertControllerStyleAlert];
        self.ac = ac;
    }
    
    self.ac.message = message;
    
    if (self.ac.presentingViewController != self.navigationController) {
        UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"OK"
                                                         style:(UIAlertActionStyleCancel)
                                                       handler:^(UIAlertAction * _Nonnull action) {
                                                           self.ac = nil;
                                                       }];
        [self.ac addAction:cancel];
        [self presentViewController:self.ac animated:YES completion:nil];
    }
}

- (void)hideAlert {
    [self dismissViewControllerAnimated:YES completion:^{
        self.ac = nil;
    }];
}

- (IBAction)retryAction:(id)sender {
    NSString *ykcId = [[YKCenterCommon sharedInstance] currentYKCId];
    __weak __typeof(self)weakSelf = self;
    
    NSString *message = [NSString stringWithFormat:@"开始匹配，请发送%@", self.matchKey];
    [self showAlert:message isLoading:YES];
    [YKCenterSDK learnCodeWithYKCId:ykcId completion:^(BOOL result, NSString * _Nullable code) {
        NSLog(@"code = %@", code);
        
        if (code.length == 0) {
            return;
        }
        
        [self showAlert:@"正在匹配" isLoading:YES];
        [weakSelf requestOnekeyMatchWith:code];
    }];
}

- (void)requestOnekeyMatchWith:(NSString *)cmd {
    if (cmd.length == 0) {
        return;
    }
    
    [YKCenterSDK oneKeyMatchWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                         beRemoteType:self.deviceType.tid.integerValue
                              brandId:self.deviceBrand.bid
                                  cmd_key:self.matchKey
                            cmd_value:cmd
                           completion:^(id _Nonnull result, NSError * _Nonnull error)
     {
         NSLog(@"result = %@, error=%@", result, error);
         
         if (result[@"errorMsg"]) {
             NSString *errorMsg = result[@"errorMsg"];
             NSLog(@"errorMsg:%@", errorMsg);
             self.matchKey = @"power";
             NSString *message = [NSString stringWithFormat:@"匹配结果：%@\nerrorMsg=%@", result, errorMsg];
             [self showAlert:message isLoading:NO];
         } else if (result[@"next_cmp_key"]) {
             self.matchKey = result[@"next_cmp_key"];
             NSString *message = [NSString stringWithFormat:@"请点击右上角按钮，开始匹配下一个键：%@",
                                  self.matchKey];
             [self showAlert:message isLoading:NO];
//             [self retryAction:nil];
             [self hideAlert];
         } else if (result[@"rc_command"]) {
             [self hideAlert];
             [self showTestView:[self parseResult:result]];
             return;
         } else {
             [self showAlert:error.localizedDescription isLoading:NO];
         }
         
     }];
}

- (YKRemoteMatchDevice *)parseResult:(NSDictionary *)deviceDict {
    
    YKRemoteMatchDevice *device = [[YKRemoteMatchDevice alloc] init];
    device.name = deviceDict[@"rc_name"];
//    device.model = deviceDict[@"be_rmodel"];
//    device.rid = deviceDict[@"rid"];
    device.rmodel = deviceDict[@"rc_model"];
//    device.typeId = typeId;
    
    NSMutableArray *keys = [NSMutableArray array];
    NSDictionary *keysDict = deviceDict[@"rc_command"];
    for (NSString *key in keysDict.allKeys) {
        YKRemoteMatchDeviceKey *deviceKey = [YKRemoteMatchDeviceKey new];
//        deviceKey.shortCMD = keyDict[@"short"];
        deviceKey.src = keysDict[key];
//        deviceKey.tip = keyDict[@"tip"];
        deviceKey.kn = key;
        deviceKey.key = key;
        deviceKey.zip = [deviceDict[@"zip"] integerValue];
//        deviceKey.order = [deviceDict[@"order"] integerValue];
        [keys addObject:deviceKey];
    }
    
    device.matchKeys = keys;
    
    return device;
}

- (void)showTestView:(YKRemoteMatchDevice *)device {
    [self performSegueWithIdentifier:@"showTestSegue" sender:device];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"OneKeyMatchCellIdentifier"
                                                            forIndexPath:indexPath];
    
    // Configure the cell...
    
    return cell;
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
