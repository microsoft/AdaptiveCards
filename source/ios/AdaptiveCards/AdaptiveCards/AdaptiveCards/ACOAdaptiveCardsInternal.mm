//
//  ACOAdaptiveCardsInternal.mm
//  ACOAdaptiveCardsInternal.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOAdaptiveCardsInternal.h"
#import "ACOParseResult.h"
#import "SharedAdaptiveCard.h"

using namespace AdaptiveCards;

@implementation ACOAdaptiveCardsInternal
{
    std::shared_ptr<AdaptiveCard> adaptiveCard;
}

- (instancetype)init
{
    self = [super init];
    return self;
}

+ (ACOParseResult *)FromJson:(NSString *)payload;
{
    ACOParseResult *result = [[ACOParseResult alloc] init];

    if(payload)
    {
        try
        {
            ACOAdaptiveCardsInternal *card = [[ACOAdaptiveCardsInternal alloc] init];
            card->adaptiveCard = AdaptiveCard::DeserializeFromString(std::string([payload UTF8String]));
            result.card = card;
            result.IsValid = YES;
        }
        catch(...)
        {
            result.IsValid = NO;
        }
    }
    return result;
}

@end
