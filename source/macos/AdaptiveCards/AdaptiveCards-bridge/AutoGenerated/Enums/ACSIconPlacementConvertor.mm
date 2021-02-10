// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSIconPlacementConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSIconPlacement.h"

@implementation ACSIconPlacementConvertor


+(enum ACSIconPlacement) convertCpp:(AdaptiveCards::IconPlacement) iconPlacementCpp
{
  switch(iconPlacementCpp)
  {
    case AdaptiveCards::IconPlacement::AboveTitle:
      return ACSIconPlacement::ACSIconPlacementAboveTitle;
    case AdaptiveCards::IconPlacement::LeftOfTitle:
      return ACSIconPlacement::ACSIconPlacementLeftOfTitle;
  }
}


+(AdaptiveCards::IconPlacement) convertObj:(enum ACSIconPlacement) iconPlacementObjc
{
  switch(iconPlacementObjc)
  {
    case ACSIconPlacement::ACSIconPlacementAboveTitle:
      return AdaptiveCards::IconPlacement::AboveTitle;
    case ACSIconPlacement::ACSIconPlacementLeftOfTitle:
      return AdaptiveCards::IconPlacement::LeftOfTitle;
  }
}

@end
