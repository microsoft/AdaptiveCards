// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSSpacingConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSSpacing.h"

@implementation ACSSpacingConvertor


+(enum ACSSpacing) convertCpp:(AdaptiveCards::Spacing) spacingCpp
{
  switch(spacingCpp)
  {
    case AdaptiveCards::Spacing::Default:
      return ACSSpacing::ACSSpacingDefault;
    case AdaptiveCards::Spacing::None:
      return ACSSpacing::ACSSpacingNone;
    case AdaptiveCards::Spacing::Small:
      return ACSSpacing::ACSSpacingSmall;
    case AdaptiveCards::Spacing::Medium:
      return ACSSpacing::ACSSpacingMedium;
    case AdaptiveCards::Spacing::Large:
      return ACSSpacing::ACSSpacingLarge;
    case AdaptiveCards::Spacing::ExtraLarge:
      return ACSSpacing::ACSSpacingExtraLarge;
    case AdaptiveCards::Spacing::Padding:
      return ACSSpacing::ACSSpacingPadding;
  }
}


+(AdaptiveCards::Spacing) convertObj:(enum ACSSpacing) spacingObjc
{
  switch(spacingObjc)
  {
    case ACSSpacing::ACSSpacingDefault:
      return AdaptiveCards::Spacing::Default;
    case ACSSpacing::ACSSpacingNone:
      return AdaptiveCards::Spacing::None;
    case ACSSpacing::ACSSpacingSmall:
      return AdaptiveCards::Spacing::Small;
    case ACSSpacing::ACSSpacingMedium:
      return AdaptiveCards::Spacing::Medium;
    case ACSSpacing::ACSSpacingLarge:
      return AdaptiveCards::Spacing::Large;
    case ACSSpacing::ACSSpacingExtraLarge:
      return AdaptiveCards::Spacing::ExtraLarge;
    case ACSSpacing::ACSSpacingPadding:
      return AdaptiveCards::Spacing::Padding;
  }
}

@end
