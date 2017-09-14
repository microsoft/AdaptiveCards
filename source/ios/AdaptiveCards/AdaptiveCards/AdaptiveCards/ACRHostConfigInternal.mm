//
//  ACRHostConfigInternal.mm
//  ACRHostConfigInternal.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACRHostConfigInternal.h"
#import "HostConfig.h"

using namespace AdaptiveCards;

@implementation ACRHostConfigInternal

- (instancetype)init
{
    self = [super init];
    self.hostConfig = HostConfig();
    return self;
}

- (ACRHostConfig *)fromJson:(NSString *)payload;
{
    if(payload)
    {
        self.hostConfig = AdaptiveCards::HostConfig::DeserializeFromString(std::string([payload UTF8String]));
    }
    return self;
}

@end
