# YKCenterDemo-iOS
遥控中心 SDK demo for iOS

<img src="/Screenshot/screenshot_1.PNG" width="320">

## 使用 Pod
1. 安装最新版本 Pod：
```$ sudo gem install cocoapods```，官方安装文档：[CocoaPods Guides - Getting Started](https://guides.cocoapods.org/using/getting-started.html#getting-started)

2. 集成遥控中心 SDK：

   1. 在 Podfile 添加 `pod 'YKCenterSDK'`，如果没有此文件则新建一个再添加。

   2. 然后执行 ```$ pod install --verbose```。

   3. 如果找不到 `YKCenterSDK` 请先更新 Pod 仓库：`pod repo update`

## 手动集成

1. 打开 `[your_project].xcodeproj`, 选择 Target `[your_target_name]` 打开 General 标签项。

2. 在 `Embedded Binaries` 中点击 `+` 号，点击 `Add Other..` 打开 `YKCenterSDK` 目录选择 `YKCenterSDK-[相应的平台].framework` 和 `GizWifiSDK.framework`。

   直接将这两个文件拖进 `Embedded Binaries` 一样可以。
