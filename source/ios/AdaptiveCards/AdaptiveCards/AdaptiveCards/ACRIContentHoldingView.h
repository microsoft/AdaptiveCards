//
//  ACRIContentHoldingView
//  ACRIContentHoldingView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOBaseCardElement.h"
#import "ACOHostConfig.h"
#import <UIKit/UIKit.h>
@protocol ACRIContentHoldingView

- (instancetype)initWithStyle:(ACRContainerStyle)style
                  parentStyle:(ACRContainerStyle)parentStyle
                   hostConfig:(ACOHostConfig *)config
                    superview:(UIView<ACRIContentHoldingView> *)superview;
- (void)addArrangedSubview:(UIView *)view;
- (void)removeLastViewFromArrangedSubview;
- (UILayoutConstraintAxis)getAxis;
- (void)addTarget:(NSObject *)target;
- (void)adjustHuggingForLastElement;
- (ACRContainerStyle)style;
- (void)setStyle:(ACRContainerStyle)stye;
- (void)hideAllShowCards;
- (NSUInteger)subviewsCounts;
- (UIView *)getLastSubview;

@end
