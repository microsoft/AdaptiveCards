//
//  ACOAdaptiveCardPrivate.h
//  ACOAdaptiveCardPrivate
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCard.h"
#import "SharedAdaptiveCard.h"
using namespace AdaptiveCards;

@interface ACOAdaptiveCard()

- (instancetype)initWithAdaptiveCard:(std::shared_ptr<AdaptiveCard> const &)card;
- (std::shared_ptr<AdaptiveCard> const &)card;
- (void)setCard:(std::shared_ptr<AdaptiveCard> const &)card;

@end
