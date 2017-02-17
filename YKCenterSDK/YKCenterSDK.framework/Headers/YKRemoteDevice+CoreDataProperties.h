//
//  YKRemoteDevice+CoreDataProperties.h
//  Pods
//
//  Created by Don on 2017/1/18.
//
//  This file was automatically generated and should not be edited.
//

#import "YKRemoteDevice+CoreDataClass.h"


NS_ASSUME_NONNULL_BEGIN

@interface YKRemoteDevice (CoreDataProperties)

+ (NSFetchRequest<YKRemoteDevice *> *)fetchRequest;

@property (nonatomic) int64_t brandId;
@property (nullable, nonatomic, copy) NSString *desc;
@property (nullable, nonatomic, copy) NSString *remoteId;
@property (nullable, nonatomic, copy) NSString *name;
@property (nullable, nonatomic, copy) NSString *localId;
@property (nullable, nonatomic, copy) NSString *showName;
@property (nullable, nonatomic, copy) NSDate *updateTime;
@property (nonatomic) int64_t typeId;
@property (nullable, nonatomic, copy) NSString *modelName;
@property (nonatomic) int16_t zip;
@property (nullable, nonatomic, copy) NSString *controllerModel;
@property (nonatomic) int16_t version;
@property (nonatomic) int64_t codeset;
@property (nullable, nonatomic, retain) NSOrderedSet<YKRemoteDeviceKey *> *keys;

@end

@interface YKRemoteDevice (CoreDataGeneratedAccessors)

- (void)insertObject:(YKRemoteDeviceKey *)value inKeysAtIndex:(NSUInteger)idx;
- (void)removeObjectFromKeysAtIndex:(NSUInteger)idx;
- (void)insertKeys:(NSArray<YKRemoteDeviceKey *> *)value atIndexes:(NSIndexSet *)indexes;
- (void)removeKeysAtIndexes:(NSIndexSet *)indexes;
- (void)replaceObjectInKeysAtIndex:(NSUInteger)idx withObject:(YKRemoteDeviceKey *)value;
- (void)replaceKeysAtIndexes:(NSIndexSet *)indexes withKeys:(NSArray<YKRemoteDeviceKey *> *)values;
- (void)addKeysObject:(YKRemoteDeviceKey *)value;
- (void)removeKeysObject:(YKRemoteDeviceKey *)value;
- (void)addKeys:(NSOrderedSet<YKRemoteDeviceKey *> *)values;
- (void)removeKeys:(NSOrderedSet<YKRemoteDeviceKey *> *)values;

@end

NS_ASSUME_NONNULL_END
