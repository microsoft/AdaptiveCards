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

@interface ACRSeparator:UIView

@property CGFloat dimension_width;
@property CGFloat dimension_height;
@property CGFloat lineWidth;
@property UILayoutConstraintAxis axis;
@property long    rgb;

+ (void) renderSeparation:(std::shared_ptr<AdaptiveCards::BaseCardElement> const &) elem
             ForSuperView:(UIView* ) view
           withHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &) config;

@end
