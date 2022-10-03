//
//  ACOAuthentication.h
//  ACOAuthentication
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef USE_AC_SWIFT_PACKAGE
#import "ACOAuthentication.h"
#import "Authentication.h"
#else
#import <AdaptiveCards/ACOAuthentication.h>
#import <AdaptiveCards/Authentication.h>
#endif

using namespace AdaptiveCards;

@interface ACOAuthentication ()

- (instancetype)init:(std::shared_ptr<Authentication> const &)adaptiveAuthentication;

@end
