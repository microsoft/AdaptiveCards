// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSTextInputStyleConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSTextInputStyle.h"

@implementation ACSTextInputStyleConvertor


+(enum ACSTextInputStyle) convertCpp:(AdaptiveCards::TextInputStyle) textInputStyleCpp
{
  switch(textInputStyleCpp)
  {
    case AdaptiveCards::TextInputStyle::Text:
      return ACSTextInputStyle::ACSTextInputStyleText;
    case AdaptiveCards::TextInputStyle::Tel:
      return ACSTextInputStyle::ACSTextInputStyleTel;
    case AdaptiveCards::TextInputStyle::Url:
      return ACSTextInputStyle::ACSTextInputStyleUrl;
    case AdaptiveCards::TextInputStyle::Email:
      return ACSTextInputStyle::ACSTextInputStyleEmail;
  }
}


+(AdaptiveCards::TextInputStyle) convertObj:(enum ACSTextInputStyle) textInputStyleObjc
{
  switch(textInputStyleObjc)
  {
    case ACSTextInputStyle::ACSTextInputStyleText:
      return AdaptiveCards::TextInputStyle::Text;
    case ACSTextInputStyle::ACSTextInputStyleTel:
      return AdaptiveCards::TextInputStyle::Tel;
    case ACSTextInputStyle::ACSTextInputStyleUrl:
      return AdaptiveCards::TextInputStyle::Url;
    case ACSTextInputStyle::ACSTextInputStyleEmail:
      return AdaptiveCards::TextInputStyle::Email;
  }
}

@end
