//
//  ACOAdaptiveCardParseResult.mm
//  ACOAdaptiveCardParseResult.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCardParseResult.h"

@implementation ACOAdaptiveCardParseResult

- (instancetype)init:(ACOAdaptiveCard *)card errors:(NSArray<NSError *> *)errors
{
    self = [super init];
    if(self)
    {
        _card = card;
        _isValid = (_card)? YES : NO;
        _parseErrors = errors;
    }
    return self;
}

@end
