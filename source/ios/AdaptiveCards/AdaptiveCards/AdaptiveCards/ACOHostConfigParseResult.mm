//
//  ACOHostConfigParseResult.mm
//  ACOHostConfigParseResult.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOHostConfigParseResult.h"

@implementation ACOHostConfigParseResult

- (instancetype)init:(ACOHostConfig *)config errors:(NSArray<NSError *> *)errors
{
    self = [super init];
    if (self) {
        _config = config;
        _isValid = (_config) ? YES : NO;
        _parseErrors = errors;
    }
    return self;
}

@end
