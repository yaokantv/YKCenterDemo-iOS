# YKCenterDemo-iOS
遥控中心 SDK demo for iOS

![运行效果](/Screenshot/screenshot_1.PNG)

## 使用 Pod
安装最新版本 Pod：
```$ sudo gem install cocoapods```，官方安装文档：[CocoaPods Guides - Getting Started](https://guides.cocoapods.org/using/getting-started.html#getting-started)

集成遥控中心 SDK 的 Pod 命令：
```$ pod install --verbose```

## 手动集成

1. 集成依赖库 [YKCenterSDK]
   1. 打开 `YKCenterDemo.xcodeproj`, 然后拖拽 `YKCenterSDK` 目录下的 `YKCenterSDK.framework` 进来 (使用 "Product Navigator view")。
   2. Choose options for adding these files 窗口中，Add to targets 选中 `YKCenterDemo`，点击 Finish。

2. 集成依赖库 [GizWifiSDK](http://gizwits.oss.aliyuncs.com/sdk/GizWifiSDK-iOS-2.06.06.1.zip)
   1. 解压后，将 `GizWifiSDK.framework` 拖拽进打开的 `YKCenterDemo.xcodeproj` 中 (使用 "Product Navigator view")。
   2. Choose options for adding these files 窗口中，Add to targets 选中 `YKCenterDemo`，点击 Finish。

3. 集成依赖库 [MBProgressHUD](https://github.com/matej/MBProgressHUD/archive/master.zip)
   1. 使用 Xcode 打开 `YKCenterDemo.xcodeproj`, 然后拖拽 `MBProgressHUD.xcodeproj` 进来 (使用 "Product Navigator view")。
   2. 选择 target `YKCenterDemo` 然后打开 Build phases. 在 Link Binary With Libraries 点击加号 +，从列表中选择 `MBProgressHUD.framework`。
   3. 将 MBProgressHUD 添加到 `Target Dependencies` 中。
   4. 然后可以在项目中通过 #import `<MBProgressHUD/MBProgressHUD.h>` 来使用。

4. 配置完成：
![项目配置](/screenshot/project_settings.png)
