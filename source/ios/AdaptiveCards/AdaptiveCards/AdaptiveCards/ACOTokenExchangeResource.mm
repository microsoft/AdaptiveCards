//
//  ACOTokenExchangeResource
//  ACOTokenExchangeResource.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//
//
//

#import "ACOBaseActionElementPrivate.h"
#import "ACOTokenExchangeResourcePrivate.h"

@implementation ACOTokenExchangeResource {
    std::shared_ptr<TokenExchangeResource> _adaptiveTokenExchangeResource;
}

- (instancetype)init:(std::shared_ptr<TokenExchangeResource> const &)adaptiveTokenExchangeResource;
{
    self = [super init];
    if (self && adaptiveTokenExchangeResource) {
        _adaptiveTokenExchangeResource = adaptiveTokenExchangeResource;
        _Id = [NSString stringWithCString:adaptiveTokenExchangeResource->GetId().c_str() encoding:NSUTF8StringEncoding];
        _uri = [NSString stringWithCString:adaptiveTokenExchangeResource->GetUri().c_str() encoding:NSUTF8StringEncoding];
        _providerId = [NSString stringWithCString:adaptiveTokenExchangeResource->GetProviderId().c_str() encoding:NSUTF8StringEncoding];
    }
    return self;
}

- (instancetype)init:(NSString *)stringId uri:(NSString *)uri providerId:(NSString *)providerId
{
    std::string cid, curi, cproviderId;
    if (stringId) {
        cid = [stringId UTF8String];
    }

    if (uri) {
        curi = [uri UTF8String];
    }

    if (providerId) {
        cproviderId = [providerId UTF8String];
    }

    return [self init:std::make_shared<TokenExchangeResource>(cid, curi, cproviderId)];
}

- (instancetype)init
{
    return [self init:nil];
}

- (std::shared_ptr<TokenExchangeResource> const &)adaptiveTokenExchangeResource
{
    return _adaptiveTokenExchangeResource;
}
@end
