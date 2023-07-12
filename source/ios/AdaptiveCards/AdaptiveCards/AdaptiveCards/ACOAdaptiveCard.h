//
//  ACOAdaptiveCard.h
//  ACOAdaptiveCard
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACOAdaptiveCardParseResult.h"
#import "ACOAuthentication.h"
#import "ACORefresh.h"
#import "ACORemoteResourceInformation.h"
#import "ACRIBaseInputHandler.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACOAdaptiveCardParseResult.h>
#import <AdaptiveCards/ACOAuthentication.h>
#import <AdaptiveCards/ACORefresh.h>
#import <AdaptiveCards/ACORemoteResourceInformation.h>
#import <AdaptiveCards/ACRIBaseInputHandler.h>
#endif
#import <Foundation/Foundation.h>

@interface ACOAdaptiveCard : NSObject

@property ACORefresh *refresh;
@property ACOAuthentication *authentication;

+ (ACOAdaptiveCardParseResult *)fromJson:(NSString *)payload;
- (NSData *)inputs;
- (NSArray<ACRIBaseInputHandler> *)getInputs;
- (void)setInputs:(NSArray *)inputs;
- (void)appendInputs:(NSArray *)inputs;
- (NSArray<ACORemoteResourceInformation *> *)remoteResourceInformation;
- (NSData *)additionalProperty;

@end
