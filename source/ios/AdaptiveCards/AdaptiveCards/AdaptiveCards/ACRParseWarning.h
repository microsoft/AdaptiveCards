//
//  ACRParseWarning
//  ACRParseWarning.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACREnums.h"
#import <Foundation/Foundation.h>

@interface ACRParseWarning : NSObject

@property (readonly) ACRWarningStatusCode statusCode;
@property (readonly) NSString *reason;

@end
