//
//  ACRContentHoldingUIView
//  ACRContentHoldingUIView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRContentHoldingUIView.h"

using namespace AdaptiveCards;

@implementation ACRContentHoldingUIView

- (CGSize)intrinsicContentSize
{
    return self.frame.size;
}

- (void)setAlignmentForSubview:(HorizontalAlignment)alignment
{
    NSMutableArray *constraints = [[NSMutableArray alloc] init];
    [constraints addObject:
     [NSLayoutConstraint constraintWithItem:self
                                  attribute:NSLayoutAttributeCenterY
                                  relatedBy:NSLayoutRelationEqual
                                     toItem:[self.subviews objectAtIndex:0]
                                  attribute:NSLayoutAttributeCenterY
                                 multiplier:1
                                   constant:0]];
    [constraints addObject:
     [NSLayoutConstraint constraintWithItem:[self.subviews objectAtIndex:0]
                                  attribute:NSLayoutAttributeTrailing
                                  relatedBy:NSLayoutRelationLessThanOrEqual
                                     toItem:self
                                  attribute:NSLayoutAttributeTrailing
                                 multiplier:1
                                   constant:0]];
    [constraints addObject:
     [NSLayoutConstraint constraintWithItem:[self.subviews objectAtIndex:0]
                                  attribute:NSLayoutAttributeTop
                                  relatedBy:NSLayoutRelationLessThanOrEqual
                                     toItem:self
                                  attribute:NSLayoutAttributeTop
                                 multiplier:1
                                   constant:0]];
    [constraints addObject:
     [NSLayoutConstraint constraintWithItem:[self.subviews objectAtIndex:0]
                                  attribute:NSLayoutAttributeBottom
                                  relatedBy:NSLayoutRelationLessThanOrEqual
                                     toItem:self
                                  attribute:NSLayoutAttributeBottom
                                 multiplier:1
                                   constant:0]];


    switch (alignment)
    {
        case HorizontalAlignment::Center:
        {
            [constraints addObject:
             [NSLayoutConstraint constraintWithItem:self
                                          attribute:NSLayoutAttributeCenterX
                                          relatedBy:NSLayoutRelationEqual
                                             toItem:[self.subviews objectAtIndex:0]
                                          attribute:NSLayoutAttributeCenterX
                                         multiplier:1
                                           constant:0]];
            break; 
        }
        case HorizontalAlignment::Left:
        {
            [constraints addObject:
             [NSLayoutConstraint constraintWithItem:self
                                          attribute:NSLayoutAttributeLeading
                                          relatedBy:NSLayoutRelationEqual
                                             toItem:[self.subviews objectAtIndex:0]
                                          attribute:NSLayoutAttributeLeading
                                         multiplier:1
                                           constant:0]];
            break; 
        }
        case HorizontalAlignment::Right:
        {
            [constraints addObject:
             [NSLayoutConstraint constraintWithItem:self
                                          attribute:NSLayoutAttributeTrailing
                                          relatedBy:NSLayoutRelationEqual
                                             toItem:[self.subviews objectAtIndex:0]
                                          attribute:NSLayoutAttributeTrailing
                                         multiplier:1
                                           constant:0]];
            break; 
        }
        default:
        {
            [constraints addObject:
             [NSLayoutConstraint constraintWithItem:self
                                          attribute:NSLayoutAttributeLeading
                                          relatedBy:NSLayoutRelationEqual
                                             toItem:[self.subviews objectAtIndex:0]
                                          attribute:NSLayoutAttributeLeading
                                         multiplier:1
                                           constant:0]];
            break; 
        }
    }
    [self addConstraints:constraints];
}
@end
