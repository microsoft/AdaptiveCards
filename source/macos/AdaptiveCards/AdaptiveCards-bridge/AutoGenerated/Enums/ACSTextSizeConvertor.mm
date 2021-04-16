// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSTextSizeConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSTextSize.h"

@implementation ACSTextSizeConvertor


+(enum ACSTextSize) convertCpp:(AdaptiveCards::TextSize) textSizeCpp
{
  switch(textSizeCpp)
  {
    case AdaptiveCards::TextSize::Small:
      return ACSTextSize::ACSTextSizeSmall;
    case AdaptiveCards::TextSize::Default:
      return ACSTextSize::ACSTextSizeDefault;
    case AdaptiveCards::TextSize::Medium:
      return ACSTextSize::ACSTextSizeMedium;
    case AdaptiveCards::TextSize::Large:
      return ACSTextSize::ACSTextSizeLarge;
    case AdaptiveCards::TextSize::ExtraLarge:
      return ACSTextSize::ACSTextSizeExtraLarge;
  }
}


+(AdaptiveCards::TextSize) convertObj:(enum ACSTextSize) textSizeObjc
{
  switch(textSizeObjc)
  {
    case ACSTextSize::ACSTextSizeSmall:
      return AdaptiveCards::TextSize::Small;
    case ACSTextSize::ACSTextSizeDefault:
      return AdaptiveCards::TextSize::Default;
    case ACSTextSize::ACSTextSizeMedium:
      return AdaptiveCards::TextSize::Medium;
    case ACSTextSize::ACSTextSizeLarge:
      return AdaptiveCards::TextSize::Large;
    case ACSTextSize::ACSTextSizeExtraLarge:
      return AdaptiveCards::TextSize::ExtraLarge;
  }
}

@end
