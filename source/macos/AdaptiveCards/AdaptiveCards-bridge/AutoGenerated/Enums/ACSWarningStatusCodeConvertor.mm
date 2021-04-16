// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSWarningStatusCodeConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSWarningStatusCode.h"

@implementation ACSWarningStatusCodeConvertor


+(enum ACSWarningStatusCode) convertCpp:(AdaptiveCards::WarningStatusCode) warningStatusCodeCpp
{
  switch(warningStatusCodeCpp)
  {
    case AdaptiveCards::WarningStatusCode::UnknownElementType:
      return ACSWarningStatusCode::ACSWarningStatusCodeUnknownElementType;
    case AdaptiveCards::WarningStatusCode::UnknownActionElementType:
      return ACSWarningStatusCode::ACSWarningStatusCodeUnknownActionElementType;
    case AdaptiveCards::WarningStatusCode::UnknownPropertyOnElement:
      return ACSWarningStatusCode::ACSWarningStatusCodeUnknownPropertyOnElement;
    case AdaptiveCards::WarningStatusCode::UnknownEnumValue:
      return ACSWarningStatusCode::ACSWarningStatusCodeUnknownEnumValue;
    case AdaptiveCards::WarningStatusCode::NoRendererForType:
      return ACSWarningStatusCode::ACSWarningStatusCodeNoRendererForType;
    case AdaptiveCards::WarningStatusCode::InteractivityNotSupported:
      return ACSWarningStatusCode::ACSWarningStatusCodeInteractivityNotSupported;
    case AdaptiveCards::WarningStatusCode::MaxActionsExceeded:
      return ACSWarningStatusCode::ACSWarningStatusCodeMaxActionsExceeded;
    case AdaptiveCards::WarningStatusCode::AssetLoadFailed:
      return ACSWarningStatusCode::ACSWarningStatusCodeAssetLoadFailed;
    case AdaptiveCards::WarningStatusCode::UnsupportedSchemaVersion:
      return ACSWarningStatusCode::ACSWarningStatusCodeUnsupportedSchemaVersion;
    case AdaptiveCards::WarningStatusCode::UnsupportedMediaType:
      return ACSWarningStatusCode::ACSWarningStatusCodeUnsupportedMediaType;
    case AdaptiveCards::WarningStatusCode::InvalidMediaMix:
      return ACSWarningStatusCode::ACSWarningStatusCodeInvalidMediaMix;
    case AdaptiveCards::WarningStatusCode::InvalidColorFormat:
      return ACSWarningStatusCode::ACSWarningStatusCodeInvalidColorFormat;
    case AdaptiveCards::WarningStatusCode::InvalidDimensionSpecified:
      return ACSWarningStatusCode::ACSWarningStatusCodeInvalidDimensionSpecified;
    case AdaptiveCards::WarningStatusCode::InvalidLanguage:
      return ACSWarningStatusCode::ACSWarningStatusCodeInvalidLanguage;
    case AdaptiveCards::WarningStatusCode::InvalidValue:
      return ACSWarningStatusCode::ACSWarningStatusCodeInvalidValue;
    case AdaptiveCards::WarningStatusCode::CustomWarning:
      return ACSWarningStatusCode::ACSWarningStatusCodeCustomWarning;
    case AdaptiveCards::WarningStatusCode::EmptyLabelInRequiredInput:
      return ACSWarningStatusCode::ACSWarningStatusCodeEmptyLabelInRequiredInput;
    case AdaptiveCards::WarningStatusCode::RequiredPropertyMissing:
      return ACSWarningStatusCode::ACSWarningStatusCodeRequiredPropertyMissing;
  }
}


+(AdaptiveCards::WarningStatusCode) convertObj:(enum ACSWarningStatusCode) warningStatusCodeObjc
{
  switch(warningStatusCodeObjc)
  {
    case ACSWarningStatusCode::ACSWarningStatusCodeUnknownElementType:
      return AdaptiveCards::WarningStatusCode::UnknownElementType;
    case ACSWarningStatusCode::ACSWarningStatusCodeUnknownActionElementType:
      return AdaptiveCards::WarningStatusCode::UnknownActionElementType;
    case ACSWarningStatusCode::ACSWarningStatusCodeUnknownPropertyOnElement:
      return AdaptiveCards::WarningStatusCode::UnknownPropertyOnElement;
    case ACSWarningStatusCode::ACSWarningStatusCodeUnknownEnumValue:
      return AdaptiveCards::WarningStatusCode::UnknownEnumValue;
    case ACSWarningStatusCode::ACSWarningStatusCodeNoRendererForType:
      return AdaptiveCards::WarningStatusCode::NoRendererForType;
    case ACSWarningStatusCode::ACSWarningStatusCodeInteractivityNotSupported:
      return AdaptiveCards::WarningStatusCode::InteractivityNotSupported;
    case ACSWarningStatusCode::ACSWarningStatusCodeMaxActionsExceeded:
      return AdaptiveCards::WarningStatusCode::MaxActionsExceeded;
    case ACSWarningStatusCode::ACSWarningStatusCodeAssetLoadFailed:
      return AdaptiveCards::WarningStatusCode::AssetLoadFailed;
    case ACSWarningStatusCode::ACSWarningStatusCodeUnsupportedSchemaVersion:
      return AdaptiveCards::WarningStatusCode::UnsupportedSchemaVersion;
    case ACSWarningStatusCode::ACSWarningStatusCodeUnsupportedMediaType:
      return AdaptiveCards::WarningStatusCode::UnsupportedMediaType;
    case ACSWarningStatusCode::ACSWarningStatusCodeInvalidMediaMix:
      return AdaptiveCards::WarningStatusCode::InvalidMediaMix;
    case ACSWarningStatusCode::ACSWarningStatusCodeInvalidColorFormat:
      return AdaptiveCards::WarningStatusCode::InvalidColorFormat;
    case ACSWarningStatusCode::ACSWarningStatusCodeInvalidDimensionSpecified:
      return AdaptiveCards::WarningStatusCode::InvalidDimensionSpecified;
    case ACSWarningStatusCode::ACSWarningStatusCodeInvalidLanguage:
      return AdaptiveCards::WarningStatusCode::InvalidLanguage;
    case ACSWarningStatusCode::ACSWarningStatusCodeInvalidValue:
      return AdaptiveCards::WarningStatusCode::InvalidValue;
    case ACSWarningStatusCode::ACSWarningStatusCodeCustomWarning:
      return AdaptiveCards::WarningStatusCode::CustomWarning;
    case ACSWarningStatusCode::ACSWarningStatusCodeEmptyLabelInRequiredInput:
      return AdaptiveCards::WarningStatusCode::EmptyLabelInRequiredInput;
    case ACSWarningStatusCode::ACSWarningStatusCodeRequiredPropertyMissing:
      return AdaptiveCards::WarningStatusCode::RequiredPropertyMissing;
  }
}

@end
