// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSSeparatorThicknessConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSSeparatorThickness.h"

@implementation ACSSeparatorThicknessConvertor


+(enum ACSSeparatorThickness) convertCpp:(AdaptiveCards::SeparatorThickness) separatorThicknessCpp
{
  switch(separatorThicknessCpp)
  {
    case AdaptiveCards::SeparatorThickness::Default:
      return ACSSeparatorThickness::ACSSeparatorThicknessDefault;
    case AdaptiveCards::SeparatorThickness::Thick:
      return ACSSeparatorThickness::ACSSeparatorThicknessThick;
  }
}


+(AdaptiveCards::SeparatorThickness) convertObj:(enum ACSSeparatorThickness) separatorThicknessObjc
{
  switch(separatorThicknessObjc)
  {
    case ACSSeparatorThickness::ACSSeparatorThicknessDefault:
      return AdaptiveCards::SeparatorThickness::Default;
    case ACSSeparatorThickness::ACSSeparatorThicknessThick:
      return AdaptiveCards::SeparatorThickness::Thick;
  }
}

@end
