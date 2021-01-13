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

- (void)layoutSubviews
{
    [super layoutSubviews];
    CGSize superviewFrameSize = self.superview.frame.size;
    CGFloat width = self.frame.size.width;
    CGFloat height = self.frame.size.height;
    if (superviewFrameSize.width < self.desiredSize.width) {
        if (self.adaptiveImageSize == ACRImageSizeLarge || self.adaptiveImageSize == ACRImageSizeMedium || self.adaptiveImageSize == ACRImageSizeSmall) {
            
            CGSize ratios = getAspectRatio(self.desiredSize);
            height = width * ratios.height;
            width  = superviewFrameSize.width;
            self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, width, height);
            self.desiredSize = self.frame.size;
        }
        
    } else if (self.adaptiveImageSize == ACRImageSizeStretch and (superviewFrameSize.width < self.image.size.width)){
        CGSize ratios = getAspectRatio(self.image.size);
        height = width * ratios.height;
        width  = superviewFrameSize.width;
        self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, width, height);
        self.desiredSize = self.frame.size;
        
    } else if (!self.image and self.adaptiveImageSize != ACRImageSizeStretch and superviewFrameSize.width > self.desiredSize.width and self.desiredSize.width != 0) {
        UIGraphicsImageRenderer *renderer = [[UIGraphicsImageRenderer alloc] initWithSize:self.desiredSize];
        UIImage *image = [renderer imageWithActions:^(UIGraphicsImageRendererContext*_Nonnull context) {
            [self drawRect:(CGRect) {.origin = CGPointZero, .size = self.desiredSize}];
        }];
        
        self.image = image;
    }
//
//    if (_isPersonStyle) {
//        CGFloat radius = self.bounds.size.width / 2.0;
//        [self.layer setCornerRadius:radius];
//        [self.layer setMasksToBounds:YES];
//    }
}

- (CGSize)intrinsicContentSize
{
    return self.desiredSize;
}

@end
