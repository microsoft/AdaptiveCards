//
//  ACOBaseActionElementPrivate
//  ACOBaseActionElementPrivate.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOBaseActionElement.h"
#import "BaseActionElement.h"

using namespace AdaptiveCards;

@interface ACOBaseActionElement ()

- (instancetype)initWithBaseActionElement:(std::shared_ptr<BaseActionElement> const &)element;
- (std::shared_ptr<BaseActionElement>)element;
- (void)setElem:(std::shared_ptr<BaseActionElement> const &)elem;

@end
