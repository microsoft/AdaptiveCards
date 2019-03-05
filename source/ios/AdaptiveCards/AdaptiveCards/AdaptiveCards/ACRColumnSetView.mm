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
    super.alignment    = UIStackViewAlignmentLeading;
    [super config:attributes];
}

- (void)addArrangedSubview:(UIView* )view
{
    [super addArrangedSubview:view];
}

- (void)adjustHuggingForLastElement
{
    if([super.arrangedSubviews count]) {
        [[super.arrangedSubviews objectAtIndex:[super.arrangedSubviews count ] - 1] setContentHuggingPriority:UILayoutPriorityFittingSizeLevel forAxis:UILayoutConstraintAxisHorizontal];
    }
}

- (void)setAlignmentForColumnStretch
{
    super.alignment = UIStackViewAlignmentFill;
}

@end
