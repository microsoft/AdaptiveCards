// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSForegroundColorConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSForegroundColor.h"

@implementation ACSForegroundColorConvertor


+(enum ACSForegroundColor) convertCpp:(AdaptiveCards::ForegroundColor) foregroundColorCpp
{
  switch(foregroundColorCpp)
  {
    case AdaptiveCards::ForegroundColor::Default:
      return ACSForegroundColor::ACSForegroundColorDefault;
    case AdaptiveCards::ForegroundColor::Dark:
      return ACSForegroundColor::ACSForegroundColorDark;
    case AdaptiveCards::ForegroundColor::Light:
      return ACSForegroundColor::ACSForegroundColorLight;
    case AdaptiveCards::ForegroundColor::Accent:
      return ACSForegroundColor::ACSForegroundColorAccent;
    case AdaptiveCards::ForegroundColor::Good:
      return ACSForegroundColor::ACSForegroundColorGood;
    case AdaptiveCards::ForegroundColor::Warning:
      return ACSForegroundColor::ACSForegroundColorWarning;
    case AdaptiveCards::ForegroundColor::Attention:
      return ACSForegroundColor::ACSForegroundColorAttention;
  }
}


+(AdaptiveCards::ForegroundColor) convertObj:(enum ACSForegroundColor) foregroundColorObjc
{
  switch(foregroundColorObjc)
  {
    case ACSForegroundColor::ACSForegroundColorDefault:
      return AdaptiveCards::ForegroundColor::Default;
    case ACSForegroundColor::ACSForegroundColorDark:
      return AdaptiveCards::ForegroundColor::Dark;
    case ACSForegroundColor::ACSForegroundColorLight:
      return AdaptiveCards::ForegroundColor::Light;
    case ACSForegroundColor::ACSForegroundColorAccent:
      return AdaptiveCards::ForegroundColor::Accent;
    case ACSForegroundColor::ACSForegroundColorGood:
      return AdaptiveCards::ForegroundColor::Good;
    case ACSForegroundColor::ACSForegroundColorWarning:
      return AdaptiveCards::ForegroundColor::Warning;
    case ACSForegroundColor::ACSForegroundColorAttention:
      return AdaptiveCards::ForegroundColor::Attention;
  }
}

@end
