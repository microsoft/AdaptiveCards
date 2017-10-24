//
//  ACOBaseActionElementPrivate
//  ACOBaseActionElementPrivate.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOBaseActionElement.h"
#import "BaseActionElement.h"

using namespace AdaptiveCards;

@interface ACOBaseActionElement()

- (std::shared_ptr<BaseActionElement>)getElem;
- (void)setElem:(std::shared_ptr<BaseActionElement> const &)elem;

@end    
