//
//  ACRToggleVisibilityTarget
//  ACRToggleVisibilityTarget.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRIContentHoldingView.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"
#import "ACRView.h"
#import "ToggleVisibilityAction.h"
#import <UIKit/UIKit.h>

@interface ACRToggleVisibilityTarget : NSObject <ACRSelectActionDelegate>

- (instancetype)initWithActionElement:(std::shared_ptr<AdaptiveCards::ToggleVisibilityAction> const &)action
                               config:(ACOHostConfig *)config
                             rootView:(ACRView *)rootView;
@end
