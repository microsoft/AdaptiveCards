//
//  ACOBaseCardElementPrivate
//  ACOBaseCardElementPrivate.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import <AdaptiveCards/ACOBaseCardElement.h>
#import <AdaptiveCards/BaseCardElement.h>

using namespace AdaptiveCards;

@interface ACOBaseCardElement ()

- (instancetype)initWithBaseCardElement:(std::shared_ptr<BaseCardElement> const &)element;
- (std::shared_ptr<BaseCardElement>)element;
- (void)setElem:(std::shared_ptr<BaseCardElement> const &)elem;

@end
