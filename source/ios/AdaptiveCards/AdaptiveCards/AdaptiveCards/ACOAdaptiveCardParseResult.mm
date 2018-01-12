//
//  ACOAdaptiveCardParseResult.mm
//  ACOAdaptiveCardParseResult.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCardParseResult.h"

@implementation ACOAdaptiveCardParseResult

- (instancetype)init
{
    self = [super init];
    if(self)
    {
        self.card = nil;
        self.IsValid = NO;
        self.parseErrors = [[NSMutableArray alloc] init];
    }
    return self;
}

@end
