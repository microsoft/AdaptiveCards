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
#import "ACRErrors.h"

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
            // converts AdaptiveCardParseException to NSError
            ErrorStatusCode errorStatusCode = e.GetStatusCode();
            NSInteger errorCode = (long)errorStatusCode;
            NSString *errorMessage= [NSString stringWithCString:e.GetMessage().c_str()
                                                  encoding:[NSString defaultCStringEncoding]];
            NSError *parseError = [NSError errorWithDomain:ACRParseErrorDomain
                                                      code:errorCode
                                                  userInfo:@{NSLocalizedFailureReasonErrorKey:errorMessage}];
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
