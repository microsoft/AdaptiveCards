//
//  ACOAuthentication.h
//  ACOAuthentication
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACOAuthentication.h>
#import <AdaptiveCards/Authentication.h>

using namespace AdaptiveCards;

@interface ACOAuthentication ()

- (instancetype)init:(std::shared_ptr<Authentication> const &)adaptiveAuthentication;

@end
