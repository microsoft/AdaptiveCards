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

- (void)increaseIntrinsicContentSizeBySize:(CGSize)size
{
    if (size.width >= 0 && size.height >= 0) {
        CGSize combinedSize = CGSizeMake(self.combinedContentSize.width + size.width, MAX(self.combinedContentSize.height, size.height));
        self.combinedContentSize = combinedSize;
    }
}

- (void)decreaseIntrinsicContentSize:(UIView *)view
{
    // get max height amongst the subviews that is not the view
    CGFloat maxHeightExludingTheView = [self getMaxHeightOfSubviewsAfterExcluding:view];
    CGSize size = [view intrinsicContentSize];
    // there are three possible cases
    // 1. maxHeightExludingTheView is equal to the height of the view
    // 2. maxHeightExludingTheView is bigger than the the height of the view
    // 3. maxHeightExludingTheView is smaller than the the height of the view
    // only #3 changes the current height, when the view's height is no longer in considreation
    // for dimension
    CGFloat newHeight = (maxHeightExludingTheView < size.height) ? maxHeightExludingTheView : self.combinedContentSize.height;
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
