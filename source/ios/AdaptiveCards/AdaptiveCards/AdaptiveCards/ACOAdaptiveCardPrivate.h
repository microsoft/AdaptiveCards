//
//  ACOAdaptiveCardPrivate.h
//  ACOAdaptiveCardPrivate
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCard.h"
#import "SharedAdaptiveCard.h"
using namespace AdaptiveCards;

@interface ACOAdaptiveCard()

- (std::shared_ptr<AdaptiveCard> const &)card;

@end
