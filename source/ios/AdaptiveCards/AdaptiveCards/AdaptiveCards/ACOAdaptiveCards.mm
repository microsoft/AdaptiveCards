//
//  ACOAdaptiveCards.mm
//  ACOAdaptiveCards.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACOAdaptiveCardsInternal.h"

@implementation ACOAdaptiveCards

+ (ACOParseResult *)FromJson:(NSString *)payload;
{
    return [ACOAdaptiveCardsInternal FromJson:payload];
}

@end
