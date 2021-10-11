//
//  ACRToggleVisibilityTarget
//  ACRToggleVisibilityTarget.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRBaseTarget.h"
#import "ACRIContentHoldingView.h"
#import "ACRView.h"
#import <AdaptiveCards/ToggleVisibilityAction.h>

#import <UIKit/UIKit.h>

@interface ACRToggleVisibilityTarget : ACRBaseTarget

- (instancetype)initWithActionElement:(std::shared_ptr<AdaptiveCards::ToggleVisibilityAction> const &)action
                               config:(ACOHostConfig *)config
                             rootView:(ACRView *)rootView;
@end
