//
//  ACOAdaptiveCards.mm
//  ACOAdaptiveCards.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACOAdaptiveCardsInternal.h"

@implementation ACOAdaptiveCards

- (instancetype)init
{
    self = [super init];
    return self;
}

+ (ACOParseResult *)FromJson:(NSString *)payload;
{
    return [ACOAdaptiveCardsInternal FromJson:payload];
}

@end
