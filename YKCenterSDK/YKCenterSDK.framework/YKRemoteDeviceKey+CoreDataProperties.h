//
//  YKRemoteDeviceKey+CoreDataProperties.h
//  
//
//  Created by Don on 2017/1/20.
//
//  This file was automatically generated and should not be edited.
//

#import "YKRemoteDeviceKey+CoreDataClass.h"


NS_ASSUME_NONNULL_BEGIN

@interface YKRemoteDeviceKey (CoreDataProperties)

+ (NSFetchRequest<YKRemoteDeviceKey *> *)fetchRequest;

@property (nonatomic) int16_t encode;
@property (nullable, nonatomic, copy) NSString *key;
@property (nullable, nonatomic, copy) NSString *name;
@property (nullable, nonatomic, copy) NSString *one;
@property (nullable, nonatomic, copy) NSString *shortValue;
@property (nullable, nonatomic, copy) NSString *src;
@property (nonatomic) int16_t version;
@property (nullable, nonatomic, copy) NSString *zero;
@property (nonatomic) int16_t zip;

@end

NS_ASSUME_NONNULL_END
