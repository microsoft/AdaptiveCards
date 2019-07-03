//
//  ACRUIImageView.m
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRUIImageView.h"
#import "ACRContentHoldingUIView.h"

@implementation ACRUIImageView

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    if (self) {
        self.tag = eACRUIImageTag;
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.tag = eACRUIImageTag;
        self.desiredSize = frame.size;
    }
    return self;
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    if (_isPersonStyle) {
        CGFloat radius = self.bounds.size.width / 2.0;
        [self.layer setCornerRadius:radius];
        [self.layer setMasksToBounds:YES];
    }
}

- (CGSize)intrinsicContentSize
{
    return self.desiredSize;
}

@end
