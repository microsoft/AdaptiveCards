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
    self.stackView.axis = UILayoutConstraintAxisVertical;
    //self.stackView.distribution = UIStackViewDistributionFill;
    //self.stackView.alignment = UIStackViewAlignmentFill;
    [super config:attributes];
}

- (void)addArrangedSubview:(UIView *)view
{
    // if auto, maintain content size whenever possible
    if([self.columnWidth isEqualToString:@"auto"]){
        [view setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
      // if columnWidth is set to stretch or number, allow column to fill the available space
    } else {
        [view setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
    }

    [self.stackView addArrangedSubview:view];
}

- (UIView *)addPaddingSpace
{
    UIView *blankTrailingSpace = [[UIView alloc] init];
    [blankTrailingSpace setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
    [self addArrangedSubview:blankTrailingSpace];
    return blankTrailingSpace;
}
/*
- (CGSize)intrinsicContentSize
{
    CGSize contentSize = CGSizeZero;
    for(UIView *item in self.stackView.subviews){
        CGSize subViewContentSize = [item intrinsicContentSize];
        contentSize.width = MAX(contentSize.width, subViewContentSize.width);
        contentSize.height += subViewContentSize.height;
    }
    return contentSize;
}
*/
@end
