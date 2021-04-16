// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSFontTypeConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSFontType.h"

@implementation ACSFontTypeConvertor


+(enum ACSFontType) convertCpp:(AdaptiveCards::FontType) fontTypeCpp
{
  switch(fontTypeCpp)
  {
    case AdaptiveCards::FontType::Default:
      return ACSFontType::ACSFontTypeDefault;
    case AdaptiveCards::FontType::Monospace:
      return ACSFontType::ACSFontTypeMonospace;
  }
}


+(AdaptiveCards::FontType) convertObj:(enum ACSFontType) fontTypeObjc
{
  switch(fontTypeObjc)
  {
    case ACSFontType::ACSFontTypeDefault:
      return AdaptiveCards::FontType::Default;
    case ACSFontType::ACSFontTypeMonospace:
      return AdaptiveCards::FontType::Monospace;
  }
}

@end
