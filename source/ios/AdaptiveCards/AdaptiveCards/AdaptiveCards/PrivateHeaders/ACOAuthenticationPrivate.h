//
//  ACOAuthentication.h
//  ACOAuthentication
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACOAuthentication.h"
#import "Authentication.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACOAuthentication.h>
#import <AdaptiveCards/Authentication.h>
#endif

using namespace AdaptiveCards;

@interface ACOAuthentication ()

- (instancetype)init:(std::shared_ptr<Authentication> const &)adaptiveAuthentication;

@end
