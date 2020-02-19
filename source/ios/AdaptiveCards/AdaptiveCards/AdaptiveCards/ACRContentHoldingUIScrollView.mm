//
//  ACRContentHoldingUIScrollView
//  ACRContentHoldingUIScrollView.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRContentHoldingUIScrollView.h"

@implementation ACRContentHoldingUIScrollView

- (CGSize)intrinsicContentSize
{
    return self.contentSize;
}

- (void)layoutSubviews
{
    CGSize superviewSize = self.superview.frame.size;
    CGSize selfsize = [self intrinsicContentSize];
    if (superviewSize.width < selfsize.width && ([self.subviews count] > 0)) {
        self.showsHorizontalScrollIndicator = YES;
        self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, superviewSize.width, selfsize.height);
        self.subviews[0].frame = self.frame;
    }
    [super layoutSubviews];
}

@end
