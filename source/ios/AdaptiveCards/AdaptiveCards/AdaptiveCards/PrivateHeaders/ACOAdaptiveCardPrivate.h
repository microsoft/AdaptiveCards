//
//  ACOAdaptiveCardPrivate.h
//  ACOAdaptiveCardPrivate
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef USE_AC_SWIFT_PACKAGE
#import "ACOAdaptiveCard.h"
#import "SharedAdaptiveCard.h"
#else
#import <AdaptiveCards/ACOAdaptiveCard.h>
#import <AdaptiveCards/SharedAdaptiveCard.h>
#endif
using namespace AdaptiveCards;

@interface ACOAdaptiveCard ()

- (std::shared_ptr<AdaptiveCard> const &)card;
- (void)setCard:(std::shared_ptr<AdaptiveCard> const &)card;

@end
