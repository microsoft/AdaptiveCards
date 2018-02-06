//
//  ACRIContentHoldingView
//  ACRIContentHoldingView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "Enums.h"
#import "HostConfig.h"
@protocol ACRIContentHoldingView

- (instancetype)initWithStyle:(AdaptiveCards::ContainerStyle)style
                   hostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &)config;
- (void)addArrangedSubview:(UIView *)view;
- (UILayoutConstraintAxis)getAxis;
- (void)addTarget:(NSObject *)target;
- (void)adjustHuggingForLastElement;
- (AdaptiveCards::ContainerStyle)getStyle;

@end
