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
#import "AdaptiveCardParseWarning.h"
#import "ACRParseWarningPrivate.h"
#import "ParseResult.h"
#import "ACRErrors.h"

using namespace AdaptiveCards;

@implementation ACOAdaptiveCard
{
    std::shared_ptr<AdaptiveCard> _adaptiveCard;
}

+ (ACOAdaptiveCardParseResult *)fromJson:(NSString *)payload;
{
    ACOAdaptiveCardParseResult *result = nil;
    if(payload)
    {
        try
        {
            ACOAdaptiveCard *card = [[ACOAdaptiveCard alloc] init];
            //card->_adaptiveCard = AdaptiveCard::DeserializeFromString(std::string([payload UTF8String]), 1.0)->GetAdaptiveCard();
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(std::string([payload UTF8String]), 1.0);
            NSMutableArray *acrParseWarnings;
            std::vector<std::shared_ptr<AdaptiveCardParseWarning>> parseWarnings = parseResult->GetWarnings();
            for(const auto &warning : parseWarnings){
                ACRParseWarning *acrParseWarning = [[ACRParseWarning alloc] initWithParseWarning:warning];
                [acrParseWarnings addObject:acrParseWarning];
            }
            result = [[ACOAdaptiveCardParseResult alloc] init:card errors:nil warnings:acrParseWarnings];
        }
        catch(const AdaptiveCardParseException& e)
        {
            // converts AdaptiveCardParseException to NSError
            ErrorStatusCode errorStatusCode = e.GetStatusCode();
            NSInteger errorCode = (long)errorStatusCode;

            NSError *parseError = [NSError errorWithDomain:ACRParseErrorDomain
                                                      code:errorCode
                                                  userInfo:nil];
            NSArray<NSError *> *errors = @[parseError];
            result = [[ACOAdaptiveCardParseResult alloc] init:nil errors:errors warnings:nil];
        }
    }
    return result;
}

- (std::shared_ptr<AdaptiveCard> const &)getCard
{
    return _adaptiveCard;
}
@end
