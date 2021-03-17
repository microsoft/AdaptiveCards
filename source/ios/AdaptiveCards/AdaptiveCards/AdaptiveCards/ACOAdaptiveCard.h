//
//  ACOAdaptiveCard.h
//  ACOAdaptiveCard
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCardParseResult.h"
#import "ACORemoteResourceInformation.h"
#import "ACRIBaseInputHandler.h"
#import "ACORefresh.h"
#import "ACOAuthentication.h"
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
