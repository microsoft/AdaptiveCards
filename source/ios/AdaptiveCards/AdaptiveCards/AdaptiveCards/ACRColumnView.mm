//
//  ACRColumnView
//  ACRColumnView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnView.h"

@implementation ACRColumnView

- (void)config
{
    [super config];
    super.stackView.axis = UILayoutConstraintAxisVertical;
    super.stackView.distribution = UIStackViewDistributionFill;
}

- (void)addArrangedSubview:(UIView *)view
{
    [super addArrangedSubview:view];
    CGRect frame = super.frame;
    super.frame = frame;
}

@end
