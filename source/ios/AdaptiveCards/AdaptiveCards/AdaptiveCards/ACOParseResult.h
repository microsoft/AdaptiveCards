//
//  ACOParseResult.h
//  ACOParseResult
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

@class ACOAdaptiveCard;
@class ACOHostConfig;

@interface ACOParseResult:NSObject

@property ACOHostConfig *config;
@property ACOAdaptiveCard *card;
@property BOOL IsValid;

@end    
