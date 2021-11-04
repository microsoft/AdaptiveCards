//
//  ACRColumnView
//  ACRColumnView.mm
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACOBaseCardElementPrivate.h"
#import "ACOFillerSpaceManager.h"
#import "ACRView.h"

@implementation ACRColumnView

- (void)setColumnWidth:(NSString *)columnWidth
{
    _columnWidth = columnWidth;
}

- (void)config:(nullable NSDictionary<NSString *, id> *)attributes
{
    self.axis = UILayoutConstraintAxisVertical;
    [super config:attributes];
    self.isLastColumn = NO;
    self.inputHandlers = [[NSMutableArray<ACRIBaseInputHandler> alloc] init];
}
- (void)addArrangedSubview:(UIView *)view
{
    [self configureWidthOfView:view];

    [super addArrangedSubview:view];

    [self increaseIntrinsicContentSize:view];
}

- (void)insertArrangedSubview:(UIView *)view atIndex:(NSUInteger)insertionIndex
{
    [self configureWidthOfView:view];

    [super insertArrangedSubview:view atIndex:insertionIndex];

    [self increaseIntrinsicContentSize:view];
}

- (void)configureWidthOfView:(UIView *)view
{
    // if auto, maintain content size whenever possible
    if ([self.columnWidth isEqualToString:@"auto"]) {

        NSInteger priority = ACRColumnWidthPriorityAuto;
        if (self.isLastColumn) {
            priority = ACRColumnWidthPriorityStretchAuto;
        }

        [view setContentHuggingPriority:priority forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentHuggingPriority:priority forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
        // if columnWidth is set to stretch or number, allow column to fill the available space
    } else if ([self.columnWidth isEqualToString:@"stretch"] || (!self.hasMoreThanOneRelativeWidth && self.relativeWidth)) {
        [view setContentHuggingPriority:ACRColumnWidthPriorityStretch forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentHuggingPriority:ACRColumnWidthPriorityStretch forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
    } else {
        [view setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
    }
}

- (void)increaseIntrinsicContentSize:(UIView *)view
{
    if (view.isHidden) {
        return;
    }
    [super increaseIntrinsicContentSize:view];
    CGSize size = [view intrinsicContentSize];

    if (size.width >= 0 and size.height >= 0) {
        self.combinedContentSize = CGSizeMake(MAX(self.combinedContentSize.width, size.width), self.combinedContentSize.height + size.height);
    }
}

- (void)decreaseIntrinsicContentSize:(UIView *)view
{
    CGFloat maxWidthExcludingTheView = [self getMaxWidthOfSubviewsAfterExcluding:view];
    CGSize size = [self getIntrinsicContentSizeInArragedSubviews:view];
    // there are three possible cases
    // 1. possibleMaxWidthExcludingTheView is equal to the height of the view
    // 2. possibleMaxWidthExcludingTheView is bigger than the the height of the view
    // 3. possibleMaxWidthExcludingTheView is smaller than the the height of the view
    // only #3 changes the current height, when the view's height is no longer in considreation
    // for dimension
    CGFloat newWidth = (maxWidthExcludingTheView < size.width) ? maxWidthExcludingTheView : self.combinedContentSize.width;
    self.combinedContentSize = CGSizeMake(newWidth, self.combinedContentSize.height - size.height);
}

- (void)updateIntrinsicContentSize
{
    self.combinedContentSize = CGSizeZero;
    [super updateIntrinsicContentSize:^(UIView *view, NSUInteger idx, BOOL *stop) {
        CGSize size = [view intrinsicContentSize];
        if (!view.hidden) {
            if (size.width >= 0 and size.height >= 0) {
                self.combinedContentSize = CGSizeMake(MAX(self.combinedContentSize.width, size.width), self.combinedContentSize.height + size.height);
            }
        }
    }];
}

@end
