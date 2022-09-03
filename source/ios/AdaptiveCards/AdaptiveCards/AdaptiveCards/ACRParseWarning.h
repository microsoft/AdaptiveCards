//
//  ACRParseWarning
//  ACRParseWarning.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACREnums.h"
#else
#import <AdaptiveCards/ACREnums.h>
#endif
#import <Foundation/Foundation.h>

@interface ACRParseWarning : NSObject

@property (readonly) ACRWarningStatusCode statusCode;
@property (readonly) NSString *reason;

@end
