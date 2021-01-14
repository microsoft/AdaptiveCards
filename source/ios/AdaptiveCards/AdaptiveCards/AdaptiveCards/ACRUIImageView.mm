//
//  ACRUIImageView.m
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRUIImageView.h"
#import "ACRContentHoldingUIView.h"
#import "UtiliOS.h"

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

/*
- (void)layoutSubviews
{
    [super layoutSubviews];
    CGSize superviewFrameSize = self.superview.frame.size;
    CGFloat width = self.frame.size.width;
    CGFloat height = self.frame.size.height;
    if (superviewFrameSize.width < self.desiredSize.width) {
        if (self.adaptiveImageSize == ACRImageSizeLarge || self.adaptiveImageSize == ACRImageSizeMedium || self.adaptiveImageSize == ACRImageSizeSmall || self.adaptiveImageSize == ACRImageSizeAuto) {

            CGSize ratios = getAspectRatio(self.desiredSize);
            height = width * ratios.height;
            width = superviewFrameSize.width;
            self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, width, height);
            self.desiredSize = self.frame.size;
        }

    } else if (self.adaptiveImageSize == ACRImageSizeStretch and (superviewFrameSize.width < self.image.size.width)) {
        CGSize ratios = getAspectRatio(self.image.size);
        height = width * ratios.height;
        width = superviewFrameSize.width;
        self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, width, height);
        self.desiredSize = self.frame.size;
    }
}

- (CGSize)intrinsicContentSize
{
    if (self.desiredSize.width == 0 or self.desiredSize.height == 0) {
        return [super intrinsicContentSize];
    }
    return self.desiredSize;
}
*/

@end
