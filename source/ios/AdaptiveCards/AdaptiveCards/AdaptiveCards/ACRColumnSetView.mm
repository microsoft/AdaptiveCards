//
//  ACRColumnSetView
//  ACRColumnSetView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnSetView.h"

@implementation ACRColumnSetView

- (void)config:(nullable NSDictionary<NSString *, id> *)attributes
{
    super.axis = UILayoutConstraintAxisHorizontal;
    super.distribution = UIStackViewDistributionFill;
    super.alignment = UIStackViewAlignmentLeading;
    [super config:attributes];
    self.isLastColumn = NO;
}

- (void)addArrangedSubview:(UIView *)view
{
    [super addArrangedSubview:view];
    [self increaseIntrinsicContentSize:view];
}

- (void)increaseIntrinsicContentSize:(UIView *)view
{
    if (!view.isHidden) {
        CGSize size = [view intrinsicContentSize];
        if (size.width >= 0 and size.height >= 0) {
            CGSize combinedSize = CGSizeMake(self.combinedContentSize.width + size.width, MAX(self.combinedContentSize.height, size.height));
            self.combinedContentSize = combinedSize;
        }
    }
}

- (void)decreaseIntrinsicContentSize:(UIView *)view
{
    CGFloat nextMax = [self getNextGreatHeight:view];
    CGSize size = [view intrinsicContentSize];
    CGFloat newHeight = (nextMax < size.height) ? nextMax : self.combinedContentSize.height;
    self.combinedContentSize = CGSizeMake(self.combinedContentSize.width - size.width, newHeight);
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

@end
