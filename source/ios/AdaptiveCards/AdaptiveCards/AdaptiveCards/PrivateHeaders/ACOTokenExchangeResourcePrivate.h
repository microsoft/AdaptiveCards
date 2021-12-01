//
//  ACOTokenExchangeResource.h
//  ACOTokenExchangeResourcePrivate
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACOTokenExchangeResource.h>
#import <AdaptiveCards/TokenExchangeResource.h>

using namespace AdaptiveCards;

@interface ACOTokenExchangeResource ()

- (instancetype)init:(std::shared_ptr<TokenExchangeResource> const &)tokenExchangeResourceElement;
- (std::shared_ptr<TokenExchangeResource> const &)adaptiveTokenExchangeResource;

@end
