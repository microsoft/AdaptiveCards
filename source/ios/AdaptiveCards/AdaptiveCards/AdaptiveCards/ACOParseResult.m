//
//  ACOParseResult.mm
//  ACOParseResult.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOAdaptiveCards.h"

@implementation ACOParseResult

- (instancetype)init
{
    self = [super init];
    if(self)
    {
        self.IsValid = NO;
        self.card = nil;
    }
    return self;
}

@end
