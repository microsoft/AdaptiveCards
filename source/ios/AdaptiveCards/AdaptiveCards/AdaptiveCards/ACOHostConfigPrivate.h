//
//  ACRHostConfigPrivate.h
//  ACRHostConfigPrivate
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOHostConfig.h"
#import "HostConfig.h"

using namespace AdaptiveCards;

@interface ACOHostConfig()

- (std::shared_ptr<HostConfig> const &)getHostConfig;

@end    
