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
    return [self init:nil config:nil];
}

- (instancetype)init:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig
{
    self = [super init];
    if (self) {
        if (!acoElem or !acoConfig) {
            self.contentSize = CGSizeZero;
            self.acrImageSize = ACRImageSizeAuto;
            self.acrHorizontalAlignment = ACRLeft;
        } else {
            std::shared_ptr<BaseCardElement> elem = [acoElem element];
            std::shared_ptr<Image> imgElem = std::dynamic_pointer_cast<Image>(elem);

            self.pixelWidth = imgElem->GetPixelWidth();
            self.pixelHeight = imgElem->GetPixelHeight();
            self.hasExplicitDimensions = (self.pixelWidth || self.pixelHeight);
            self.isAspectRatioNeeded = !(self.pixelWidth && self.pixelHeight);

            ACRImageSize acrImageSize = getACRImageSize(imgElem->GetImageSize(), self.hasExplicitDimensions);
            if (acrImageSize == ACRImageSizeNone) {
                acrImageSize = ACRImageSizeAuto;
            }

            self.acrImageSize = acrImageSize;
            self.contentSize = [acoConfig getImageSizeAsCGSize:acrImageSize width:self.pixelWidth height:self.pixelHeight];
            self.acrHorizontalAlignment = getACRHorizontalAlignment(imgElem->GetHorizontalAlignment());
        }
    }
    return self;
}

- (void)updateContentSize:(CGSize)size
{
    CGSize ratios = getAspectRatio(size);
    CGFloat heightToWidthRatio = ratios.height;
    CGFloat widthToHeightRatio = ratios.width;

    CGSize newSize = self.contentSize;
    if (self.hasExplicitDimensions) {
        if (self.pixelWidth) {
            newSize.width = self.pixelWidth;
            if (self.isAspectRatioNeeded) {
                newSize.height = self.contentSize.width * heightToWidthRatio;
            }
        }
        if (self.pixelHeight) {
            newSize.height = self.pixelHeight;
            if (self.isAspectRatioNeeded) {
                newSize.width = self.pixelHeight * widthToHeightRatio;
            }
        }
        self.contentSize = newSize;
    }
}
@end
