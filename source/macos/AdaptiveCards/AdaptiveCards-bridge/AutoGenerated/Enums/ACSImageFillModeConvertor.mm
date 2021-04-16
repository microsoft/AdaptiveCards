// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSImageFillModeConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSImageFillMode.h"

@implementation ACSImageFillModeConvertor


+(enum ACSImageFillMode) convertCpp:(AdaptiveCards::ImageFillMode) imageFillModeCpp
{
  switch(imageFillModeCpp)
  {
    case AdaptiveCards::ImageFillMode::Cover:
      return ACSImageFillMode::ACSImageFillModeCover;
    case AdaptiveCards::ImageFillMode::RepeatHorizontally:
      return ACSImageFillMode::ACSImageFillModeRepeatHorizontally;
    case AdaptiveCards::ImageFillMode::RepeatVertically:
      return ACSImageFillMode::ACSImageFillModeRepeatVertically;
    case AdaptiveCards::ImageFillMode::Repeat:
      return ACSImageFillMode::ACSImageFillModeRepeat;
  }
}


+(AdaptiveCards::ImageFillMode) convertObj:(enum ACSImageFillMode) imageFillModeObjc
{
  switch(imageFillModeObjc)
  {
    case ACSImageFillMode::ACSImageFillModeCover:
      return AdaptiveCards::ImageFillMode::Cover;
    case ACSImageFillMode::ACSImageFillModeRepeatHorizontally:
      return AdaptiveCards::ImageFillMode::RepeatHorizontally;
    case ACSImageFillMode::ACSImageFillModeRepeatVertically:
      return AdaptiveCards::ImageFillMode::RepeatVertically;
    case ACSImageFillMode::ACSImageFillModeRepeat:
      return AdaptiveCards::ImageFillMode::Repeat;
  }
}

@end
