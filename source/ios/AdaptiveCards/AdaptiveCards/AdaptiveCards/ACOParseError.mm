//
//  ACOParseError.mm
//  ACOParseError.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOParseError.h"

@implementation ACOParseError
- (instancetype)init:(NSString *)errorMessage errorCode:(NSNumber *)errorCode
{
    self = [super init];
    if(self)
    {
        self.errorMessage = errorMessage;
        self.errorCode = errorCode;
    }
    return self;
}

- (instancetype)init
{
    self = [super init];
    if(self)
    {
        self = [self init:nil errorCode:@0];
    }
    return self;
}
@end
