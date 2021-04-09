//
//  ACOActionOverflow
//  ACOActionOverflow.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOBaseActionElement.h"
#import <Foundation/Foundation.h>

@interface ACOActionOverflow : ACOBaseActionElement

- (instancetype)initWithBaseActionElements:(const std::vector<std::shared_ptr<BaseActionElement>> &)elements
                                    atCard:(ACOAdaptiveCard*)card;

@end
