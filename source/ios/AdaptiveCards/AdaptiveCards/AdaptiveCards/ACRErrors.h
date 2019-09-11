//
//  ACRErrors
//  ACRErrors.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const ACRInputErrorDomain;
extern NSString *const ACRParseErrorDomain;

typedef NS_ENUM(NSUInteger, ACRInputError) {
    ACRInputErrorValueMissing,
    ACRInputErrorLessThanMin,
    ACRInputErrorGreaterThanMax,
    ACRInputErrorLessThanMinDate,
    ACRInputErrorGreaterThanMaxDate,
};

typedef NS_ENUM(NSUInteger, ACRRenderingStatus) {
    ACROk = 0,
    ACRFailed,
    ACRUnsupported,
};

@interface ACOFallbackException : NSObject

+ (ACOFallbackException *)fallbackException;

@end
