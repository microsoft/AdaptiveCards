//
//  ACOHostConfigParseResult.h
//  ACOHostConfigParseResult
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ACOHostConfig;

@interface ACOHostConfigParseResult:NSObject

@property ACOHostConfig *config;
@property BOOL IsValid;
@property NSMutableArray<NSError *> *parseErrors;

@end    
