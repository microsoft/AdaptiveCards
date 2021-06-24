//
//  ACRContentStackView
//  ACRContentStackView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRIContentHoldingView.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"
#import <UIKit/UIKit.h>

@interface ACRContentStackView : UIView <ACRIContentHoldingView>

@property (weak, nullable) UIView *backgroundView;
@property (nonnull) NSArray<NSLayoutConstraint *> *widthconstraint;
@property (nonnull) NSArray<NSLayoutConstraint *> *heightconstraint;
@property CGSize combinedContentSize;
@property UILayoutConstraintAxis axis;
@property UIStackViewDistribution distribution;
@property UIStackViewAlignment alignment;
@property (weak, nullable) NSObject<ACRSelectActionDelegate> *selectActionTarget;
@property BOOL isActionSet;
// tells if a background image is set
@property BOOL isBackgroundImageSet;
// if true, RTL's set
@property ACRRtl rtl;

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

- (UIView *_Nullable)getLastArrangedSubview;

- (NSArray<UIView *> *)getArrangedSubviews;

// return the largest width from the given subviews Excluding the view
- (CGFloat)getMaxWidthOfSubviewsAfterExcluding:(UIView *_Nonnull)view;

// return the largest height from the given subviews Excluding the view
- (CGFloat)getMaxHeightOfSubviewsAfterExcluding:(UIView *_Nonnull)view;

- (void)increaseIntrinsicContentSize:(UIView *_Nonnull)view;

- (void)decreaseIntrinsicContentSize:(UIView *_Nonnull)view;

- (CGSize)getIntrinsicContentSizeInArragedSubviews:(UIView *_Nonnull)view;

- (void)updateIntrinsicContentSize;

- (void)updateIntrinsicContentSize:(void (^_Nonnull)(UIView * _Nonnull view, NSUInteger idx, BOOL * _Nonnull stop))block;

- (void)hideIfSubviewsAreAllHidden;

- (void)bleed:(unsigned int)padding priority:(unsigned int)priority target:(UIView *_Nonnull)target direction:(ACRBleedDirection)direction parentView:(UIView *_Nullable)parent;

- (void)removeViewFromContentStackView:(UIView *_Nonnull)view;

- (UIView *_Nonnull)addPaddingSpace;

@end
