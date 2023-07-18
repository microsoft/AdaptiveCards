//
//  ACRShowCardTarget
//  ACRShowCardTarget.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACRBaseTarget.h"
#import "ACRIContentHoldingView.h"
#import "ACRView.h"
#import "SharedAdaptiveCard.h"
#import "ShowCardAction.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACRBaseTarget.h>
#import <AdaptiveCards/ACRIContentHoldingView.h>
#import <AdaptiveCards/ACRView.h>
#import <AdaptiveCards/SharedAdaptiveCard.h>
#import <AdaptiveCards/ShowCardAction.h>
#endif
#import <UIKit/UIKit.h>

@interface ACRShowCardTarget : ACRBaseTarget

- (instancetype)initWithActionElement:(std::shared_ptr<AdaptiveCards::ShowCardAction> const &)showCardActionElement
                               config:(ACOHostConfig *)config
                             rootView:(ACRView *)rootView
                               button:(UIButton *)button;

- (void)createShowCard:(NSMutableArray *)inputs superview:(UIView<ACRIContentHoldingView> *)superview;

// show or hide a showCard UIView. If the UIView is not created already, it will be created and shown
// else, it toggles the visibility
- (IBAction)toggleVisibilityOfShowCard;

- (void)hideShowCard;
@end
