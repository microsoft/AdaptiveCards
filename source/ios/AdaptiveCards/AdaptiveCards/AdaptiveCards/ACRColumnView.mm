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
    enum Bounds { eMinNumRequired = 2};
    if([self.stackView.arrangedSubviews count] >= eMinNumRequired)
    {
        [self addConstraint:
                [NSLayoutConstraint constraintWithItem:
                 [self.stackView.arrangedSubviews objectAtIndex:[self.stackView.arrangedSubviews count] - eMinNumRequired]
                                             attribute:NSLayoutAttributeBottom
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeTop
                                            multiplier:1
                                              constant:0]];
    }
    
    [self addConstraint:
     [NSLayoutConstraint constraintWithItem:
      self.stackView attribute:NSLayoutAttributeWidth
                      relatedBy:NSLayoutRelationGreaterThanOrEqual
                         toItem:view
                      attribute:NSLayoutAttributeWidth
                     multiplier:1
                       constant:0]];

}

@end
