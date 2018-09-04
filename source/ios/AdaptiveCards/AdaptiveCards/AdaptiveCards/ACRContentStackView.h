//
//  ACRContentStackView
//  ACRContentStackView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRIContentHoldingView.h"

@interface ACRContentStackView:UIView<ACRIContentHoldingView>

@property UIStackView* stackView;

- (instancetype)initWithFrame:(CGRect)frame;

- (void)addArrangedSubview:(UIView *)view;

- (void)config;

- (void)adjustHuggingForLastElement;

- (void)addTarget:(NSObject *)target;
@end
