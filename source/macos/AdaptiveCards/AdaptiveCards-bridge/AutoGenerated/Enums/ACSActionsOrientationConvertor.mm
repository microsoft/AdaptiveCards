// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSActionsOrientationConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSActionsOrientation.h"

@implementation ACSActionsOrientationConvertor


+(enum ACSActionsOrientation) convertCpp:(AdaptiveCards::ActionsOrientation) actionsOrientationCpp
{
  switch(actionsOrientationCpp)
  {
    case AdaptiveCards::ActionsOrientation::Vertical:
      return ACSActionsOrientation::ACSActionsOrientationVertical;
    case AdaptiveCards::ActionsOrientation::Horizontal:
      return ACSActionsOrientation::ACSActionsOrientationHorizontal;
  }
}


+(AdaptiveCards::ActionsOrientation) convertObj:(enum ACSActionsOrientation) actionsOrientationObjc
{
  switch(actionsOrientationObjc)
  {
    case ACSActionsOrientation::ACSActionsOrientationVertical:
      return AdaptiveCards::ActionsOrientation::Vertical;
    case ACSActionsOrientation::ACSActionsOrientationHorizontal:
      return AdaptiveCards::ActionsOrientation::Horizontal;
  }
}

@end
