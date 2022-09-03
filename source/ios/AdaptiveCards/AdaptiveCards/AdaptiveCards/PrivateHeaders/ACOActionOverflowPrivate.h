//
//  ACOActionOverflow
//  ACOActionOverflow.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACOBaseActionElement.h"
#import "BaseActionElement.h"
#else
#import <AdaptiveCards/ACOBaseActionElement.h>
#import <AdaptiveCards/BaseActionElement.h>
#endif
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@interface ACOActionOverflow : ACOBaseActionElement

- (instancetype)initWithBaseActionElements:(const std::vector<std::shared_ptr<BaseActionElement>> &)elements
                                    atCard:(ACOAdaptiveCard *)card;

@end
