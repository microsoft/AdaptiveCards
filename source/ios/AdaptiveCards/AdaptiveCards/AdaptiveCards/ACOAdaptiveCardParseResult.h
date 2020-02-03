//
//  ACOAdaptiveCardParseResult.h
//  ACOAdaptiveCardParseResult
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRParseWarning.h"
#import <Foundation/Foundation.h>

@class ACOAdaptiveCard;

@interface ACOAdaptiveCardParseResult : NSObject

@property (readonly) ACOAdaptiveCard *card;
@property (readonly) BOOL isValid;
@property (readonly) NSArray<NSError *> *parseErrors;
@property (readonly) NSArray<ACRParseWarning *> *parseWarnings;

- (instancetype)init:(ACOAdaptiveCard *)card errors:(NSArray<NSError *> *)errors warnings:(NSArray<ACRParseWarning *> *)warnings;

@end
