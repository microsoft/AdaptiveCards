//
//  ACOHostConfigParseResult.h
//  ACOHostConfigParseResult
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ACOHostConfig;

@interface ACOHostConfigParseResult : NSObject

@property (readonly) ACOHostConfig *config;
@property (readonly) BOOL isValid;
@property (readonly) NSArray<NSError *> *parseErrors;

- (instancetype)init:(ACOHostConfig *)config errors:(NSArray<NSError *> *)errors;

@end
