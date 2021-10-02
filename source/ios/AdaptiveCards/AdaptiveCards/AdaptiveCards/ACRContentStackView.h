//
//  ACRContentStackView
//  ACRContentStackView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOVisibilityManager.h"
#import "ACRIContentHoldingView.h"
#import "ACRTapGestureRecognizerEventHandler.h"
#import <UIKit/UIKit.h>

@interface ACRContentStackView : UIView <ACRIContentHoldingView, ACOIVisibilityManagerFacade> {
  @protected
    UIStackView *_stackView;
    ACOFillerSpaceManager *_paddingHandler;
    NSMutableArray<UIView *> *_paddings;
    ACOVisibilityManager *_visibilityManager;
}

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
// there are some subviews that can be stretched
// it indicates that additional filler views are not needed.
@property (nonatomic) BOOL hasStretchableView;

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

- (NSArray<UIView *> *_Nonnull)getArrangedSubviews;

- (NSArray<UIView *> *_Nonnull)getContentStackSubviews;

// return the largest width from the given subviews Excluding the view
- (CGFloat)getMaxWidthOfSubviewsAfterExcluding:(UIView *_Nonnull)view;

// return the largest height from the given subviews Excluding the view
- (CGFloat)getMaxHeightOfSubviewsAfterExcluding:(UIView *_Nonnull)view;

- (void)increaseIntrinsicContentSize:(UIView *_Nonnull)view;

- (void)decreaseIntrinsicContentSize:(UIView *_Nonnull)view;

- (CGSize)getIntrinsicContentSizeInArragedSubviews:(UIView *_Nonnull)view;

- (void)updateIntrinsicContentSize;

- (void)updateIntrinsicContentSize:(void (^_Nonnull)(UIView *_Nonnull view, NSUInteger idx, BOOL *_Nonnull stop))block;

- (void)bleed:(unsigned int)padding priority:(unsigned int)priority target:(UIView *_Nonnull)target direction:(ACRBleedDirection)direction parentView:(UIView *_Nullable)parent;

- (void)removeViewFromContentStackView:(UIView *_Nonnull)view;

- (UIView *_Nonnull)addPaddingSpace;

/// call this method once all subviews are rendered
/// this methods add padding to itself for alignment and stretch
/// apply visibility to subviews
/// configure min height
/// then activate all contraints associated with the configuration.
/// activation constraint all at once is more efficient than activating
/// constraints one by one.
- (void)configureLayoutAndVisibility:(ACRVerticalContentAlignment)verticalContentAlignment
                           minHeight:(NSInteger)minHeight
                          heightType:(ACRHeightType)heightType
                                type:(ACRCardElementType)type;

/// call this method when visibility of subviews has chaned and
/// padding needs to be updated
- (void)updatePaddingVisibility;

/// this method applies visibility to subviews once all of them are rendered and become part of content stack view
/// applying visibility as each subview is rendered has known side effects.
/// such as its superview, content stack view becomes hidden if a first subview is set hidden.
- (void)applyVisibilityToSubviews;

@end
