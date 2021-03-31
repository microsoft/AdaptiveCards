//
//  ACOBaseCardElementPrivate
//  ACOBaseCardElementPrivate.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import "ACOBaseCardElement.h"
#import "BaseCardElement.h"

using namespace AdaptiveCards;

@interface ACOBaseCardElement ()

- (instancetype)initWithBaseCardElement:(std::shared_ptr<BaseCardElement> const &)element;
- (std::shared_ptr<BaseCardElement>)element;
- (void)setElem:(std::shared_ptr<BaseCardElement> const &)elem;
- (NSData *)additionalProperty;

@end
