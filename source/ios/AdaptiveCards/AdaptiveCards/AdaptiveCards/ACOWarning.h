//
//  ACOWarning
//  ACOWarning.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACREnums.h"
#else
#import <AdaptiveCards/ACREnums.h>
#endif
#import <Foundation/Foundation.h>

@interface ACOWarning : NSObject

@property ACRWarningStatusCode statusCode;
@property NSString *message;

- (instancetype)initWith:(ACRWarningStatusCode)statusCode message:(NSString *)message;

@end
