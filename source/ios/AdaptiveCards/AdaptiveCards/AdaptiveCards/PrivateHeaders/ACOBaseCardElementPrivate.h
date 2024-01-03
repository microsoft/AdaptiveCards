//
//  ACOBaseCardElementPrivate
//  ACOBaseCardElementPrivate.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACOBaseCardElement.h"
#import "BaseCardElement.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACOBaseCardElement.h>
#import <AdaptiveCards/BaseCardElement.h>
#endif

using namespace AdaptiveCards;

@interface ACOBaseCardElement ()

- (instancetype)initWithBaseCardElement:(std::shared_ptr<BaseCardElement> const &)element;
- (std::shared_ptr<BaseCardElement>)element;
- (void)setElem:(std::shared_ptr<BaseCardElement> const &)elem;

@end
