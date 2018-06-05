//
//  ACRUIImageView.m
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRUIImageView.h"

@implementation ACRUIImageView

-(void)layoutSubviews
{
    [super layoutSubviews];
    CGFloat radius = self.bounds.size.width / 2.0;
    [self.layer setCornerRadius:radius];
}

@end
