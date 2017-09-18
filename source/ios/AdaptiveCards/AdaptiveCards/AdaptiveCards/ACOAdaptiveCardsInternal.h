//
//  ACOAdaptiveCardsInternal.h
//  ACOAdaptiveCardsInternal
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCards.h"
#import "SharedAdaptiveCard.h"
using namespace AdaptiveCards;

@interface ACOAdaptiveCardsInternal:ACOAdaptiveCards
- (std::shared_ptr<AdaptiveCard> const &)getCard;
@end
