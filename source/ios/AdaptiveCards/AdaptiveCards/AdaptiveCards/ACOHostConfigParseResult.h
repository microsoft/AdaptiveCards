//
//  ACOHostConfigParseResult.h
//  ACOHostConfigParseResult
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOParseError.h"

@class ACOHostConfig;

@interface ACOHostConfigParseResult:NSObject

@property ACOHostConfig *config;
@property BOOL IsValid;
@property NSMutableArray<ACOParseError *> *parseErrors;

@end    
