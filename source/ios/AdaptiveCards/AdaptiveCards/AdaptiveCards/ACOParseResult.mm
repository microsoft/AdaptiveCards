//
//  ACOParseResult.mm
//  ACOParseResult.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOAdaptiveCard.h"

@implementation ACOParseResult

- (instancetype)init
{
    self = [super init];
    if(self)
    {
        self.IsValid = NO;
        self.config = nil;
        self.card = nil;
    }
    return self;
}

@end
