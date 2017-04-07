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

+ (YKRemoteDevice *)modelsWithLocalDeviceId:(NSString *)localDeviceId;
+ (NSArray <YKRemoteDevice *> *)modelsWithDeviceId:(NSString *)enterId;

+ (YKRemoteDevice *)saveRemoteDeviceWithDictionary:(NSDictionary *)dict;

+ (YKRemoteDevice *)newModel;

@end

NS_ASSUME_NONNULL_END
