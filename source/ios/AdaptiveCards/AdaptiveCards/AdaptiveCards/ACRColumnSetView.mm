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
    super.stackView.axis = UILayoutConstraintAxisHorizontal;
    super.stackView.distribution = UIStackViewDistributionFill;
    super.stackView.alignment    = UIStackViewAlignmentLeading;
    [super config:attributes];
    self.isLastColumn = NO;
}

- (void)addArrangedSubview:(UIView *)view
{
    [super addArrangedSubview:view];
}

- (void)adjustHuggingForLastElement
{
    if([super.stackView.arrangedSubviews count])
        [[super.stackView.arrangedSubviews objectAtIndex:[super.stackView.arrangedSubviews count ] - 1] setContentHuggingPriority:UILayoutPriorityFittingSizeLevel forAxis:UILayoutConstraintAxisHorizontal];
}

- (void)setAlignmentForColumnStretch
{
    super.stackView.alignment = UIStackViewAlignmentFill;
}

@end
