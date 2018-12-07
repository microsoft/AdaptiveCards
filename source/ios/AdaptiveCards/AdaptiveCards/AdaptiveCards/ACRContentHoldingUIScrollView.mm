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
    return self.frame.size;
}

- (CGSize)contentSize
{
    CGSize contentsize = [self.subviews[0] intrinsicContentSize];
    return contentsize;
}

@end
