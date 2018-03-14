//
//  ACRIContentHoldingView
//  ACRIContentHoldingView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACOBaseCardElement.h"
#import "ACOHostConfig.h"
@protocol ACRIContentHoldingView

- (instancetype)initWithStyle:(ACRContainerStyle)style
                  parentStyle:(ACRContainerStyle)parentStyle 
                   hostConfig:(ACOHostConfig *)config;
- (void)addArrangedSubview:(UIView *)view;
- (UILayoutConstraintAxis)getAxis;
- (void)addTarget:(NSObject *)target;
- (void)adjustHuggingForLastElement;
- (ACRContainerStyle)style;
- (void)setStyle:(ACRContainerStyle)stye;

@end
