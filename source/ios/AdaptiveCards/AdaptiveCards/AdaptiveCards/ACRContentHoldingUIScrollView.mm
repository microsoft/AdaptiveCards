//
//  ACRContentHoldingUIScrollView
//  ACRContentHoldingUIScrollView.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRContentHoldingUIScrollView.h"

@implementation ACRContentHoldingUIScrollView

- (CGSize)intrinsicContentSize {
    return [super intrinsicContentSize];
}

- (void)layoutSubviews {
    [super layoutSubviews];

    if (self.contentview && self.frame.size.width > self.contentWidth && self.stretch) {
        [self.contentview.widthAnchor constraintEqualToAnchor:self.widthAnchor multiplier:1.0]
            .active = YES;
        [self.contentview setNeedsUpdateConstraints];
    }
}

@end
