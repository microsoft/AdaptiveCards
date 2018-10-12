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

@end
