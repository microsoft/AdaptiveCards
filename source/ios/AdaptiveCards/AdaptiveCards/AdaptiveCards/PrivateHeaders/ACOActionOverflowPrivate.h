//
//  ACOActionOverflow
//  ACOActionOverflow.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACOBaseActionElement.h>
#import <AdaptiveCards/BaseActionElement.h>
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@interface ACOActionOverflow : ACOBaseActionElement

- (instancetype)initWithBaseActionElements:(const std::vector<std::shared_ptr<BaseActionElement>> &)elements
                                    atCard:(ACOAdaptiveCard *)card;

@end
