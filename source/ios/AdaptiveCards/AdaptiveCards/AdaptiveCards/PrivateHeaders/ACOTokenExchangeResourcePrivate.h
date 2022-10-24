//
//  ACOTokenExchangeResource.h
//  ACOTokenExchangeResourcePrivate
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOTokenExchangeResource.h"
#import "TokenExchangeResource.h"

using namespace AdaptiveCards;

@interface ACOTokenExchangeResource ()

- (instancetype)init:(std::shared_ptr<TokenExchangeResource> const &)tokenExchangeResourceElement;
- (std::shared_ptr<TokenExchangeResource> const &)adaptiveTokenExchangeResource;

@end
