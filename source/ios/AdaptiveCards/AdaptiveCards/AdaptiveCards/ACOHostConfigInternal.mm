//
//  ACRHostConfigInternal.mm
//  ACRHostConfigInternal.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOHostConfigInternal.h"
#import "HostConfig.h"

using namespace AdaptiveCards;

@implementation ACOHostConfigInternal
{
    std::shared_ptr<HostConfig> hostConfig;
}
- (instancetype)init
{
    self = [super init];
    hostConfig = std::make_shared<HostConfig>();
    return self;
}

+ (ACOParseResult *)FromJson:(NSString *)payload;
{
    ACOParseResult *result = [[ACOParseResult alloc] init];

    if(payload)
    {
        try
        {
            ACOHostConfigInternal *config= [[ACOHostConfigInternal alloc] init];
            *config->hostConfig.get() = AdaptiveCards::HostConfig::DeserializeFromString(std::string([payload UTF8String]));
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
    return hostConfig;
}
@end
