//
//  ACORemoteResourceInformationPrivate.h
//  ACORemoteResourceInformationPrivate
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#ifdef SWIFT_PACKAGE
#import "ACORemoteResourceInformation.h"
#import "RemoteResourceInformation.h"
#else
#import <AdaptiveCards/ACORemoteResourceInformation.h>
#import <AdaptiveCards/RemoteResourceInformation.h>
#endif

@interface ACORemoteResourceInformation ()

- (instancetype)initWithRemoteResourceInformation:(AdaptiveCards::RemoteResourceInformation const &)remoteResourceInformation;

@end
