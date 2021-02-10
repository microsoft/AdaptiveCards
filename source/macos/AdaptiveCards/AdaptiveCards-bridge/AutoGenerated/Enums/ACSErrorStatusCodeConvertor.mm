// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSErrorStatusCodeConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSErrorStatusCode.h"

@implementation ACSErrorStatusCodeConvertor


+(enum ACSErrorStatusCode) convertCpp:(AdaptiveCards::ErrorStatusCode) errorStatusCodeCpp
{
  switch(errorStatusCodeCpp)
  {
    case AdaptiveCards::ErrorStatusCode::InvalidJson:
      return ACSErrorStatusCode::ACSErrorStatusCodeInvalidJson;
    case AdaptiveCards::ErrorStatusCode::RenderFailed:
      return ACSErrorStatusCode::ACSErrorStatusCodeRenderFailed;
    case AdaptiveCards::ErrorStatusCode::RequiredPropertyMissing:
      return ACSErrorStatusCode::ACSErrorStatusCodeRequiredPropertyMissing;
    case AdaptiveCards::ErrorStatusCode::InvalidPropertyValue:
      return ACSErrorStatusCode::ACSErrorStatusCodeInvalidPropertyValue;
    case AdaptiveCards::ErrorStatusCode::UnsupportedParserOverride:
      return ACSErrorStatusCode::ACSErrorStatusCodeUnsupportedParserOverride;
    case AdaptiveCards::ErrorStatusCode::IdCollision:
      return ACSErrorStatusCode::ACSErrorStatusCodeIdCollision;
    case AdaptiveCards::ErrorStatusCode::CustomError:
      return ACSErrorStatusCode::ACSErrorStatusCodeCustomError;
  }
}


+(AdaptiveCards::ErrorStatusCode) convertObj:(enum ACSErrorStatusCode) errorStatusCodeObjc
{
  switch(errorStatusCodeObjc)
  {
    case ACSErrorStatusCode::ACSErrorStatusCodeInvalidJson:
      return AdaptiveCards::ErrorStatusCode::InvalidJson;
    case ACSErrorStatusCode::ACSErrorStatusCodeRenderFailed:
      return AdaptiveCards::ErrorStatusCode::RenderFailed;
    case ACSErrorStatusCode::ACSErrorStatusCodeRequiredPropertyMissing:
      return AdaptiveCards::ErrorStatusCode::RequiredPropertyMissing;
    case ACSErrorStatusCode::ACSErrorStatusCodeInvalidPropertyValue:
      return AdaptiveCards::ErrorStatusCode::InvalidPropertyValue;
    case ACSErrorStatusCode::ACSErrorStatusCodeUnsupportedParserOverride:
      return AdaptiveCards::ErrorStatusCode::UnsupportedParserOverride;
    case ACSErrorStatusCode::ACSErrorStatusCodeIdCollision:
      return AdaptiveCards::ErrorStatusCode::IdCollision;
    case ACSErrorStatusCode::ACSErrorStatusCodeCustomError:
      return AdaptiveCards::ErrorStatusCode::CustomError;
  }
}

@end
