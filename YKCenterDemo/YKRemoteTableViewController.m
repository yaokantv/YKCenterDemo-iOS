//
//  YKRemoteTableViewController.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/18.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKRemoteTableViewController.h"
#import <YKCenterSDK/YKCenterSDK.h>
#import "YKRemoteViewController.h"
#import "YKRemoteACViewController.h"
#import "YKCenterCommon.h"

@interface YKRemoteTableViewController () <NSFetchedResultsControllerDelegate>

@property (nonatomic) NSArray<YKRemoteDevice *> *remotes;
@property (nonatomic, strong) NSFetchedResultsController *fetchedResultsController;

@end

@implementation YKRemoteTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self loadRemoteList];
}

- (NSFetchedResultsController *)fetchedResultsController {
    if (_fetchedResultsController == nil) {
        _fetchedResultsController = [YKRemoteDevice fetchedResultsController];
        _fetchedResultsController.delegate = self;
    }
    
    return _fetchedResultsController;
}

// 当数据库的数据有变化时更新Views
- (void)controllerDidChangeContent:(NSFetchedResultsController *)controller {
    NSArray *items = [controller fetchedObjects];
    //[self setupSubViewsWithItems:items];
    self.remotes = items;
    //    [self updateEditingVisible];
    dispatch_async(dispatch_get_main_queue(), ^ {
        [self.tableView reloadData];
    });
    
    NSLog(@"%s - items=%lu", __PRETTY_FUNCTION__, (unsigned long)items.count);
}

- (void)loadRemoteList {
    NSError *error;
    if (![[self fetchedResultsController] performFetch:&error]) {
        // Update to handle the error appropriately.
        NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
        //exit(-1);  // Fail
    }
    
    NSArray *items = [_fetchedResultsController fetchedObjects];
    self.remotes = items;
    
    //    [self updateEditingVisible];
    [self.tableView reloadData];
}

#pragma mark - Table view data source
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.remotes.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"YKRemotesCellIdentifier"
                                                            forIndexPath:indexPath];
    
    YKRemoteDevice *device = self.remotes[indexPath.row];
    NSString *displayName = device.showName;
    if (displayName.length == 0) {
        displayName = [device.name stringByAppendingFormat:@"-%@", device.modelName];
    }
    cell.textLabel.text = displayName;
    cell.detailTextLabel.text = device.modelName;
    
    return cell;
}


// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}


// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        YKRemoteDevice *device = self.remotes[indexPath.row];
        if ([device remove]) {
            NSLog(@"删除成功");
        } else {
            NSLog(@"删除失败");
        }
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
    // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }
}

-(void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath {
    YKRemoteDevice *device = self.remotes[indexPath.row];
    UIAlertController *ac = [UIAlertController alertControllerWithTitle:@"请输入名称"
                                                                message:@""
                                                         preferredStyle:(UIAlertControllerStyleAlert)];
    [ac addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
        NSString *displayName = device.showName;
        if (displayName.length == 0) {
            displayName = device.name;
        }
        
        textField.placeholder = displayName;
    }];
    
    UIAlertAction *cancelAction = [UIAlertAction
                                   actionWithTitle:NSLocalizedString(@"Cancel", @"Cancel action")
                                   style:UIAlertActionStyleCancel
                                   handler:^(UIAlertAction *action)
                                   {
                                       NSLog(@"Cancel action");
                                   }];
    UIAlertAction *okAction = [UIAlertAction
                               actionWithTitle:NSLocalizedString(@"OK", @"OK action")
                               style:UIAlertActionStyleDefault
                               handler:^(UIAlertAction *action)
                               {
                                   UITextField *showNameField = ac.textFields.firstObject;
                                   device.showName = showNameField.text;
                                   [device save];
                               }];
    [ac addAction:cancelAction];
    [ac addAction:okAction];
    [self presentViewController:ac animated:YES completion:nil];
}

#pragma mark - Navigation
// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if (segue.identifier) {
        UITableViewCell *cell = sender;
        
        NSIndexPath *indexPath = [self.tableView indexPathForCell:cell];
        YKRemoteDevice *remote = self.remotes[indexPath.row];
        
        
        if ([segue.destinationViewController isKindOfClass:[YKRemoteViewController class]]) {
            YKRemoteViewController *vc = segue.destinationViewController;
            
            vc.remote = remote;
        } else {
            YKRemoteACViewController *vc = segue.destinationViewController;
            vc.remote = remote;
        }
    }
}

- (BOOL)shouldPerformSegueWithIdentifier:(NSString *)identifier sender:(id)sender {
    
    if (identifier) {
        UITableViewCell *cell = sender;
        
        NSIndexPath *indexPath = [self.tableView indexPathForCell:cell];
        YKRemoteDevice *remote = self.remotes[indexPath.row];
        
        if (remote.typeId == kDeviceACType) {
            if ([identifier isEqualToString:@"normal"]) {
                [self performSegueWithIdentifier:@"ac" sender:sender];
                return NO;
            }
        }
    }
    
    return YES;
}

@end
