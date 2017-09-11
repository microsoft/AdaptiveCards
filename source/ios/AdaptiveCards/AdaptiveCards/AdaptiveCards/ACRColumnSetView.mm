//
//  ACRColumnSetView
//  ACRColumnSetView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnSetView.h"

@implementation ACRColumnSetView

- (void)config
{
    [super config];
    super.stackView.axis = UILayoutConstraintAxisHorizontal;
    super.stackView.distribution = UIStackViewDistributionFill;
    super.stackView.alignment    = UIStackViewAlignmentLeading;
}

- (void)addArrangedSubview:(UIView* )view
{
    CGSize contentSz = [view systemLayoutSizeFittingSize:UILayoutFittingCompressedSize];
    [super addArrangedSubview:view];
    CGRect frame = super.frame;
    frame.size.height = MAX(super.frame.size.height, contentSz.height);
    frame.size.width += contentSz.width;
    super.frame = frame;
}

- (void)adjustHuggingForLastElement
{
    if([super.stackView.arrangedSubviews count])
        [[super.stackView.arrangedSubviews objectAtIndex:[super.stackView.arrangedSubviews count ] - 1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
}

@end
