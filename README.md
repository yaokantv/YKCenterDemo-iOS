# YKCenterDemo-iOS
遥控中心 SDK demo for iOS

<img src="/Screenshot/screenshot_1.PNG" width="320">

## 使用 Pod
安装最新版本 Pod：
```$ sudo gem install cocoapods```，官方安装文档：[CocoaPods Guides - Getting Started](https://guides.cocoapods.org/using/getting-started.html#getting-started)

集成遥控中心 SDK 的 Pod 命令：
```$ pod install --verbose```

## 手动集成

1. 集成依赖库 YKCenterSDK
   1. 打开 `YKCenterDemo.xcodeproj`, 选择 Target `YKCenterDemo` 打开 General 标签项
   2. 在 Embedded Binaries 中点击“+”号，点击 Add Other.. 打开项目根目录，选择在 YKCenterSDK 目录下的 `YKCenterSDK.framework`。

2. 集成依赖库 [GizWifiSDK](http://gizwits.oss.aliyuncs.com/sdk/GizWifiSDK-iOS-2.06.06.1.zip)
   解压后，按步骤 1 的方法将 `GizWifiSDK.framework` 添加到 Embedded Binaries.

3. 集成依赖库 [MBProgressHUD](https://github.com/matej/MBProgressHUD/archive/master.zip)
   1. 使用 Xcode 打开 `YKCenterDemo.xcodeproj`, 然后拖拽 `MBProgressHUD.xcodeproj` 进来 (使用 "Product Navigator view")。
   2. 选择 target `YKCenterDemo` 然后打开 General， 在 Embedded Binaries 点击加号 +，从列表中选择 `MBProgressHUD.framework`。
   3. 将 MBProgressHUD 添加到 `Target Dependencies` 中。
   4. 然后可以在项目中通过 #import `<MBProgressHUD/MBProgressHUD.h>` 来使用。

4. 配置完成：
![项目配置](/Screenshot/project_settings.png)
