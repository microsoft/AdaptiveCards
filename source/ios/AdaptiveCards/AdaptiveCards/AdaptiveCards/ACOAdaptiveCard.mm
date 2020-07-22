//
//  ACOAdaptiveCard.mm
//  ACOAdaptiveCard.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOAdaptiveCardParseResult.h"
#import "ACOAdaptiveCardPrivate.h"
#import "ACORemoteResourceInformationPrivate.h"
#import "ACRErrors.h"
#import "ACRIBaseInputHandler.h"
#import "ACRParseWarningPrivate.h"
#import "AdaptiveCardParseException.h"
#import "AdaptiveCardParseWarning.h"
#import "ParseResult.h"
#import "SharedAdaptiveCard.h"
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@implementation ACOAdaptiveCard {
    std::shared_ptr<AdaptiveCard> _adaptiveCard;
    NSMutableArray<ACRIBaseInputHandler> *_inputs;
}

- (void)setInputs:(NSArray *)inputs
{
    _inputs = [[NSMutableArray<ACRIBaseInputHandler> alloc] initWithArray:inputs];
}

- (void)appendInputs:(NSArray *)inputs
{
    [_inputs addObjectsFromArray:inputs];
}

- (NSData *)inputs
{
    if (_inputs) {
        NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
        for (id<ACRIBaseInputHandler> input in _inputs) {
            [input getInput:dictionary];
        }

        return [NSJSONSerialization dataWithJSONObject:dictionary options:NSJSONWritingPrettyPrinted error:nil];
    }

    return nil;
}

- (NSArray<ACRIBaseInputHandler> *)getInputs
{
    return _inputs;
}

+ (ACOAdaptiveCardParseResult *)fromJson:(NSString *)payload;
{
    ACOAdaptiveCardParseResult *result = nil;
    if (payload) {
        try {
            ACOAdaptiveCard *card = [[ACOAdaptiveCard alloc] init];
            std::shared_ptr<ParseResult> parseResult = AdaptiveCard::DeserializeFromString(std::string([payload UTF8String]), std::string("1.3"));
            NSMutableArray *acrParseWarnings;
            std::vector<std::shared_ptr<AdaptiveCardParseWarning>> parseWarnings = parseResult->GetWarnings();
            for (const auto &warning : parseWarnings) {
                ACRParseWarning *acrParseWarning = [[ACRParseWarning alloc] initWithParseWarning:warning];
                [acrParseWarnings addObject:acrParseWarning];
            }
            card->_adaptiveCard = parseResult->GetAdaptiveCard();
            result = [[ACOAdaptiveCardParseResult alloc] init:card errors:nil warnings:acrParseWarnings];
        } catch (const AdaptiveCardParseException &e) {
            // converts AdaptiveCardParseException to NSError
            ErrorStatusCode errorStatusCode = e.GetStatusCode();
            NSInteger errorCode = (long)errorStatusCode;

            NSError *parseError = [NSError errorWithDomain:ACRParseErrorDomain
                                                      code:errorCode
                                                  userInfo:nil];
            NSArray<NSError *> *errors = @[ parseError ];
            result = [[ACOAdaptiveCardParseResult alloc] init:nil errors:errors warnings:nil];
        }
    }
    return result;
}

- (std::shared_ptr<AdaptiveCard> const &)card
{
    return _adaptiveCard;
}

- (void)setCard:(std::shared_ptr<AdaptiveCard> const &)card
{
    _adaptiveCard = card;
}

- (NSArray<ACORemoteResourceInformation *> *)remoteResourceInformation
{
    NSMutableArray *mutableRemoteResources = nil;
    std::vector<RemoteResourceInformation> remoteResourceVector = _adaptiveCard->GetResourceInformation();
    if (!remoteResourceVector.empty()) {
        mutableRemoteResources = [[NSMutableArray alloc] init];
        for (const auto &remoteResource : remoteResourceVector) {
            ACORemoteResourceInformation *remoteResourceObjc =
                [[ACORemoteResourceInformation alloc] initWithRemoteResourceInformation:remoteResource];
            if (remoteResourceObjc) {
                [mutableRemoteResources addObject:remoteResourceObjc];
            }
        }
        NSArray<ACORemoteResourceInformation *> *remoteResources = [NSArray arrayWithArray:mutableRemoteResources];
        return remoteResources;
    }
    return nil;
}

@end
