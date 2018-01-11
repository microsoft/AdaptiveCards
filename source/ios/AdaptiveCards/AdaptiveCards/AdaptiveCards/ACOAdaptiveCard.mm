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
            HString errorMessage;
            ErrorStatusCode statusCode = e.GetStatusCode();
            std::string errorMessage = e.GetMessage();
            ComPtr<IAdaptiveError> adaptiveError;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveError>(&adaptiveError, statusCode, errorMessage.Get()));
            RETURN_IF_FAILED(errors->Append(adaptiveError.Get()));
            return adaptiveParseResult.CopyTo(parseResult);
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
