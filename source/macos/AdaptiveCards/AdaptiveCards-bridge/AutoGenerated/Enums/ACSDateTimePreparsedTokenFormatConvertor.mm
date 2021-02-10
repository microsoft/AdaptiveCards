// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSDateTimePreparsedTokenFormatConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSDateTimePreparsedTokenFormat.h"

@implementation ACSDateTimePreparsedTokenFormatConvertor


+(enum ACSDateTimePreparsedTokenFormat) convertCpp:(AdaptiveCards::DateTimePreparsedTokenFormat) dateTimePreparsedTokenFormatCpp
{
  switch(dateTimePreparsedTokenFormatCpp)
  {
    case AdaptiveCards::DateTimePreparsedTokenFormat::RegularString:
      return ACSDateTimePreparsedTokenFormat::ACSDateTimePreparsedTokenFormatRegularString;
    case AdaptiveCards::DateTimePreparsedTokenFormat::Time:
      return ACSDateTimePreparsedTokenFormat::ACSDateTimePreparsedTokenFormatTime;
    case AdaptiveCards::DateTimePreparsedTokenFormat::DateCompact:
      return ACSDateTimePreparsedTokenFormat::ACSDateTimePreparsedTokenFormatDateCompact;
    case AdaptiveCards::DateTimePreparsedTokenFormat::DateShort:
      return ACSDateTimePreparsedTokenFormat::ACSDateTimePreparsedTokenFormatDateShort;
    case AdaptiveCards::DateTimePreparsedTokenFormat::DateLong:
      return ACSDateTimePreparsedTokenFormat::ACSDateTimePreparsedTokenFormatDateLong;
  }
}


+(AdaptiveCards::DateTimePreparsedTokenFormat) convertObj:(enum ACSDateTimePreparsedTokenFormat) dateTimePreparsedTokenFormatObjc
{
  switch(dateTimePreparsedTokenFormatObjc)
  {
    case ACSDateTimePreparsedTokenFormat::ACSDateTimePreparsedTokenFormatRegularString:
      return AdaptiveCards::DateTimePreparsedTokenFormat::RegularString;
    case ACSDateTimePreparsedTokenFormat::ACSDateTimePreparsedTokenFormatTime:
      return AdaptiveCards::DateTimePreparsedTokenFormat::Time;
    case ACSDateTimePreparsedTokenFormat::ACSDateTimePreparsedTokenFormatDateCompact:
      return AdaptiveCards::DateTimePreparsedTokenFormat::DateCompact;
    case ACSDateTimePreparsedTokenFormat::ACSDateTimePreparsedTokenFormatDateShort:
      return AdaptiveCards::DateTimePreparsedTokenFormat::DateShort;
    case ACSDateTimePreparsedTokenFormat::ACSDateTimePreparsedTokenFormatDateLong:
      return AdaptiveCards::DateTimePreparsedTokenFormat::DateLong;
  }
}

@end
