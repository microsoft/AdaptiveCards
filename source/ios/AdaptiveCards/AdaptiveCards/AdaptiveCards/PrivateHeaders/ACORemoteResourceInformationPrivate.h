//
//  ACORemoteResourceInformationPrivate.h
//  ACORemoteResourceInformationPrivate
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import <AdaptiveCards/ACORemoteResourceInformation.h>
#import <AdaptiveCards/RemoteResourceInformation.h>

@interface ACORemoteResourceInformation ()

- (instancetype)initWithRemoteResourceInformation:(AdaptiveCards::RemoteResourceInformation const &)remoteResourceInformation;

@end
