//
//  GizWifiDefinitions.h
//  GizWifiSDK
//
//  Created by GeHaitong on 15/7/9.
//  Copyright (c) 2015年 gizwits. All rights reserved.
//

#ifndef GizWifiSDK_GizWifiDefinitions_h
#define GizWifiSDK_GizWifiDefinitions_h

/*
 升级SDK兼容定义
 @note 仅为A1的APP无缝过渡升级使用。全新开发APP的过程中，请不要使用XPG开头的定义，以免以后升级SDK时遇到麻烦
 */
#define XPGWifiSDK GizWifiSDK
#define XPGWifiSDKDelegate GizWifiSDKDelegate
#define XPGWifiDevice GizWifiDevice
#define XPGWifiDeviceDelegate GizWifiDeviceDelegate
#define XPGWifiCentralControlDevice GizWifiCentralControlDevice
#define XPGWifiCentralControlDeviceDelegate GizWifiCentralControlDeviceDelegate
#define XPGWifiSubDevice GizWifiSubDevice
#define XPGWifiGroup GizWifiGroup
#define XPGWifiGroupDelegate GizWifiGroupDelegate
#define XPGWifiBinary GizWifiBinary
#define XPGUserInfo GizUserInfo
#define XPGWifiSSID GizWifiSSID

/*
 * @brief 这里会定义 APP 能够用到的错误码枚举定义
 */
typedef NS_ENUM(NSInteger, GizWifiErrorCode) {
    /*
     Client发出的请求执行成功
     */
    GIZ_SDK_SUCCESS = 0,
    
    /*
     body json invalid
     */
    GIZ_PUSHAPI_BODY_JSON_INVALID = 5001,
    /*
     Data Not Exist
     */
    GIZ_PUSHAPI_DATA_NOT_EXIST = 5300,
    /*
     No Client config
     */
    GIZ_PUSHAPI_NO_CLIENT_CONFIG = 5501,
    /*
     No Server Data
     */
    GIZ_PUSHAPI_NO_SERVER_DATA = 5502,
    /*
     Gizwits_appid Already Exist
     */
    GIZ_PUSHAPI_GIZWITS_APPID_EXIST = 5601,
    /*
     Param Error
     */
    GIZ_PUSHAPI_PARAM_ERROR = 5700,
    /*
     Auth_Key Invalid
     */
    GIZ_PUSHAPI_AUTH_KEY_INVALID = 5701,
    /*
     Appid or User-Token Error
     */
    GIZ_PUSHAPI_APPID_OR_TOKEN_ERROR = 5702,
    /*
     Type Param Error
     */
    GIZ_PUSHAPI_TYPE_PARAM_ERROR = 5703,
    /*
     Id Param Error
     */
    GIZ_PUSHAPI_ID_PARAM_ERROR = 5704,
    /*
     ApiKey or SecretKey Param Invalid
     */
    GIZ_PUSHAPI_APPKEY_SECRETKEY_INVALID = 5705,
    /*
     ChannelId Param Error
     */
    GIZ_PUSHAPI_CHANNELID_ERROR_INVALID = 5706,
    /*
     Push Error
     */
    GIZ_PUSHAPI_PUSH_ERROR = 5900,
    
    /*
     Client发给Daemon的json格式错误
     */
    GIZ_SDK_PARAM_FORM_INVALID = 8001,
    /*
     Client与Daemon之间如果没有通过握手认证，任何数据交互都无效
     */
    GIZ_SDK_CLIENT_NOT_AUTHEN = 8002,
    /*
     Client版本号无效
     */
    GIZ_SDK_CLIENT_VERSION_INVALID = 8003,
    /*
     udp端口绑定失败
     */
    GIZ_SDK_UDP_PORT_BIND_FAILED = 8004,
    /*
     Daemon系统错误
     */
    GIZ_SDK_DAEMON_EXCEPTION = 8005,
    /*
     Client发出的数据请求，Json格式正确，但参数无效；APP传入参数无效
     */
    GIZ_SDK_PARAM_INVALID = 8006,
    /*
     appid长度错误
     */
    GIZ_SDK_APPID_LENGTH_ERROR = 8007,
    /*
     日志路径无效
     */
    GIZ_SDK_LOG_PATH_INVALID = 8008,
    /*
     日志级别无效
     */
    GIZ_SDK_LOG_LEVEL_INVALID = 8009,
    
    /*
     设备配置信息发送失败
     */
    GIZ_SDK_DEVICE_CONFIG_SEND_FAILED = 8021,
    /*
     设备正在配置
     */
    GIZ_SDK_DEVICE_CONFIG_IS_RUNNING = 8022,
    /*
     设备配置超时
     */
    GIZ_SDK_DEVICE_CONFIG_TIMEOUT = 8023,
    /*
     设备did无效
     */
    GIZ_SDK_DEVICE_DID_INVALID = 8024,
    /*
     设备mac无效
     */
    GIZ_SDK_DEVICE_MAC_INVALID = 8025,
    /*
     子设备did无效
     */
    GIZ_SDK_SUBDEVICE_DID_INVALID = 8026,
    /*
     设备passcode无效
     */
    GIZ_SDK_DEVICE_PASSCODE_INVALID = 8027,
    /*
     不是中控设备
     */
    GIZ_SDK_DEVICE_NOT_CENTERCONTROL = 8028,
    /*
     设备未订阅
     */
    GIZ_SDK_DEVICE_NOT_SUBSCRIBED = 8029,
    /*
     设备未响应
     */
    GIZ_SDK_DEVICE_NO_RESPONSE = 8030,
    /*
     设备未就绪
     */
    GIZ_SDK_DEVICE_NOT_READY = 8031,
    /*
     设备未绑定
     */
    GIZ_SDK_DEVICE_NOT_BINDED = 8032,
    /*
     设备控制指令中包含无效指令
     */
    GIZ_SDK_DEVICE_CONTROL_WITH_INVALID_COMMAND = 8033,
    /*
     设备控制指令执行失败
     */
    GIZ_SDK_DEVICE_CONTROL_FAILED = 8034,
    /*
     设备状态查询失败
     */
    GIZ_SDK_DEVICE_GET_STATUS_FAILED = 8035,
    /*
     设备控制指令参数类型错误
     */
    GIZ_SDK_DEVICE_CONTROL_VALUE_TYPE_ERROR = 8036,
    /*
     设备控制指令参数值不在有效范围内
     */
    GIZ_SDK_DEVICE_CONTROL_VALUE_OUT_OF_RANGE = 8037,
    /*
     设备控制指令中包含不可写指令
     */
    GIZ_SDK_DEVICE_CONTROL_NOT_WRITABLE_COMMAND = 8038,
    /*
     设备绑定失败
     */
    GIZ_SDK_BIND_DEVICE_FAILED = 8039,
    /*
     设备解绑失败
     */
    GIZ_SDK_UNBIND_DEVICE_FAILED = 8040,
    
    /*
     域名解析失败
     */
    GIZ_SDK_DNS_FAILED = 8041,
    /*
     m2m连接成功
     */
    GIZ_SDK_M2M_CONNECTION_SUCCESS = 8042,
    /*
     socket设置非阻塞失败
     */
    GIZ_SDK_SET_SOCKET_NON_BLOCK_FAILED = 8043,
    /*
     连接超时
     */
    GIZ_SDK_CONNECTION_TIMEOUT = 8044,
    /*
     连接被拒绝
     */
    GIZ_SDK_CONNECTION_REFUSED = 8045,
    /*
     连接错误
     */
    GIZ_SDK_CONNECTION_ERROR = 8046,
    /*
     连接被关闭
     */
    GIZ_SDK_CONNECTION_CLOSED = 8047,
    /*
     ssl握手失败
     */
    GIZ_SDK_SSL_HANDSHAKE_FAILED = 8048,
    /*
     设备登录验证失败
     */
    GIZ_SDK_DEVICE_LOGIN_VERIFY_FAILED = 8049,
    /*
     当前外网不可达
     */
    GIZ_SDK_INTERNET_NOT_REACHABLE = 8050,
    
    /*
     http应答格式错误
     */
    GIZ_SDK_HTTP_ANSWER_FORMAT_ERROR = 8096,
    /*
     http应答参数错误
     */
    GIZ_SDK_HTTP_ANSWER_PARAM_ERROR = 8097,
    /*
     http服务无响应
     */
    GIZ_SDK_HTTP_SERVER_NO_ANSWER = 8098,
    /*
     http请求失败
     */
    GIZ_SDK_HTTP_REQUEST_FAILED = 8099,
    
    /*
     其他错误
     */
    GIZ_SDK_OTHERWISE = 8100,
    /*
     Daemon内存分配失败
     */
    GIZ_SDK_MEMORY_MALLOC_FAILED = 8101,
    /*
     Daemon内部线程创建失败
     */
    GIZ_SDK_THREAD_CREATE_FAILED = 8102,
    
    /*
     用户ID无效
     */
    GIZ_SDK_USER_ID_INVALID = 8150,
    /*
     用户token无效
     */
    GIZ_SDK_TOKEN_INVALID = 8151,
    /*
     组ID无效
     */
    GIZ_SDK_GROUP_ID_INVALID = 8152,
    /*
     组名称无效
     */
    GIZ_SDK_GROUPNAME_INVALID = 8153,
    /*
     组类型无效
     */
    GIZ_SDK_GROUP_PRODUCTKEY_INVALID = 8154,
    /*
     组设备删除失败
     */
    GIZ_SDK_GROUP_FAILED_DELETE_DEVICE = 8155,
    /*
     组设备添加失败
     */
    GIZ_SDK_GROUP_FAILED_ADD_DEVICE = 8156,
    /*
     组设备获取失败
     */
    GIZ_SDK_GROUP_GET_DEVICE_FAILED = 8157,
    
    /*
     配置文件还未下载
     */
    GIZ_SDK_DATAPOINT_NOT_DOWNLOAD = 8201,
    /*
     配置文件服务不可用
     */
    GIZ_SDK_DATAPOINT_SERVICE_UNAVAILABLE = 8202,
    /*
     配置文件解析失败
     */
    GIZ_SDK_DATAPOINT_PARSE_FAILED = 8203,
    
    /*
     SDK 未初始化
     */
    GIZ_SDK_NOT_INITIALIZED = 8300,
    /*
     daemon程序执行失败
     */
    GIZ_SDK_EXEC_DAEMON_FAILED = 8304,
    /*
     尝试运行daemon时发生异常
     */
    GIZ_SDK_EXEC_CATCH_EXCEPTION = 8305,
    /*
     APPID为空
     */
    GIZ_SDK_APPID_IS_EMPTY = 8306,
    /*
     不支持的API
     */
    GIZ_SDK_UNSUPPORTED_API = 8307,
    /*
     Client如果等不到Daemon的回复，就向APP返回操作超时
     */
    GIZ_SDK_REQUEST_TIMEOUT = 8308,
    /*
     Daemon版本号无效
     */
    GIZ_SDK_DAEMON_VERSION_INVALID = 8309,
    /*
     手机没有连接软AP热点
     */
    GIZ_SDK_PHONE_NOT_CONNECT_TO_SOFTAP_SSID = 8310,
    /*
     手机热点和要配置的路由ssid不匹配
     */
    GIZ_SDK_DEVICE_CONFIG_SSID_NOT_MATCHED = 8311,
    /*
     设备不在softap模式
     */
    GIZ_SDK_NOT_IN_SOFTAPMODE = 8312,
    /*
     设备配置时无可用wifi
     */
    GIZ_SDK_PHONE_WIFI_IS_UNAVAILABLE = 8313,
    /*
     设备上报透传数据的标识
     */
    GIZ_SDK_RAW_DATA_TRANSMIT = 8314,
    /*
     正在下载设备的产品定义
     */
    GIZ_SDK_PRODUCT_IS_DOWNLOADING = 8315,
    /*
     SDK启动成功
     */
    GIZ_SDK_START_SUCCESS = 8316,
    
    /*
     当前固件是最新版本，不需要升级
     */
    GIZ_SDK_DEVICE_FIRMWARE_IS_LATEST = 8350,
    /*
     固件下载成功
     */
    GIZ_SDK_DEVICE_FIRMWARE_DOWNLOAD_OK = 8351,
    /*
     固件下载失败
     */
    GIZ_SDK_DEVICE_FIRMWARE_DOWNLOAD_FAILED = 8352,
    /*
     设备忙，固件正在升级
     */
    GIZ_SDK_DEVICE_BUSY_IN_UPGRADE = 8353,
    /*
     固件推送失败
     */
    GIZ_SDK_DEVICE_FIRMWARE_PUSH_FAILED = 8354,
    /*
     固件版本过低
     */
    GIZ_SDK_DEVICE_FIRMWARE_VERSION_TOO_LOW = 8355,
    /*
     固件校验失败
     */
    GIZ_SDK_DEVICE_FIRMWARE_CHECK_FAILED = 8356,
    /*
     固件升级失败
     */
    GIZ_SDK_DEVICE_UPGRADE_FAILED = 8357,
    /*
     固件升级成功
     */
    GIZ_SDK_DEVICE_UPGRADE_SUCCESS = 8358,
    
    /*
     mac already registered!
     */
    GIZ_OPENAPI_MAC_ALREADY_REGISTERED = 9001,
    /*
     product_key invalid
     */
    GIZ_OPENAPI_PRODUCT_KEY_INVALID = 9002,
    /*
     appid invalid
     */
    GIZ_OPENAPI_APPID_INVALID = 9003,
    /*
     token invalid
     */
    GIZ_OPENAPI_TOKEN_INVALID = 9004,
    /*
     user not exist
     */
    GIZ_OPENAPI_USER_NOT_EXIST = 9005,
    /*
     token expired
     */
    GIZ_OPENAPI_TOKEN_EXPIRED = 9006,
    /*
     m2m_id invalid
     */
    GIZ_OPENAPI_M2M_ID_INVALID = 9007,
    /*
     server error
     */
    GIZ_OPENAPI_SERVER_ERROR = 9008,
    /*
     code expired
     */
    GIZ_OPENAPI_CODE_EXPIRED = 9009,
    /*
     code invalid
     */
    GIZ_OPENAPI_CODE_INVALID = 9010,
    /*
     sandbox scale quota exhausted!
     */
    GIZ_OPENAPI_SANDBOX_SCALE_QUOTA_EXHAUSTED = 9011,
    /*
     production scale quota exhausted!
     */
    GIZ_OPENAPI_PRODUCTION_SCALE_QUOTA_EXHAUSTED = 9012,
    /*
     product has no request scale!
     */
    GIZ_OPENAPI_PRODUCT_HAS_NO_REQUEST_SCALE = 9013,
    /*
     device not found!
     */
    GIZ_OPENAPI_DEVICE_NOT_FOUND = 9014,
    /*
     form invalid!
     */
    GIZ_OPENAPI_FORM_INVALID = 9015,
    /*
     did or passcode invalid!
     */
    GIZ_OPENAPI_DID_PASSCODE_INVALID = 9016,
    /*
     device not bound!
     */
    GIZ_OPENAPI_DEVICE_NOT_BOUND = 9017,
    /*
     phone unavailable!
     */
    GIZ_OPENAPI_PHONE_UNAVALIABLE = 9018,
    /*
     username unavailable!
     */
    GIZ_OPENAPI_USERNAME_UNAVALIABLE = 9019,
    /*
     username or password error!
     */
    GIZ_OPENAPI_USERNAME_PASSWORD_ERROR = 9020,
    /*
     send command failed!
     */
    GIZ_OPENAPI_SEND_COMMAND_FAILED = 9021,
    /*
     email unavailable!
     */
    GIZ_OPENAPI_EMAIL_UNAVALIABLE = 9022,
    /*
     device is disabled!
     */
    GIZ_OPENAPI_DEVICE_DISABLED = 9023,
    /*
     fail to notify m2m!
     */
    GIZ_OPENAPI_FAILED_NOTIFY_M2M = 9024,
    /*
     attr invalid!
     */
    GIZ_OPENAPI_ATTR_INVALID = 9025,
    /*
     user invalid!
     */
    GIZ_OPENAPI_USER_INVALID = 9026,
    /*
     firmware not found!
     */
    GIZ_OPENAPI_FIRMWARE_NOT_FOUND = 9027,
    /*
     JD product info not found!
     */
    GIZ_OPENAPI_JD_PRODUCT_NOT_FOUND = 9028,
    /*
     datapoint data not found!
     */
    GIZ_OPENAPI_DATAPOINT_DATA_NOT_FOUND = 9029,
    /*
     scheduler not found!
     */
    GIZ_OPENAPI_SCHEDULER_NOT_FOUND = 9030,
    /*
     qq oauth key invalid!
     */
    GIZ_OPENAPI_QQ_OAUTH_KEY_INVALID = 9031,
    /*
     ota upgrade service OK, but in idle or disable!
     */
    GIZ_OPENAPI_OTA_SERVICE_OK_BUT_IN_IDLE = 9032,
    /*
     bt firmware unverified, except verify device!
     */
    GIZ_OPENAPI_BT_FIRMWARE_UNVERIFIED = 9033,
    /*
     bt firmware is OK, but nothing to upgrade!
     */
    GIZ_OPENAPI_BT_FIRMWARE_NOTHING_TO_UPGRADE = 9034,
    /*
     Save kairosdb error!
     */
    GIZ_OPENAPI_SAVE_KAIROSDB_ERROR = 9035,
    /*
     event not defined!
     */
    GIZ_OPENAPI_EVENT_NOT_DEFINED = 9036,
    /*
     send sms failed!
     */
    GIZ_OPENAPI_SEND_SMS_FAILED = 9037,
    /*
     signature invalid!
     */
    GIZ_OPENAPI_APPLICATION_AUTH_INVALID = 9038,
    /*
     Not allowed to call deprecated API!
     */
    GIZ_OPENAPI_NOT_ALLOWED_CALL_API = 9039,
    /*
     bad qrcode content!
     */
    GIZ_OPENAPI_BAD_QRCODE_CONTENT = 9040,
    /*
     request was throttled
     */
    GIZ_OPENAPI_REQUEST_THROTTLED = 9041,
    /*
     device offline!
     */
    GIZ_OPENAPI_DEVICE_OFFLINE = 9042,
    /*
     X-Gizwits-Timestamp invalid!
     */
    GIZ_OPENAPI_TIMESTAMP_INVALID = 9043,
    /*
     X-Gizwits-Signature invalid!
     */
    GIZ_OPENAPI_SIGNATURE_INVALID = 9044,
    /*
     API deprecated!
     */
    GIZ_OPENAPI_DEPRECATED_API = 9045,
    /*
     reserved
     */
    GIZ_OPENAPI_RESERVED = 9999,
    
    /*
     产品标识码无效
     */
    GIZ_SITE_PRODUCTKEY_INVALID = 10003,
    /*
     数据点未定义
     */
    GIZ_SITE_DATAPOINTS_NOT_DEFINED = 10010,
    /*
     数据点异常
     */
    GIZ_SITE_DATAPOINTS_NOT_MALFORME = 10011
};

/*
 @deprecated 此枚举定义已废弃，不再提供支持。请使用替代定义：GizWifiErrorCode
 */
typedef NS_ENUM(NSInteger, XPGWifiErrorCode) {
    XPGWifiError_NONE = 0,
    XPGWifiError_GENERAL = -1,
    XPGWifiError_NOT_IMPLEMENTED = -2,
    XPGWifiError_PACKET_DATALEN = -4,
    XPGWifiError_CONNECTION_ID = -5,
    XPGWifiError_CONNECTION_CLOSED = -7,
    XPGWifiError_PACKET_CHECKSUM = -8,
    XPGWifiError_LOGIN_VERIFY_FAILED = -9,
    XPGWifiError_NOT_LOGINED = -10,
    XPGWifiError_NOT_CONNECTED = -11,
    XPGWifiError_MQTT_FAIL = -12,
    XPGWifiError_DISCOVERY_MISMATCH = -13,
    XPGWifiError_SET_SOCK_OPT = -14,
    XPGWifiError_THREAD_CREATE = -15,
    XPGWifiError_CONNECTION_POOL_FULLED = -17,
    XPGWifiError_NULL_CLIENT_ID = -18,
    XPGWifiError_CONNECTION_ERROR = -19,
    XPGWifiError_INVALID_PARAM = -20,
    XPGWifiError_CONNECT_TIMEOUT = -21,
    XPGWifiError_INVALID_VERSION = -22,
    XPGWifiError_INSUFFIENT_MEM = -23,
    XPGWifiError_THREAD_BUSY = -24,
    XPGWifiError_HTTP_FAIL = -25,
    XPGWifiError_GET_PASSCODE_FAIL = -26,
    XPGWifiError_DNS_FAILED = -27,
    XPGWifiError_UDP_PORT_BIND_FAILED = -30,
    XPGWifiError_CONFIGURE_SSID_NOT_MATCHED = -39,
    XPGWifiError_CONFIGURE_TIMEOUT = -40,
    XPGWifiError_CONFIGURE_SENDFAILED = -41,
    XPGWifiError_NOT_IN_SOFTAPMODE = -42,
    XPGWifiError_UNRECOGNIZED_DATA = -43,
    XPGWifiError_CONNECTION_NO_GATEWAY = -44,
    XPGWifiError_CONNECTION_REFUSED = -45,
    XPGWifiError_IS_RUNNING = -46,
    XPGWifiError_UNSUPPORTED_API = -47,
    XPGWifiError_RAW_DATA_TRANSMIT = -48,
    XPGWifiError_START_SDK_FAILED = -49,
} DEPRECATED_ATTRIBUTE;

/*
 GizLogPrintLevel枚举，描述SDK提供的日志级别
 */
typedef NS_ENUM(NSInteger, GizLogPrintLevel) {
    
    /*
     不输出任何日志
     */
    GizLogPrintNone = 0,
    
    /*
     输出错误日志
     */
    GizLogPrintI,
    
    /*
     输出调试日志
     */
    GizLogPrintII,
    
    /*
     输出数据日志
     */
    GizLogPrintAll
};

/*
 GizWifiConfigureMode枚举，描述SDK支持的设备配置方式
 */
typedef NS_ENUM(NSInteger, GizWifiConfigureMode) {
    /*
     SoftAP配置模式
     */
    GizWifiSoftAP = 0,
    /*
     AirLink配置模式
     */
    GizWifiAirLink = 1,
};

/*
 @deprecated 此枚举定义已废弃，不再提供支持。请使用替代定义：GizWifiConfigureMode
 */
typedef NS_ENUM(NSInteger, XPGConfigureMode) {
    XPGWifiSDKSoftAPMode = 1,
    XPGWifiSDKAirLinkMode = 2,
} DEPRECATED_ATTRIBUTE;

/*
 GizWifiGAgentType 模组类型
 */
typedef NS_ENUM(NSInteger, GizWifiGAgentType) {
    /*
     庆科3162模组
     */
    GizGAgentMXCHIP = 0,
    /*
     汉枫模组
     */
    GizGAgentHF = 1,
    /*
     瑞昱模组
     */
    GizGAgentRTK = 2,
    /*
     联盛德模组
     */
    GizGAgentWM = 3,
    /*
     乐鑫模组
     */
    GizGAgentESP = 4,
    /*
     高通模组
     */
    GizGAgentQCA = 5,
    /*
     TI 模组
     */
    GizGAgentTI = 6,
    /*
     宇音天下模组
     */
    GizGAgentFSK = 7,
    /*
     庆科V3
     */
    GizGAgentMXCHIP3 = 8,
    /*
     古北模组
     */
    GizGAgentBL = 9,
    /*
     AtmelEE
     */
    GizGAgentAtmelEE = 10,
    /*
     其他
     */
    GizGAgentOther = 11,
};

/*
 @deprecated 此枚举定义已废弃，不再提供支持。请使用替代定义：GizWifiGAgentType
 */
typedef NS_ENUM(NSInteger, XPGWifiGAgentType) {
    XPGWifiGAgentTypeMXCHIP = 0,
    XPGWifiGAgentTypeHF = 1,
    XPGWifiGAgentTypeRTK = 2,
    XPGWifiGAgentTypeWM = 3,
    XPGWifiGAgentTypeESP = 4,
    XPGWifiGAgentTypeQCA = 5,
    XPGWifiGAgentTypeTI = 6,
    XPGWifiGAgentTypeFSK = 7,
    XPGWifiGAgentTypeMXCHIP3 = 8,
    XPGWifiGAgentTypeBL = 9,
} DEPRECATED_ATTRIBUTE;

/*
 GizUserAccountType枚举，描述SDK支持的用户（非第三方）账号类型
 */
typedef NS_ENUM(NSInteger, GizUserAccountType) {
    /*
     普通用户
     */
    GizUserNormal = 0,
    /*
     手机用户
     */
    GizUserPhone = 1,
    /*
     电子邮箱用户
     */
    GizUserEmail = 2,
};

typedef NS_ENUM(NSInteger, XPGUserAccountType) {
    XPGUserAccountTypeNormal = 0,
    XPGUserAccountTypePhone = 1,
    XPGUserAccountTypeEmail = 2
} DEPRECATED_ATTRIBUTE;

/*
 GizThirdAccountType枚举，描述SDK支持的第三方账号类型
 */
typedef NS_ENUM(NSInteger, GizThirdAccountType) {
    
    /*
     百度账号
     */
    GizThirdBAIDU = 0,
    
    /*
     新浪账号
     */
    GizThirdSINA = 1,
    
    /*
     QQ 账号
     */
    GizThirdQQ = 2,
    
    /**
     微信帐号
     */
    GizThirdWeChat = 3,
};

/*
 @deprecated 此枚举定义已废弃，不再提供支持。请使用替代定义：GizThirdAccountType
 */
typedef NS_ENUM(NSInteger, XPGWifiThirdAccountType) {
    XPGWifiThirdAccountTypeBAIDU = 0,
    XPGWifiThirdAccountTypeSINA,
    XPGWifiThirdAccountTypeQQ,
} DEPRECATED_ATTRIBUTE;

/*
 GizEventType枚举，描述SDK支持的事件类型
 */
typedef NS_ENUM(NSInteger, GizEventType) {
    
    /*
     SDK系统事件
     */
    GizEventSDK = 0,
    
    /*
     设备异常事件
     */
    GizEventDevice = 1,
    
    /*
     M2M异常事件
     */
    GizEventM2MService = 2,
    
    GizEventOpenAPIService = 3,
    GizEventProductService = 4,
    
    /*
     Token失效事件
     */
    GizEventToken = 5
};

/*
 GizWifiDeviceType枚举，描述SDK支持的设备分类
 */
typedef NS_ENUM(NSInteger, GizWifiDeviceType) {
    
    /*
     普通设备
     */
    GizDeviceNormal = 0,
    
    /*
     中控设备
     */
    GizDeviceCenterControl = 1,
};

/*
 @deprecated 此枚举定义已废弃，不再提供支持。请使用替代定义：GizWifiDeviceType
 */
typedef NS_ENUM(NSInteger, XPGWifiDeviceType) {
    XPGWifiDeviceTypeNormal = 0,
    XPGWifiDeviceTypeCenterControl,
} DEPRECATED_ATTRIBUTE;

/*
 GizWifiDeviceNetStatus 枚举，描述 SDK 支持的设备网路状态
 */
typedef NS_ENUM(NSInteger, GizWifiDeviceNetStatus) {
    
    /*
     离线状态
     */
    GizDeviceOffline = 0,
    
    /*
     在线状态
     */
    GizDeviceOnline = 1,
    
    /*
     可控状态
     */
    GizDeviceControlled = 2,
    
    GizDeviceUnavailable = 3,
};

/*
 性别类型
 */
typedef NS_ENUM(NSInteger, GizUserGenderType) {
    
    /*
     男
     */
    GizUserGenderMale = 0,
    
    /*
     女
     */
    GizUserGenderFemale = 1,
    
    /*
     其他
     */
    GizUserGenderUnknown = 2,
};

typedef NS_ENUM(NSInteger, XPGUserGenderType) {
    Male = 0,
    Female = 1,
    Unknown = 2,
} DEPRECATED_ATTRIBUTE;

/*
 推送类型
 */
typedef NS_ENUM(NSInteger, GizPushType) {
    /*
     百度
     */
    GizPushBaiDu = 0,
    /*
     极光
     */
    GizPushJiGuang = 1
};

/*
 定时按周重复
 */
typedef NS_ENUM(NSInteger, GizScheduleWeekday) {
    /*
     星期日
     */
    GizScheduleSunday = 0,
    /*
     星期一
     */
    GizScheduleMonday = 1,
    /*
     星期二
     */
    GizScheduleTuesday = 2,
    /*
     星期三
     */
    GizScheduleWednesday = 3,
    /*
     星期四
     */
    GizScheduleThursday = 4,
    /*
     星期五
     */
    GizScheduleFriday = 5,
    /*
     星期六
     */
    GizScheduleSaturday = 6
};

/*
 定时任务重复策略
 */
typedef NS_ENUM(NSInteger, GizScheduleRepeatRule) {
    /*
     不管什么情况都重复
     */
    GizScheduleRepeatAll = 0,
    /*
     仅失败重复
     */
    GizScheduleRepeatFailed,
};

/*
 定时任务执行状态
 */
typedef NS_ENUM(NSInteger, GizScheduleStatus) {
    /*
     成功
     */
    GizScheduleSucceed = 0,
    /*
     失败
     */
    GizScheduleFailed,
    /**
     无状态
     */
    GizScheduleNotDone,
};

#endif
