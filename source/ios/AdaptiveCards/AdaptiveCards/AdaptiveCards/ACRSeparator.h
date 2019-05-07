//
//  ACRSeparator.h
//  ADCIOSFramework
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "HostConfig.h"
#import "SharedAdaptiveCard.h"
#import "ACRContentStackView.h"
#import "ACRIContentHoldingView.h"

@interface ACRSeparator:UIView

+ (ACRSeparator *)renderSeparation:(std::shared_ptr<AdaptiveCards::BaseCardElement> const &) elem
                      forSuperview:(UIView *) view
                    withHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &) config;

+ (void)renderActionsSeparator:(UIView *)view
                    hostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &)config;

+ (void)renderSeparationWithFrame:(CGRect)frame
                                  superview:(UIView<ACRIContentHoldingView> *)superview
                                       axis:(UILayoutConstraintAxis)huggingAxis;

- (NSLayoutConstraint *)configAutoLayout:(UIView *)superview
                              havingAxis:(UILayoutConstraintAxis)superviewAxis
                                  toAxis:(UILayoutConstraintAxis)huggingAxis;

@end
