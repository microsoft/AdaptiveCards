//
//  ACORemoteResourceInformationPrivate.h
//  ACORemoteResourceInformationPrivate
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import "ACORemoteResourceInformation.h"
#import "RemoteResourceInformation.h"

@interface ACORemoteResourceInformation()

- (instancetype)initWithRemoteResourceInformations:(std::vector<AdaptiveCards::RemoteResourceInformation> const &)remoteResourceInformations;
- (std::vector<AdaptiveCards::RemoteResourceInformation>)getRemoteResourceInformations;
- (void)setRemoteResourceInformations:(std::vector<AdaptiveCards::RemoteResourceInformation> const &)remoteResourceInformations;

@end
