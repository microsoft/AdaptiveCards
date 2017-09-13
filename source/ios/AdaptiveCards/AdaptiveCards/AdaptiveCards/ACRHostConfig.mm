//
//  ACRHostConfig.mm
//  ACRHostConfig.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACRHostConfig.h"
#import "HostConfig.h"

using namespace AdaptiveCards;

@implementation ACRHostConfig
{
    HostConfig hostConfig;
}

- (instancetype)init
{
    self = [self initWithJson:nil];
    return self;
}

- (instancetype)initWithJson:(NSString *)payload
{
    self = [super init];
    if(self)
    {
        if(payload)
        {
            hostConfig = AdaptiveCards::HostConfig::DeserializeFromString(std::string([payload UTF8String]));
        }
    }
    return self;
}

@end
