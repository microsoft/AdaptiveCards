//
//  ACOAdaptiveCard.h
//  ACOAdaptiveCard
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOAdaptiveCardParseResult.h"
#import "ACORemoteResourceInformation.h"

@interface ACOAdaptiveCard:NSObject

+ (ACOAdaptiveCardParseResult *)fromJson:(NSString *)payload;
- (NSData *)inputs;
- (NSArray *)getInputs;
- (void)setInputs:(NSArray *)inputs;
- (void)appendInputs:(NSArray *)inputs;
- (NSArray<ACORemoteResourceInformation *> *)remoteResourceInformation;

@end
