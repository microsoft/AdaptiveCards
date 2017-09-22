//
//  ACRHostConfig.mm
//  ACRHostConfig.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACOHostConfig.h"
#import "HostConfig.h"

using namespace AdaptiveCards;

@implementation ACOHostConfig
{
    std::shared_ptr<HostConfig> _config;
}

- (instancetype)init
{
    self = [super init];
    _config = std::make_shared<HostConfig>();
    return self;
}

+ (ACOParseResult *)fromJson:(NSString *)payload;
{
    ACOParseResult *result = [[ACOParseResult alloc] init];

    if(payload)
    {
        try
        {
            ACOHostConfig *config= [[ACOHostConfig alloc] init];
            *config->_config.get() = AdaptiveCards::HostConfig::DeserializeFromString(std::string([payload UTF8String]));
            result.config = config;
            result.IsValid = YES;
        }
        catch(...)
        {
            result.IsValid = NO;
        }
    }
    return result;
}

- (std::shared_ptr<HostConfig> const &)getHostConfig
{
    return _config;
}

@end
