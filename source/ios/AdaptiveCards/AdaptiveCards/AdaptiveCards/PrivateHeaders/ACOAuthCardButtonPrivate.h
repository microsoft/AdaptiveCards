//
//  ACOAuthCardButton.h
//  ACOAuthCardButton
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACOAuthCardButton.h"
#import "AuthCardButton.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACOAuthCardButton.h>
#import <AdaptiveCards/AuthCardButton.h>
#endif

using namespace AdaptiveCards;

@interface ACOAuthCardButton ()

- (instancetype)init:(std::shared_ptr<AuthCardButton> const &)adaptiveAuthCardButton;

- (std::shared_ptr<AuthCardButton> const &)adaptiveButton;

@end
