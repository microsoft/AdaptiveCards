// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSDelimiterTypeConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSDelimiterType.h"

@implementation ACSDelimiterTypeConvertor


+(enum ACSDelimiterType) convertCpp:(AdaptiveCards::DelimiterType) delimiterTypeCpp
{
  switch(delimiterTypeCpp)
  {
    case AdaptiveCards::DelimiterType::Init:
      return ACSDelimiterType::ACSDelimiterTypeInit;
    case AdaptiveCards::DelimiterType::Alphanumeric:
      return ACSDelimiterType::ACSDelimiterTypeAlphanumeric;
    case AdaptiveCards::DelimiterType::Puntuation:
      return ACSDelimiterType::ACSDelimiterTypePuntuation;
    case AdaptiveCards::DelimiterType::Escape:
      return ACSDelimiterType::ACSDelimiterTypeEscape;
    case AdaptiveCards::DelimiterType::WhiteSpace:
      return ACSDelimiterType::ACSDelimiterTypeWhiteSpace;
    case AdaptiveCards::DelimiterType::Underscore:
      return ACSDelimiterType::ACSDelimiterTypeUnderscore;
    case AdaptiveCards::DelimiterType::Asterisk:
      return ACSDelimiterType::ACSDelimiterTypeAsterisk;
  }
}


+(AdaptiveCards::DelimiterType) convertObj:(enum ACSDelimiterType) delimiterTypeObjc
{
  switch(delimiterTypeObjc)
  {
    case ACSDelimiterType::ACSDelimiterTypeInit:
      return AdaptiveCards::DelimiterType::Init;
    case ACSDelimiterType::ACSDelimiterTypeAlphanumeric:
      return AdaptiveCards::DelimiterType::Alphanumeric;
    case ACSDelimiterType::ACSDelimiterTypePuntuation:
      return AdaptiveCards::DelimiterType::Puntuation;
    case ACSDelimiterType::ACSDelimiterTypeEscape:
      return AdaptiveCards::DelimiterType::Escape;
    case ACSDelimiterType::ACSDelimiterTypeWhiteSpace:
      return AdaptiveCards::DelimiterType::WhiteSpace;
    case ACSDelimiterType::ACSDelimiterTypeUnderscore:
      return AdaptiveCards::DelimiterType::Underscore;
    case ACSDelimiterType::ACSDelimiterTypeAsterisk:
      return AdaptiveCards::DelimiterType::Asterisk;
  }
}

@end
