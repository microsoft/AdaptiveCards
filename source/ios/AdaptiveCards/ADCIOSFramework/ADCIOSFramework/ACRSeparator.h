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

@interface ACRSeparator:UIView

+ (void)renderSeparation:(std::shared_ptr<AdaptiveCards::BaseCardElement> const &) elem
             forSuperview:(UIView *) view
           withHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &) config;

- (instancetype)initWithFrame:(CGRect)frame 
                withSuperview:(ACRContentStackView *)superview
                       toAxis:(UILayoutConstraintAxis)huggingAxis;

- (NSLayoutConstraint *)configAutoLayout:(UIView *)superview
                              havingAxis:(UILayoutConstraintAxis)superviewAxis
                                  toAxis:(UILayoutConstraintAxis)huggingAxis;

@end
