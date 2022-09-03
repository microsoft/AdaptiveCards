//
//  ACRErrors
//  ACRErrors.m
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRErrors.h"
#else
#import <AdaptiveCards/ACRErrors.h>
#endif

NSString *const ACRInputErrorDomain = @"ACRInputErrorDomain";
NSString *const ACRParseErrorDomain = @"ACRParseErrorDomain";

@implementation ACOFallbackException

+ (ACOFallbackException *)fallbackException
{
    ACOFallbackException *fallbackException = [[ACOFallbackException alloc] init];
    return fallbackException;
}

@end
