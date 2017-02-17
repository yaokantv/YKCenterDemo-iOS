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

@end
