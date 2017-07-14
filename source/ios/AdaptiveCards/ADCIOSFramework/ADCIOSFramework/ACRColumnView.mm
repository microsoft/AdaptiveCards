//
//  ACRColumnView
//  ACRColumnView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#include "ACRColumnView.h"

@implementation ACRColumnView

-(void)config
{
    [super config];
    super.stackView.axis = UILayoutConstraintAxisVertical;
}

- (void)addArrangedSubview:(UIView *) view
{
    CGSize contentSz = [view systemLayoutSizeFittingSize:UILayoutFittingCompressedSize];
    [super addArrangedSubview: view];
    super.frame.size = [super.stackView systemLayoutSizeFittingSize:UILayoutFittingCompressedSize];
    CGSize sz = super.frame.size;
    sz.width = MAX(super.frame.size.width, contentSz.width);
    super.frame.size = sz;
}

@end
