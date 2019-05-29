//
//  ACRContentStackView
//  ACRContentStackView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRIContentHoldingView.h"

@interface ACRContentStackView:UIView<ACRIContentHoldingView>

@property (nonnull) UIStackView* stackView;
@property (weak, nullable) UIView *backgroundView;
@property (nonnull) NSArray<NSLayoutConstraint *>* widthconstraint;
@property (nonnull) NSArray<NSLayoutConstraint *>* heightconstraint;

@property BOOL isActionSet;

- (instancetype _Nonnull)initWithFrame:(CGRect)frame;

- (instancetype _Nonnull)initWithFrame:(CGRect)frame attributes:(nullable NSDictionary<NSString *, id> *)attributes;

- (void)addArrangedSubview:(nonnull UIView *)view;

- (void)config:(nullable NSDictionary<NSString *, id> *)attributes;

- (void)adjustHuggingForLastElement;

- (void)addTarget:(nonnull NSObject *)target;

- (void)applyPadding:(unsigned int)padding priority:(unsigned int)priority;

- (void)bleed:(unsigned int)padding priority:(unsigned int)priority target:(UIView *)target direction:(ACRBleedDirection)direction parentView:(UIView *)parent;

@end
