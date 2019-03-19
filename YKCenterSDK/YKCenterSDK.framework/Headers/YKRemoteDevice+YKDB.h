//
//  YKRemoteDevice+YKDB.h
//  Pods
//
//  Created by Don on 16/4/28.
//
//
#import "YKRemoteDevice+CoreDataClass.h"

NS_ASSUME_NONNULL_BEGIN

@interface YKRemoteDevice (YKDB)

+ (NSFetchedResultsController *)fetchedResultsController;

- (BOOL)save;
- (BOOL)remove;
- (BOOL)removeMemoryModel;

+ (YKRemoteDevice *)modelsWithLocalDeviceId:(NSString *)localDeviceId;
+ (NSArray <YKRemoteDevice *> *)modelsWithDeviceId:(NSString *)enterId;

+ (nullable YKRemoteDevice *)saveRemoteDeviceWithDictionary:(NSDictionary *)dict;
+ (nullable YKRemoteDevice *)remoteDeviceWithDictionary:(NSDictionary *)dict isMemoryModel:(BOOL)memory;

+ (YKRemoteDevice *)newModel;
+ (YKRemoteDevice *)newMemoryModel;


/**
 导出遥控器为json格式

 @return 字典类型
 */
- (NSDictionary *)toJsonObject;

@end

NS_ASSUME_NONNULL_END
