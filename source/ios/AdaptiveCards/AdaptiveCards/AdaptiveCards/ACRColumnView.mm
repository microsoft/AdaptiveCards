//
//  ACRColumnView
//  ACRColumnView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnView.h"

@implementation ACRColumnView

- (void)config:(nullable NSDictionary<NSString *, id> *)attributes
{
    self.axis = UILayoutConstraintAxisVertical;
    [super config:attributes];
    self.isLastColumn = NO;
}

- (void)addArrangedSubview:(UIView *)view
{
    // if auto, maintain content size whenever possible
    if ([self.columnWidth isEqualToString:@"auto"]) {

        NSInteger priority = ACRColumnWidthPriorityAuto;
        if (self.isLastColumn) {
            priority = ACRColumnWidthPriorityStretchAuto;
        }

        [view setContentHuggingPriority:priority forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
        // if columnWidth is set to stretch or number, allow column to fill the available space
    } else if ([self.columnWidth isEqualToString:@"stretch"]) {
        [view setContentHuggingPriority:ACRColumnWidthPriorityStretch forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
    } else {
        [view setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
    }

    [super addArrangedSubview:view];

    [self increaseIntrinsicContentSize:view];
}

- (void)increaseIntrinsicContentSize:(UIView *)view
{
    if (view.isHidden) {
        return;
    }
    CGSize size = [view intrinsicContentSize];
    if (size.width >= 0 and size.height >= 0) {
        self.combinedContentSize = CGSizeMake(MAX(self.combinedContentSize.width, size.width), self.combinedContentSize.height + size.height);
    }
}

- (void)decreaseIntrinsicContentSize:(UIView *)view
{
    CGFloat nextMax = [self getNextGreatWidth:view];
    CGSize size = [view intrinsicContentSize];
    CGFloat newWidth = (nextMax < size.width) ? nextMax : self.combinedContentSize.width;
    self.combinedContentSize = CGSizeMake(newWidth, self.combinedContentSize.height - size.height);
}

- (UIView *)addPaddingSpace
{
    UIView *blankTrailingSpace = [[UIView alloc] init];
    [blankTrailingSpace setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
    [self addArrangedSubview:blankTrailingSpace];
    return blankTrailingSpace;
}

@end
