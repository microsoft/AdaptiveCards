//
//  ACOAdaptiveCard.mm
//  ACOAdaptiveCard.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACOAdaptiveCardParseResult.h"
#import "SharedAdaptiveCard.h"
#import "ACOAdaptiveCardPrivate.h"
#import "AdaptiveCardParseException.h"

using namespace AdaptiveCards;

@implementation ACOAdaptiveCard
{
    std::shared_ptr<AdaptiveCard> _adaptiveCard;
}

+ (ACOAdaptiveCardParseResult *)fromJson:(NSString *)payload;
{
    ACOAdaptiveCardParseResult *result = [[ACOAdaptiveCardParseResult alloc] init];

    if(payload)
    {
        try
        {
            ACOAdaptiveCard *card = [[ACOAdaptiveCard alloc] init];
            card->_adaptiveCard = AdaptiveCard::DeserializeFromString(std::string([payload UTF8String]));
            result.card = card;
            result.IsValid = YES;
        }
        catch(const AdaptiveCardParseException& e)
        {
            // covert AdaptiveCardParseException to ACOParseError
            ErrorStatusCode errorStatusCode = e.GetStatusCode();
            NSNumber* errorCode = [NSNumber numberWithInt:(int)errorStatusCode];
            NSString *errorMessage= [NSString stringWithCString:e.GetMessage().c_str()
                                                  encoding:[NSString defaultCStringEncoding]];
            ACOParseError *parseError = [[ACOParseError alloc] init:errorMessage errorCode:errorCode];
            [result.parseErrors addObject:parseError];
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
