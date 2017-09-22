//
//  ACOAdaptiveCards.mm
//  ACOAdaptiveCards.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACOParseResult.h"
#import "SharedAdaptiveCard.h"

@implementation ACOAdaptiveCards
{
    std::shared_ptr<AdaptiveCard> _adaptiveCard;
}

+ (ACOParseResult *)FromJson:(NSString *)payload;
{
    ACOParseResult *result = [[ACOParseResult alloc] init];

    if(payload)
    {
        try
        {
            ACOAdaptiveCards *card = [[ACOAdaptiveCards alloc] init];
            card->_adaptiveCard = AdaptiveCard::DeserializeFromString(std::string([payload UTF8String]));
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

- (std::shared_ptr<AdaptiveCard> const &)getCard
{
    return _adaptiveCard;
}
@end
