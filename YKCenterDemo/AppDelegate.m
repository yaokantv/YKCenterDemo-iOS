//
//  AppDelegate.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/12.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "AppDelegate.h"

#import <YKCenterSDK/YKCenterSDK.h>
//#import <GizWifiSDK/GizWifiSDK.h>

#warning 请输入注册到的 APP_ID
static NSString *const YK_APP_ID = @"";

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // 方案1：使用遥控中心SDK进行初始化
    [YKCenterSDK registApp:YK_APP_ID];
    
    //  方案2：自己管理第三方平台的方式
//    [YKCenterSDK registYKApp:YK_APP_ID];
//    [GizWifiSDK setLogLevel:GizLogPrintNone];
//    [GizWifiSDK startWithAppID:@"xxx"
//                     appSecret:@"xxx"
//            specialProductKeys:@[@"xxx"]
//              cloudServiceInfo:nil
//           autoSetDeviceDomain:NO];
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
