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
        if(tag == eACRUILabelTag) {
            UIView *textView = [self viewWithTag:eACRUILabelTag];
            CGSize size = [textView intrinsicContentSize];
            return size;
        } else if (tag == eACRUIImageTag) {
            UIView *ImageView = [self viewWithTag:eACRUIImageTag];
            if(ImageView) {
                CGSize size = [ImageView intrinsicContentSize];
                return size;
            }
        }
    }
    return self.frame.size;
}

- (void)layoutSubviews
{
    [super layoutSubviews];
}

@end
