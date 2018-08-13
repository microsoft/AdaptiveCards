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

- (instancetype)initWithRemoteResourceInformation:(RemoteResourceInformation const &)remoteResourceInformation
{
    self = [super init];
    if(self){
        NSString *URLString = [NSString stringWithCString:remoteResourceInformation.url.c_str() encoding:NSUTF8StringEncoding];
        if([URLString length]){
            _url =[NSURL URLWithString:URLString];
        }
        _mimeType = [NSString stringWithCString:remoteResourceInformation.mimeType.c_str() encoding:NSUTF8StringEncoding]; ;
        _resourceType = (ACRCardElementType)remoteResourceInformation.resourceType;
    }
    return self;
}

@end
