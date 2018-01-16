//
//  ACRShowCardTarget
//  ACRShowCardTarget.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRIContentHoldingView.h"
#import "SharedAdaptiveCard.h"
#import "HostConfig.h"

@interface ACRShowCardTarget:NSObject<UIGestureRecognizerDelegate>

- (instancetype)initWithAdaptiveCard:(std::shared_ptr<AdaptiveCards::AdaptiveCard> const &)adaptiveCard 
                              config:(std::shared_ptr<AdaptiveCards::HostConfig> const&)config
                           superview:(UIView<ACRIContentHoldingView> *)superview
                                  vc:(UIViewController *)vc;

- (instancetype)initWithAdaptiveCard:(std::shared_ptr<AdaptiveCards::AdaptiveCard> const &)adaptiveCard
                              config:(std::shared_ptr<AdaptiveCards::HostConfig> const&)config
                           superview:(UIView<ACRIContentHoldingView> *)superview
                                  vc:(UIViewController *)vc
                          targetView:(UIView *)targetView;
// show or hide a showCard UIView. If the UIView is not created already, it will be created and shown
// else, it toggles the visibility
- (IBAction)toggleVisibilityOfShowCard;

- (IBAction)toggleVisibilityOfShowCard:(UILongPressGestureRecognizer *) recognizer;

@end
