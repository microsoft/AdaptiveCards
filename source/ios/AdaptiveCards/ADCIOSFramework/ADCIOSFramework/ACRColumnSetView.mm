//
//  ACRColumnSetView
//  ACRColumnSetView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnSetView.h"

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
    CGRect frame = super.frame;
    frame.size.height = MAX(super.frame.size.height, contentSz.height);
    frame.size.width += contentSz.width;
    super.frame = frame;
    NSLog(@"columset frame size w = %f, h = %f", super.frame.size.width, super.frame.size.height);
}

@end
