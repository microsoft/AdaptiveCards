#import <Foundation/Foundation.h>

#import "ACSHostConfigParseResult.h"

@implementation ACSHostConfigParseResult

- (instancetype)initWithConfig:(ACSHostConfig *)config error:(NSError *)error
{
    self = [super init];
    if (self) {
        _config = config;
        _isValid = (_config) ? YES : NO;
        _error = error;
    }
    return self;
}

@end
