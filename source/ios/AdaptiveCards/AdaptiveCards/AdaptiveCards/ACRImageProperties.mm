//
//  ACRImageProperties
//  ACRImageProperties.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//
#import "ACRImageProperties.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "Enums.h"
#import "Image.h"
#import "SharedAdaptiveCard.h"
#import "UtiliOS.h"
#import <Foundation/Foundation.h>

@implementation ACRImageProperties

- (instancetype)init
{
    return [self init:nil config:nil image:nil];
}

- (instancetype)init:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image
{
    self = [super init];
    if (self) {
        if (!acoElem or !acoConfig) {
            self.contentSize = CGSizeZero;
            self.acrImageSize = ACRImageSizeAuto;
            self.height = ACRHeightAuto;
            self.acrHorizontalAlignment = ACRLeft;
        } else {
            std::shared_ptr<BaseCardElement> elem = [acoElem element];
            std::shared_ptr<Image> imgElem = std::dynamic_pointer_cast<Image>(elem);

            self.pixelWidth = imgElem->GetPixelWidth();
            self.pixelHeight = imgElem->GetPixelHeight();
            self.hasExplicitDimensions = (self.pixelWidth || self.pixelHeight);
            self.isAspectRatioNeeded = self.hasExplicitDimensions && !(self.pixelWidth && self.pixelHeight);

            ACRImageSize acrImageSize = getACRImageSize(imgElem->GetImageSize(), self.hasExplicitDimensions);
            if (acrImageSize == ACRImageSizeNone) {
                acrImageSize = ACRImageSizeAuto;
            }

            self.acrImageSize = acrImageSize;
            self.contentSize = [acoConfig getImageSizeAsCGSize:acrImageSize width:self.pixelWidth height:self.pixelHeight];

            if (image) {
                [self updateContentSize:image.size];
            }

            self.acrHorizontalAlignment = getACRHorizontalAlignment(imgElem->GetHorizontalAlignment().value_or(HorizontalAlignment::Left));
            self.height = GetACRHeight(imgElem->GetHeight());
        }
    }
    return self;
}

- (void)updateContentSize:(CGSize)size
{
    ACRAspectRatio ratios = [ACRImageProperties convertToAspectRatio:size];

    CGFloat heightToWidthRatio = ratios.heightToWidth;
    CGFloat widthToHeightRatio = ratios.widthToHeight;
    CGSize newSize = self.contentSize;

    CGFloat (^newHeight)(CGFloat) = ^(CGFloat width) {
        return width * heightToWidthRatio;
    };

    CGFloat (^newWidth)(CGFloat) = ^(CGFloat height) {
        return height * widthToHeightRatio;
    };

    if (self.hasExplicitDimensions) {
        if (self.pixelWidth) {
            newSize.width = self.pixelWidth;
            if (!self.pixelHeight) {
                newSize.height = newHeight(self.pixelWidth);
            }
        }

        if (self.pixelHeight) {
            newSize.height = self.pixelHeight;
            if (!self.pixelWidth) {
                newSize.width = newWidth(self.pixelHeight);
            }
        }
        self.contentSize = newSize;
    } else if (self.acrImageSize == ACRImageSizeAuto || self.acrImageSize == ACRImageSizeStretch) {
        self.contentSize = size;
    } else if (self.acrImageSize == ACRImageSizeSmall || self.acrImageSize == ACRImageSizeMedium ||
               self.acrImageSize == ACRImageSizeLarge) {
        newSize = self.contentSize;
        newSize.height = newHeight(self.contentSize.width);
        self.contentSize = newSize;
    }
}

+ (ACRAspectRatio)convertToAspectRatio:(CGSize)cgsize
{
    if (cgsize.width == 0) {
        return {.widthToHeight = 1.0f, .heightToWidth = 1.0f};
    }
    // keeping all precisions are not necessary, and 744W X 84H and its multiples cause a crash.
    // rounding off to 100th points.
    // To make the constraints work, the rounded value has to become 1 when the two ratios are multiplied
    const CGFloat precision = 100;
    // MAX is necessary to prevent heightByWidth becoming zero.
    ACRAspectRatio aspectRatio;
    aspectRatio.heightToWidth = MAX(round(precision * (cgsize.height / cgsize.width)) / precision, 1 / precision);
    aspectRatio.widthToHeight = 1 / aspectRatio.heightToWidth;
    return aspectRatio;
}

@end
