//
//  YKRemoteViewController.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/19.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKRemoteViewController.h"
#import <YKCenterSDK/YKCenterSDK.h>
#import "YKCenterCommon.h"

@interface YKRemoteViewController ()
@property (nonatomic, assign) BOOL isLearning;
@end

@implementation YKRemoteViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = self.remote.name;
    self.isLearning = NO;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/**
 用于演示如何使用学习红外码接口

 @param sender sender 对象
 */
- (IBAction)learnCode:(id)sender {
    if (self.isLearning) {
        [YKCenterSDK stopLearnCode:[[YKCenterCommon sharedInstance] currentYKCId]];
        self.isLearning = NO;
    }
    else {
        __weak __typeof(self)weakSelf = self;
        [YKCenterSDK learnCodeWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                             completion:^(BOOL result, NSString * _Nullable code)
         {
             NSLog(@"result:%ld, code:%@", (long)result, code);
             
             if (result) {
                 __strong __typeof(weakSelf)strongSelf = weakSelf;
                 strongSelf.isLearning = NO;
                 // 使用举例：修改第一个key的码值
                 YKRemoteDeviceKey *key = strongSelf.remote.keys[0];
                 key.src = code;
                 key.zip = 2;
             }
         }];
    }
    
    self.isLearning = YES;
}


/**
 用于测试发送学习到的码

 @param sender sender 对象
 */
- (IBAction)sendLearnCode:(id)sender {
    YKRemoteDeviceKey *key = self.remote.keys[0];
    
    [YKCenterSDK sendRemoteWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                               datas:@[key]
                          completion:^(BOOL result, NSError * _Nonnull error) {
                              NSLog(@"result=%s, error=%@", result ? "true" : "false", error);
                          }];
}


- (IBAction)showActions:(id)sender {
    UIAlertController *ac = [UIAlertController alertControllerWithTitle:@"请选择"
                                                                message:nil
                                                         preferredStyle:(UIAlertControllerStyleActionSheet)];
    
    UIAlertAction *learn = [UIAlertAction actionWithTitle:@"学码"
                                                      style:(UIAlertActionStyleDefault)
                                                    handler:^(UIAlertAction * _Nonnull action)
                              {
                                  [self learnCode:nil];
                              }];
    
    UIAlertAction *test = [UIAlertAction actionWithTitle:@"测试"
                                                      style:(UIAlertActionStyleDefault)
                                                    handler:^(UIAlertAction * _Nonnull action)
                              {
                                   [self sendLearnCode:nil];
                              }];
    __weak __typeof(self)weakSelf = self;
    UIAlertAction *exportJson = [UIAlertAction actionWithTitle:@"导出json"
                                                    style:(UIAlertActionStyleDefault)
                                                  handler:^(UIAlertAction * _Nonnull action)
                            {
                                __weak __typeof(weakSelf)strongSelf = weakSelf;
                                NSDictionary *dict = [strongSelf.remote toJsonObject];
                                [strongSelf showAlert:dict.description];
                            }];
    
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"取消"
                                                     style:(UIAlertActionStyleCancel)
                                                   handler:nil];
    
    [ac addAction:learn];
    [ac addAction:test];
    [ac addAction:exportJson];
    [ac addAction:cancel];
    
    [self presentViewController:ac animated:YES completion:nil];
}

- (void)showAlert:(NSString *)message{
    UIAlertController *ac = [UIAlertController alertControllerWithTitle:@"Json"
                                                               message:message
                                                        preferredStyle:(UIAlertControllerStyleAlert)];
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"关闭"
                                                     style:(UIAlertActionStyleCancel)
                                                   handler:nil];
    [ac addAction:cancel];
    [self presentViewController:ac animated:YES completion:nil];
}

#pragma mark - Table view data source
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.remote.keys.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"YKRemoteCellIdentifier"
                                                            forIndexPath:indexPath];
    
    YKRemoteDeviceKey *key = self.remote.keys[indexPath.row];
    cell.textLabel.text = key.key;
    cell.detailTextLabel.text = key.name;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    YKRemoteDeviceKey *key = self.remote.keys[indexPath.row];
    NSLog(@"%@ = %@, zip=%d", key.name, key.src, key.zip);
    [YKCenterSDK sendRemoteWithYKCId:[[YKCenterCommon sharedInstance] currentYKCId]
                               datas:@[key]
                          completion:^(BOOL result, NSError * _Nonnull error)
     {
        NSLog(@"result=%s, error=%@", result ? "true" : "false", error);
    }];
}

@end
