// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSTextWeightConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSTextWeight.h"

@implementation ACSTextWeightConvertor


+(enum ACSTextWeight) convertCpp:(AdaptiveCards::TextWeight) textWeightCpp
{
  switch(textWeightCpp)
  {
    case AdaptiveCards::TextWeight::Lighter:
      return ACSTextWeight::ACSTextWeightLighter;
    case AdaptiveCards::TextWeight::Default:
      return ACSTextWeight::ACSTextWeightDefault;
    case AdaptiveCards::TextWeight::Bolder:
      return ACSTextWeight::ACSTextWeightBolder;
  }
}


+(AdaptiveCards::TextWeight) convertObj:(enum ACSTextWeight) textWeightObjc
{
  switch(textWeightObjc)
  {
    case ACSTextWeight::ACSTextWeightLighter:
      return AdaptiveCards::TextWeight::Lighter;
    case ACSTextWeight::ACSTextWeightDefault:
      return AdaptiveCards::TextWeight::Default;
    case ACSTextWeight::ACSTextWeightBolder:
      return AdaptiveCards::TextWeight::Bolder;
  }
}

@end
