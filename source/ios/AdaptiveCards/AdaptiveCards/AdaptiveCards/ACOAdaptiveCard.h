//
//  ACOAdaptiveCard.h
//  ACOAdaptiveCard
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOAdaptiveCardParseResult.h"

@interface ACOAdaptiveCard:NSObject

+ (ACOAdaptiveCardParseResult *)fromJson:(NSString *)payload;
- (NSData *)inputs:(NSError **)error;
- (void) setInputs:(NSMutableArray *)inputs;
- (void) appendInputs:(NSMutableArray *)inputs;

@end
