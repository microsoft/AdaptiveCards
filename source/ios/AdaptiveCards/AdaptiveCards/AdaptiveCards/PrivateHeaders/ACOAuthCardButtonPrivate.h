//
//  ACOAuthCardButton.h
//  ACOAuthCardButton
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACOAuthCardButton.h>
#import <AdaptiveCards/AuthCardButton.h>

using namespace AdaptiveCards;

@interface ACOAuthCardButton ()

- (instancetype)init:(std::shared_ptr<AuthCardButton> const &)adaptiveAuthCardButton;

- (std::shared_ptr<AuthCardButton> const &)adaptiveButton;

@end
