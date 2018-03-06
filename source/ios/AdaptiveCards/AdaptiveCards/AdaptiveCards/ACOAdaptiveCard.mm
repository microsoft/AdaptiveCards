//
//  ACOAdaptiveCard.mm
//  ACOAdaptiveCard.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACOAdaptiveCardParseResult.h"
#import "ACRIBaseInputHandler.h"
#import "SharedAdaptiveCard.h"
#import "ACOAdaptiveCardPrivate.h"
#import "AdaptiveCardParseException.h"
#import "ACRErrors.h"

using namespace AdaptiveCards;

@implementation ACOAdaptiveCard
{
    std::shared_ptr<AdaptiveCard> _adaptiveCard;
    NSMutableArray *_inputs;
}

- (void)setInputs:(NSArray *) inputs
{
    _inputs = [[NSMutableArray alloc] initWithArray:inputs];
}

- (void)appendInputs:(NSArray *)inputs
{
    [_inputs addObjectsFromArray:inputs];
}

- (NSData *)inputs
{
    if(_inputs){
        NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
        for(id<ACRIBaseInputHandler> input in _inputs)
        {
            [input getInput:dictionary];
        }

        return [NSJSONSerialization dataWithJSONObject:dictionary options:NSJSONWritingPrettyPrinted error:nil];
    }

    return nil;
}

+ (ACOAdaptiveCardParseResult *)fromJson:(NSString *)payload;
{
    ACOAdaptiveCardParseResult *result = nil;
    if(payload)
    {
        try
        {
            ACOAdaptiveCard *card = [[ACOAdaptiveCard alloc] init];
            card->_adaptiveCard = AdaptiveCard::DeserializeFromString(std::string([payload UTF8String]), 1.0);
            result = [[ACOAdaptiveCardParseResult alloc] init:card errors:nil];
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
            result = [[ACOAdaptiveCardParseResult alloc] init:nil errors:errors];
        }
    }
    return result;
}

- (std::shared_ptr<AdaptiveCard> const &)card
{
    return _adaptiveCard;
}
@end
