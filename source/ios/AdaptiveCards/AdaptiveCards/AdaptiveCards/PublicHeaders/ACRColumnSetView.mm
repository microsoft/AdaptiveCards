//
//  ACRColumnSetView
//  ACRColumnSetView.mm
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACRColumnSetView.h"

@implementation ACRColumnSetView

- (void)config:(nullable NSDictionary<NSString *, id> *)attributes
{
    super.axis = UILayoutConstraintAxisHorizontal;
    super.distribution = UIStackViewDistributionFill;
    super.alignment = UIStackViewAlignmentFill;
    [super config:attributes];
    self.isLastColumn = NO;
}

- (void)addArrangedSubview:(UIView *)view
{
    [super addArrangedSubview:view];
    [self increaseIntrinsicContentSize:view];
}

// inserts a UIView at insertion index
- (void)insertArrangedSubview:(UIView *)view atIndex:(NSUInteger)insertionIndex
{
    [super insertArrangedSubview:view atIndex:insertionIndex];
    [self increaseIntrinsicContentSize:view];
}

- (void)increaseIntrinsicContentSize:(UIView *)view
{
    if (!view.isHidden) {
        [super increaseIntrinsicContentSize:view];
        CGSize size = [view intrinsicContentSize];
        if (size.width >= 0 && size.height >= 0) {
            CGSize combinedSize = CGSizeMake(self.combinedContentSize.width + size.width, MAX(self.combinedContentSize.height, size.height));
            self.combinedContentSize = combinedSize;
        }
    }
}

- (void)decreaseIntrinsicContentSize:(UIView *)view
{
    // get max height amongst the subviews that is not the view
    CGFloat maxHeightExludingTheView = [self getMaxHeightOfSubviewsAfterExcluding:view];
    CGSize size = [self getIntrinsicContentSizeInArragedSubviews:view];
    // there are three possible cases
    // 1. maxHeightExludingTheView is equal to the height of the view
    // 2. maxHeightExludingTheView is bigger than the the height of the view
    // 3. maxHeightExludingTheView is smaller than the the height of the view
    // only #3 changes the current height, when the view's height is no longer in considreation
    // for dimension
    CGFloat newHeight = (maxHeightExludingTheView < size.height) ? maxHeightExludingTheView : self.combinedContentSize.height;
    self.combinedContentSize = CGSizeMake(self.combinedContentSize.width - size.width, newHeight);
}

- (void)updateIntrinsicContentSize
{
    self.combinedContentSize = CGSizeZero;
    [super updateIntrinsicContentSize:^(UIView *view, NSUInteger idx, BOOL *stop) {
        CGSize size = [view intrinsicContentSize];
        if (size.width >= 0 && size.height >= 0) {
            CGSize combinedSize = CGSizeMake(self.combinedContentSize.width + size.width, MAX(self.combinedContentSize.height, size.height));
            self.combinedContentSize = combinedSize;
        }
    }];
}

- (void)adjustHuggingForLastElement
{
    UIView *view = [self getLastArrangedSubview];
    if (view) {
        [view setContentHuggingPriority:UILayoutPriorityFittingSizeLevel forAxis:UILayoutConstraintAxisHorizontal];
    }
}

- (void)setAlignmentForColumnStretch
{
    super.alignment = UIStackViewAlignmentFill;
}

- (void)configureLayoutAndVisibility:(ACRVerticalContentAlignment)verticalContentAlignment
                           minHeight:(NSInteger)minHeight
                          heightType:(ACRHeightType)heightType
                                type:(ACRCardElementType)type
{
    [super applyVisibilityToSubviews];

    if (minHeight > 0) {
        NSLayoutConstraint *constraint =
            [NSLayoutConstraint constraintWithItem:self
                                         attribute:NSLayoutAttributeHeight
                                         relatedBy:NSLayoutRelationGreaterThanOrEqual
                                            toItem:nil
                                         attribute:NSLayoutAttributeNotAnAttribute
                                        multiplier:1
                                          constant:minHeight];
        constraint.priority = 999;
        constraint.active = YES;
    }
}

@end
