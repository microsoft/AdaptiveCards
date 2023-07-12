//
//  ACORemoteResourceInformationPrivate.h
//  ACORemoteResourceInformationPrivate
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACORemoteResourceInformation.h"
#import "RemoteResourceInformation.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACORemoteResourceInformation.h>
#import <AdaptiveCards/RemoteResourceInformation.h>
#endif

@interface ACORemoteResourceInformation ()

- (instancetype)initWithRemoteResourceInformation:(AdaptiveCards::RemoteResourceInformation const &)remoteResourceInformation;

@end
