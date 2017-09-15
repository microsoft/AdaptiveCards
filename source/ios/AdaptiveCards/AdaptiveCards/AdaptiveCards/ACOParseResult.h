//
//  ACOParseResult.h
//  ACOParseResult
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOParseResult.h"

@class ACOAdaptiveCards;
@class ACOHostConfig;

@interface ACOParseResult:NSObject

@property ACOHostConfig *config;
@property ACOAdaptiveCards *card;
@property BOOL IsValid;

@end    
