// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSHeightTypeConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSHeightType.h"

@implementation ACSHeightTypeConvertor


+(enum ACSHeightType) convertCpp:(AdaptiveCards::HeightType) heightTypeCpp
{
  switch(heightTypeCpp)
  {
    case AdaptiveCards::HeightType::Auto:
      return ACSHeightType::ACSHeightTypeAuto;
    case AdaptiveCards::HeightType::Stretch:
      return ACSHeightType::ACSHeightTypeStretch;
  }
}


+(AdaptiveCards::HeightType) convertObj:(enum ACSHeightType) heightTypeObjc
{
  switch(heightTypeObjc)
  {
    case ACSHeightType::ACSHeightTypeAuto:
      return AdaptiveCards::HeightType::Auto;
    case ACSHeightType::ACSHeightTypeStretch:
      return AdaptiveCards::HeightType::Stretch;
  }
}

@end
