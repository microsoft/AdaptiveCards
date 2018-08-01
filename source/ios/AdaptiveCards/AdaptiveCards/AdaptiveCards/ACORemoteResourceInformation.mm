//
//  ACORemoteResourceInformation.mm
//  ACORemoteResourceInformation.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACORemoteResourceInformationPrivate.h"

using namespace AdaptiveCards;

@implementation ACORemoteResourceInformation
{
    std::vector<RemoteResourceInformation> _remoteResourceInformations;
}

- (instancetype)initWithRemoteResourceInformations:(std::vector<RemoteResourceInformation> const &)remoteResourceInformations
{
    self = [super init];
    if(self){
        _remoteResourceInformations = remoteResourceInformations;
    }
    return self;
}

- (std::vector<AdaptiveCards::RemoteResourceInformation>)getRemoteResourceInformations
{
    return _remoteResourceInformations;
}

- (void)setRemoteResourceInformations:(std::vector<AdaptiveCards::RemoteResourceInformation> const &)remoteResourceInformations
{
    _remoteResourceInformations = remoteResourceInformations;
}

@end
