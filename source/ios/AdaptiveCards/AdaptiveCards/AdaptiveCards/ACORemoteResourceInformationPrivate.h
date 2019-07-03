//
//  ACORemoteResourceInformationPrivate.h
//  ACORemoteResourceInformationPrivate
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import "ACORemoteResourceInformation.h"
#import "RemoteResourceInformation.h"

@interface ACORemoteResourceInformation ()

- (instancetype)initWithRemoteResourceInformation:(AdaptiveCards::RemoteResourceInformation const &)remoteResourceInformation;

@end
