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
    UIView *textView = [self viewWithTag:eACRUILabelTag];
    if(textView) {
        CGSize size = [textView intrinsicContentSize];
        return size;
    } else
    {
        return self.frame.size;
    }
}

- (void)layoutSubviews
{
    /*
    if(self.bChanged){
        [self invalidateIntrinsicContentSize];
    }*/
    [super layoutSubviews];
}

@end
