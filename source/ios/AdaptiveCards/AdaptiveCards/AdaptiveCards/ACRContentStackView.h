//
//  ACRContentStackView
//  ACRContentStackView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRIContentHoldingView.h"
#import <UIKit/UIKit.h>

@interface ACRContentStackView : UIView <ACRIContentHoldingView>

@property (weak, nullable) UIView *backgroundView;
@property (nonnull) NSArray<NSLayoutConstraint *> *widthconstraint;
@property (nonnull) NSArray<NSLayoutConstraint *> *heightconstraint;
@property CGSize combinedContentSize;
@property UILayoutConstraintAxis axis;
@property UIStackViewDistribution distribution;
@property UIStackViewAlignment alignment;

@property BOOL isActionSet;

- (instancetype _Nonnull)initWithFrame:(CGRect)frame;

- (instancetype _Nonnull)initWithFrame:(CGRect)frame attributes:(nullable NSDictionary<NSString *, id> *)attributes;

- (void)addArrangedSubview:(nonnull UIView *)view;

- (void)config:(nullable NSDictionary<NSString *, id> *)attributes;

- (void)adjustHuggingForLastElement;

- (void)addTarget:(nonnull NSObject *)target;

- (void)applyPadding:(unsigned int)padding priority:(unsigned int)priority;

- (void)applyPaddingToTop:(CGFloat)top left:(CGFloat)left
                   bottom:(CGFloat)bottom
                    right:(CGFloat)right
                 priority:(unsigned int)priority
                 location:(ACRBleedDirection)location;

- (UIView *)getLastArrangedSubview;

- (CGFloat)getNextGreatWidth:(UIView *)view;

- (CGFloat)getNextGreatHeight:(UIView *)view;

- (void)increaseIntrinsicContentSize:(UIView *)view;

- (void)decreaseIntrinsicContentSize:(UIView *)view;

- (void)hideIfSubviewsAreAllHidden;

- (void)bleed:(unsigned int)padding priority:(unsigned int)priority target:(UIView *)target direction:(ACRBleedDirection)direction parentView:(UIView *)parent;

- (void)removeViewFromContentStackView:(UIView *)view;
@end
