//
//  ACRShowCardTarget
//  ACRShowCardTarget.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRIContentHoldingView.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"
#import "ACRView.h"
#import "SharedAdaptiveCard.h"
#import "ShowCardAction.h"
#import <UIKit/UIKit.h>

@interface ACRShowCardTarget : NSObject <ACRSelectActionDelegate>

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
