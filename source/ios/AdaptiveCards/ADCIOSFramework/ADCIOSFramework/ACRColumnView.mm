//
//  ACRColumnView
//  ACRColumnView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnView.h"

@implementation ACRColumnView

-(void)config
{
    [super config];
    super.stackView.axis = UILayoutConstraintAxisVertical;
    super.stackView.distribution = UIStackViewDistributionFill;
}

- (void)addArrangedSubview:(UIView *) view
{
    CGSize contentSz = [view systemLayoutSizeFittingSize:UILayoutFittingCompressedSize];
    [super addArrangedSubview: view];
    super.frame.size = [super.stackView systemLayoutSizeFittingSize:UILayoutFittingCompressedSize];
    CGRect frame = super.frame;
    frame.size.width = MAX(super.frame.size.width, contentSz.width);
    frame.size.height += contentSz.height;
    super.frame = frame;
    NSLog(@"column frame size w = %f, h = %f", super.frame.size.width, super.frame.size.height);
    if([self.stackView.arrangedSubviews count] - 1)
    {
        [self addConstraint: 
                [NSLayoutConstraint constraintWithItem:
                 [self.stackView.arrangedSubviews objectAtIndex:[self.stackView.arrangedSubviews count] - 2]
                                             attribute:NSLayoutAttributeBottom
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeTop
                                            multiplier:1
                                              constant:0]];
    }
}

@end
