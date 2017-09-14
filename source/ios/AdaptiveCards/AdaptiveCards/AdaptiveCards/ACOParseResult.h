//
//  ACOParseResult.h
//  ACOParseResult
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOParseResult.h"

@class ACOAdaptiveCards;

@interface ACOParseResult:NSObject

@property ACOAdaptiveCards *card;
@property BOOL IsValid;

@end    
