//
//  ACOWarning
//  ACOWarning.m
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACOWarning.h"

@implementation ACOWarning

- (instancetype)init
{
    return [self initWith:ACRUnknownElementType message:@""];
}

- (instancetype)initWith:(ACRWarningStatusCode)statusCode message:(NSString *)message
{
    self = [super init];

    if (self) {
        _statusCode = statusCode;
        _message = message;
    }

    return self;
}
@end
