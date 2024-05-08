//
//  ACRToggleVisibilityTarget
//  ACRToggleVisibilityTarget.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACRBaseTarget.h"
#import "ACRIContentHoldingView.h"
#import "ACRView.h"
#import "ToggleVisibilityAction.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACRBaseTarget.h>
#import <AdaptiveCards/ACRIContentHoldingView.h>
#import <AdaptiveCards/ACRView.h>
#import <AdaptiveCards/ToggleVisibilityAction.h>
#endif

#import <UIKit/UIKit.h>

@interface ACRToggleVisibilityTarget : ACRBaseTarget

- (instancetype)initWithActionElement:(std::shared_ptr<AdaptiveCards::ToggleVisibilityAction> const &)action
                               config:(ACOHostConfig *)config
                             rootView:(ACRView *)rootView;
@end
