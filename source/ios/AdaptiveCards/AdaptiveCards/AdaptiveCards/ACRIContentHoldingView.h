//
//  ACRIContentHoldingView
//  ACRIContentHoldingView.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
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
- (void)insertArrangedSubview:(UIView *)view atIndex:(NSUInteger)insertionIndex;
- (void)removeLastViewFromArrangedSubview;
- (void)addTarget:(NSObject *)target;
- (void)adjustHuggingForLastElement;
- (ACRContainerStyle)style;
- (void)setStyle:(ACRContainerStyle)stye;
- (void)hideAllShowCards;
- (NSUInteger)subviewsCounts;
- (NSUInteger)arrangedSubviewsCounts;
- (UIView *)getLastSubview;

@end
