//
//  ACRContentHoldingUIView
//  ACRContentHoldingUIView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRContentHoldingUIView.h"
#import "ACRUILabel.h"

using namespace AdaptiveCards;

@implementation ACRContentHoldingUIView

- (CGSize)intrinsicContentSize
{
    if(self.subviews.count) {
        NSInteger tag = self.subviews.firstObject.tag;
        if((tag == eACRUILabelTag) || (tag == eACRUIImageTag)) {
            UIView *view = [self viewWithTag:tag];
            if(view) {
                return [view intrinsicContentSize];
            }
        }
    }
    return self.frame.size;
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    if(_isPersonStyle) {
        UIView *subview = self.subviews[0];
        CGFloat radius = subview.bounds.size.width / 2.0;
        [subview.layer setCornerRadius:radius];
        [subview.layer setMasksToBounds:YES];
    }
}

@end
