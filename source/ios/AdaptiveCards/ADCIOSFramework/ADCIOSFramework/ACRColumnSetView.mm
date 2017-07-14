//
//  ACRColumnSetView
//  ACRColumnSetView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#include "ACRColumnSetView.h"

@implementation ACRColumnSetView

-(void)config
{
    [super config];
    super.stackView.axis = UILayoutConstraintAxisHorizontal;
    super.stackView.distribution = UIStackViewDistributionFillProportionally;
}

- (void)addArrangedSubview:(UIView *) view
{
    CGSize contentSz = [view systemLayoutSizeFittingSize:UILayoutFittingCompressedSize];
    [super addArrangedSubview: view];
    CGSize sz = super.frame.size;
    sz.width += contentSz.width;
    super.frame.size = sz;
}

@end
