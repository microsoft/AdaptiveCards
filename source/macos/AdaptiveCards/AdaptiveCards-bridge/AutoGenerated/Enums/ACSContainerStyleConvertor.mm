// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSContainerStyleConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSContainerStyle.h"

@implementation ACSContainerStyleConvertor


+(enum ACSContainerStyle) convertCpp:(AdaptiveCards::ContainerStyle) containerStyleCpp
{
  switch(containerStyleCpp)
  {
    case AdaptiveCards::ContainerStyle::None:
      return ACSContainerStyle::ACSContainerStyleNone;
    case AdaptiveCards::ContainerStyle::Default:
      return ACSContainerStyle::ACSContainerStyleDefault;
    case AdaptiveCards::ContainerStyle::Emphasis:
      return ACSContainerStyle::ACSContainerStyleEmphasis;
    case AdaptiveCards::ContainerStyle::Good:
      return ACSContainerStyle::ACSContainerStyleGood;
    case AdaptiveCards::ContainerStyle::Attention:
      return ACSContainerStyle::ACSContainerStyleAttention;
    case AdaptiveCards::ContainerStyle::Warning:
      return ACSContainerStyle::ACSContainerStyleWarning;
    case AdaptiveCards::ContainerStyle::Accent:
      return ACSContainerStyle::ACSContainerStyleAccent;
  }
}


+(AdaptiveCards::ContainerStyle) convertObj:(enum ACSContainerStyle) containerStyleObjc
{
  switch(containerStyleObjc)
  {
    case ACSContainerStyle::ACSContainerStyleNone:
      return AdaptiveCards::ContainerStyle::None;
    case ACSContainerStyle::ACSContainerStyleDefault:
      return AdaptiveCards::ContainerStyle::Default;
    case ACSContainerStyle::ACSContainerStyleEmphasis:
      return AdaptiveCards::ContainerStyle::Emphasis;
    case ACSContainerStyle::ACSContainerStyleGood:
      return AdaptiveCards::ContainerStyle::Good;
    case ACSContainerStyle::ACSContainerStyleAttention:
      return AdaptiveCards::ContainerStyle::Attention;
    case ACSContainerStyle::ACSContainerStyleWarning:
      return AdaptiveCards::ContainerStyle::Warning;
    case ACSContainerStyle::ACSContainerStyleAccent:
      return AdaptiveCards::ContainerStyle::Accent;
  }
}

@end
