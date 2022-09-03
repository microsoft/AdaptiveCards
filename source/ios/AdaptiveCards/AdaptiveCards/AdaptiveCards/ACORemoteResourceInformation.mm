//
//  ACORemoteResourceInformation.mm
//  ACORemoteResourceInformation.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#ifdef SWIFT_PACKAGE
#import "ACORemoteResourceInformationPrivate.h"
#else
#import <AdaptiveCards/ACORemoteResourceInformationPrivate.h>
#endif
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@implementation ACORemoteResourceInformation

- (instancetype)initWithRemoteResourceInformation:(RemoteResourceInformation const &)remoteResourceInformation
{
    self = [super init];
    if (self) {
        NSString *URLString = [NSString stringWithCString:remoteResourceInformation.url.c_str() encoding:NSUTF8StringEncoding];
        if ([URLString length]) {
            _url = [NSURL URLWithString:URLString];
        }
        _mimeType = [NSString stringWithCString:remoteResourceInformation.mimeType.c_str() encoding:NSUTF8StringEncoding];
        ;
    }
    return self;
}

@end
