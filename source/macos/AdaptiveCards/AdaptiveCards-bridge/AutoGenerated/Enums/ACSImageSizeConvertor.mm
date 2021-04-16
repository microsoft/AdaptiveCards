// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSImageSizeConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSImageSize.h"

@implementation ACSImageSizeConvertor


+(enum ACSImageSize) convertCpp:(AdaptiveCards::ImageSize) imageSizeCpp
{
  switch(imageSizeCpp)
  {
    case AdaptiveCards::ImageSize::None:
      return ACSImageSize::ACSImageSizeNone;
    case AdaptiveCards::ImageSize::Auto:
      return ACSImageSize::ACSImageSizeAuto;
    case AdaptiveCards::ImageSize::Stretch:
      return ACSImageSize::ACSImageSizeStretch;
    case AdaptiveCards::ImageSize::Small:
      return ACSImageSize::ACSImageSizeSmall;
    case AdaptiveCards::ImageSize::Medium:
      return ACSImageSize::ACSImageSizeMedium;
    case AdaptiveCards::ImageSize::Large:
      return ACSImageSize::ACSImageSizeLarge;
  }
}


+(AdaptiveCards::ImageSize) convertObj:(enum ACSImageSize) imageSizeObjc
{
  switch(imageSizeObjc)
  {
    case ACSImageSize::ACSImageSizeNone:
      return AdaptiveCards::ImageSize::None;
    case ACSImageSize::ACSImageSizeAuto:
      return AdaptiveCards::ImageSize::Auto;
    case ACSImageSize::ACSImageSizeStretch:
      return AdaptiveCards::ImageSize::Stretch;
    case ACSImageSize::ACSImageSizeSmall:
      return AdaptiveCards::ImageSize::Small;
    case ACSImageSize::ACSImageSizeMedium:
      return AdaptiveCards::ImageSize::Medium;
    case ACSImageSize::ACSImageSizeLarge:
      return AdaptiveCards::ImageSize::Large;
  }
}

@end
