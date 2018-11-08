//
//  YKCenterCommon.m
//  YKCenterDemo
//
//  Created by Don on 2017/1/16.
//  Copyright © 2017年 Shenzhen Yaokan Technology Co., Ltd. All rights reserved.
//

#import "YKCenterCommon.h"

#import <CommonCrypto/CommonCrypto.h>

static NSString *ssidCacheKey = @"ykSSIDKeyValuePairs";
static NSString *encryptKey = @"com.yaokantv.ykcentersdk.commondata";

static NSData *AES256EncryptWithKey(NSString *key, NSData *data) {
    // 'key' should be 32 bytes for AES256, will be null-padded otherwise
    char keyPtr[kCCKeySizeAES256+1]; // room for terminator (unused)
    bzero(keyPtr, sizeof(keyPtr)); // fill with zeroes (for padding)
    
    // fetch key data
    [key getCString:keyPtr maxLength:sizeof(keyPtr) encoding:NSUTF8StringEncoding];
    
    NSUInteger dataLength = [data length];
    
    //See the doc: For block ciphers, the output size will always be less than or
    //equal to the input size plus the size of one block.
    //That's why we need to add the size of one block here
    size_t bufferSize = dataLength + kCCBlockSizeAES128;
    void *buffer = malloc(bufferSize);
    
    size_t numBytesEncrypted = 0;
    CCCryptorStatus cryptStatus = CCCrypt(kCCEncrypt, kCCAlgorithmAES128, kCCOptionPKCS7Padding,
                                          keyPtr, kCCKeySizeAES256,
                                          NULL /* initialization vector (optional) */,
                                          [data bytes], dataLength, /* input */
                                          buffer, bufferSize, /* output */
                                          &numBytesEncrypted);
    if (cryptStatus == kCCSuccess) {
        //the returned NSData takes ownership of the buffer and will free it on deallocation
        return [NSData dataWithBytesNoCopy:buffer length:numBytesEncrypted];
    }
    
    free(buffer); //free the buffer;
    return nil;
}

static NSData *AES256DecryptWithKey(NSString *key, NSData *data) {
    // 'key' should be 32 bytes for AES256, will be null-padded otherwise
    char keyPtr[kCCKeySizeAES256+1]; // room for terminator (unused)
    bzero(keyPtr, sizeof(keyPtr)); // fill with zeroes (for padding)
    
    // fetch key data
    [key getCString:keyPtr maxLength:sizeof(keyPtr) encoding:NSUTF8StringEncoding];
    
    NSUInteger dataLength = [data length];
    
    //See the doc: For block ciphers, the output size will always be less than or
    //equal to the input size plus the size of one block.
    //That's why we need to add the size of one block here
    size_t bufferSize = dataLength + kCCBlockSizeAES128;
    void *buffer = malloc(bufferSize);
    
    size_t numBytesDecrypted = 0;
    CCCryptorStatus cryptStatus = CCCrypt(kCCDecrypt, kCCAlgorithmAES128, kCCOptionPKCS7Padding,
                                          keyPtr, kCCKeySizeAES256,
                                          NULL /* initialization vector (optional) */,
                                          [data bytes], dataLength, /* input */
                                          buffer, bufferSize, /* output */
                                          &numBytesDecrypted);
    
    if (cryptStatus == kCCSuccess) {
        //the returned NSData takes ownership of the buffer and will free it on deallocation
        return [NSData dataWithBytesNoCopy:buffer length:numBytesDecrypted];
    }
    
    free(buffer); //free the buffer;
    return nil;
}

static NSString *makeEncryptKey(Class class, NSString *ssid) {
    NSString *tmpEncryptKey = NSStringFromClass(class);
    tmpEncryptKey = [tmpEncryptKey stringByAppendingString:@"_"];
    tmpEncryptKey = [tmpEncryptKey stringByAppendingString:ssid];
    tmpEncryptKey = [tmpEncryptKey stringByAppendingString:@"_"];
    
    unsigned char result[16] = { 0 };
    CC_MD5(tmpEncryptKey.UTF8String, (CC_LONG)tmpEncryptKey.length, result);
    NSString *ret = @"";
    
    for (int i=0; i<16; i++) {
        ret = [ret stringByAppendingFormat:@"%02X", result[i]];
    }
    
    return ret;
}

id YKGetControllerWithClass(Class class, UITableView *tableView, NSString *reuseIndentifer) {
    if ([class isSubclassOfClass:[UITableViewCell class]]) {
        UINib *nib = [UINib nibWithNibName:NSStringFromClass(class) bundle:nil];
        if(nib) {
            [tableView registerNib:nib forCellReuseIdentifier:reuseIndentifer];
            return [tableView dequeueReusableCellWithIdentifier:reuseIndentifer];
        }
    }
    return nil;
}

static YKCenterCommon *instance = nil;

@implementation YKCenterCommon

+ (instancetype)sharedInstance {
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[YKCenterCommon alloc] __init];
    });
    
    return instance;
}

- (id)__init {
    self = [super init];
    if (self) {
    }
    
    return self;
}


- (NSMutableDictionary *)ssidKeyPairs {
    id obj = [[NSUserDefaults standardUserDefaults] valueForKey:ssidCacheKey];
    if (![obj isKindOfClass:[NSDictionary class]]) {
        return [NSMutableDictionary dictionary];
    }
    return [obj mutableCopy];
}

- (void)setSsidKeyPairs:(NSDictionary *)dict {
    if ([dict isKindOfClass:[NSDictionary class]]) {
        [[NSUserDefaults standardUserDefaults] setValue:dict forKey:ssidCacheKey];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

- (void)saveSSID:(NSString *)ssid key:(NSString *)key {
    if (nil == ssid)  return;
    if (nil == key) {
        key = @"";
    }
    
    NSMutableDictionary *dict = [self ssidKeyPairs];
    NSString *tmpEncryptKey = makeEncryptKey([self class], ssid);
    NSData *encrypted = AES256EncryptWithKey(tmpEncryptKey, [key dataUsingEncoding:NSUTF8StringEncoding]);
    [dict setValue:encrypted forKey:ssid];
    [self setSsidKeyPairs:dict];
}

- (NSString *)getPasswrodFromSSID:(NSString *)ssid {
    if (nil == ssid) return @"";
    
    NSMutableDictionary *dict = [self ssidKeyPairs];
    NSData *encrypted = dict[ssid];
    if ([encrypted isKindOfClass:[NSData class]]) {
        NSString *tmpEncryptKey = makeEncryptKey([self class], ssid);
        NSData *data = AES256DecryptWithKey(tmpEncryptKey, encrypted);
        if (data) {
            NSString *ret = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
            if ([ret isKindOfClass:[NSString class]]) {
                return ret;
            }
        }
    }
    return @"";
}

- (void)saveUserDefaults:(NSString *)username password:(NSString *)password uid:(NSString *)uid token:(NSString *)token {
    if (username) [[NSUserDefaults standardUserDefaults] setObject:username forKey:@"username"];
    if (password) [[NSUserDefaults standardUserDefaults] setObject:password forKey:@"password"];
    if (uid) self.uid = uid;
    if (token) self.token = token;
    [[NSUserDefaults standardUserDefaults] synchronize];
    //    self.isLogin = YES;
}

- (void)removeUserDefaults {
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:@"username"];
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:@"password"];
    self.uid = @"";
    self.token = @"";
    [[NSUserDefaults standardUserDefaults] synchronize];
}

+ (BOOL)isMobileNumber:(NSString *)mobileNum {
    if (mobileNum.length < 1) {
        return NO;
    }
    
    /**
     * 手机号码
     * 移动：134[0-8],135,136,137,138,139,150,151,157,158,159,182,187,188
     * 联通：130,131,132,152,155,156,185,186
     * 电信：133,1349,153,180,189
     */
    //    NSString * MOBILE = @"^1(3[0-9]|5[0-35-9]|8[025-9])\\\\d{8}$";
    NSString * MOBILE = @"^(13[0-9]|15[012356789]|17[0678]|18[0-9]|14[57])[0-9]{8}$";
    /**
     10         * 中国移动：China Mobile
     11         * 134[0-8],135,136,137,138,139,150,151,157,158,159,182,187,188
     12         */
    NSString * CM = @"^1(34[0-8]|(3[5-9]|5[017-9]|8[278])\\\\d)\\\\d{7}$";
    /**
     15         * 中国联通：China Unicom
     16         * 130,131,132,152,155,156,185,186
     17         */
    NSString * CU = @"^1(3[0-2]|5[256]|8[56])\\\\d{8}$";
    /**
     20         * 中国电信：China Telecom
     21         * 133,1349,153,180,189
     22         */
    NSString * CT = @"^1((33|53|8[09])[0-9]|349)\\\\d{7}$";
    /**
     25         * 大陆地区固话及小灵通
     26         * 区号：010,020,021,022,023,024,025,027,028,029
     27         * 号码：七位或八位
     28         */
//     NSString * PHS = @"^0(10|2[0-5789]|\\\\d{3})\\\\d{7,8}$";
    
        NSPredicate *regextestmobile = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", MOBILE];
        NSPredicate *regextestcm = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", CM];
        NSPredicate *regextestcu = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", CU];
        NSPredicate *regextestct = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", CT];
    
        if (([regextestmobile evaluateWithObject:mobileNum] == YES)
            || ([regextestcm evaluateWithObject:mobileNum] == YES)
            || ([regextestct evaluateWithObject:mobileNum] == YES)
            || ([regextestcu evaluateWithObject:mobileNum] == YES))
        {
            return YES;
        }
        else
        {
            return NO;
        }
}

- (void)showAlertCancelConfig:(id)delegate {
    self.cancelAlertView = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"tip", nil) message:NSLocalizedString(@"Discard your configuration?", nil) delegate:delegate cancelButtonTitle:NSLocalizedString(@"NO", nil) otherButtonTitles:NSLocalizedString(@"OK", nil), nil];
    [self.cancelAlertView show];
}

- (void)cancelAlertViewDismiss {
    [self.cancelAlertView dismissWithClickedButtonIndex:self.cancelAlertView.cancelButtonIndex animated:YES];
}


@end
