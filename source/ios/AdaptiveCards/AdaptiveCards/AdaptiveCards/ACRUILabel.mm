//
//  ACRUILabel.m
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRUILabel.h"

@implementation ACRUILabel
/*
-(void)drawTextInRect:(CGRect)rect
{
    if (_isFactSetLabel || _isStretchable) {
        CGSize labelStringSize = [self.text boundingRectWithSize:CGSizeMake(self.frame.size.width, CGFLOAT_MAX)
                                                         options:NSStringDrawingUsesLineFragmentOrigin | NSStringDrawingUsesFontLeading
                                                      attributes:@{NSFontAttributeName:self.font}
                                                         context:nil].size;
        [super drawTextInRect:CGRectMake(0, 0, ceilf(self.frame.size.width),ceilf(labelStringSize.height))];
    } else {
        [super drawTextInRect:rect];
    }
}
*/

- (CGSize)intrinsicContentSize
{
    UIView *superview = self.superview;
    CGSize sizeThatFitsTextView = [self sizeThatFits:CGSizeMake(superview.frame.size.width, MAXFLOAT)];
    self.frame = CGRectMake(0, 0, sizeThatFitsTextView.width, sizeThatFitsTextView.height);
    return self.frame.size;
}


@end
