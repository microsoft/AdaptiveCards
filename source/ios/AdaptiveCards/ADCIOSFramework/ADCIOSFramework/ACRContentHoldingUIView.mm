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

- (NSMutableArray* )setAlignment:(HorizontalAlignment)alignment
                   withSuperview:(UIView* )superview
                          toView:(UIView* )view
{
    NSMutableArray* constraints = [[NSMutableArray alloc] init];
    [constraints addObject:
     [NSLayoutConstraint constraintWithItem:superview
                                  attribute:NSLayoutAttributeCenterY
                                  relatedBy:NSLayoutRelationEqual
                                     toItem:view
                                  attribute:NSLayoutAttributeCenterY
                                 multiplier:1
                                   constant:0]];
    switch (alignment)
    {
        case HorizontalAlignment::Center:
        {
            [constraints addObject:
             [NSLayoutConstraint constraintWithItem:superview
                                          attribute:NSLayoutAttributeCenterX
                                          relatedBy:NSLayoutRelationEqual
                                             toItem:view
                                          attribute:NSLayoutAttributeCenterX
                                         multiplier:1
                                           constant:0]];
            return constraints;
        }
        case HorizontalAlignment::Left:
        {
            [constraints addObject:
             [NSLayoutConstraint constraintWithItem:superview
                                          attribute:NSLayoutAttributeLeading
                                          relatedBy:NSLayoutRelationEqual
                                             toItem:view
                                          attribute:NSLayoutAttributeLeading
                                         multiplier:1
                                           constant:0]];
            return constraints;
        }
        case HorizontalAlignment::Right:
        {
            [constraints addObject:
             [NSLayoutConstraint constraintWithItem:superview
                                          attribute:NSLayoutAttributeTrailing
                                          relatedBy:NSLayoutRelationEqual
                                             toItem:view
                                          attribute:NSLayoutAttributeTrailing
                                         multiplier:1
                                           constant:0]];
            return constraints;
        }
        default:
        {
            [constraints addObject:
             [NSLayoutConstraint constraintWithItem:superview
                                          attribute:NSLayoutAttributeLeading
                                          relatedBy:NSLayoutRelationEqual
                                             toItem:view
                                          attribute:NSLayoutAttributeLeading
                                         multiplier:1
                                           constant:0]];
            return constraints;
        }
    }
    return constraints;
}
@end
