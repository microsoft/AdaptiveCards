// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSActionAlignmentConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSActionAlignment.h"

@implementation ACSActionAlignmentConvertor


+(enum ACSActionAlignment) convertCpp:(AdaptiveCards::ActionAlignment) actionAlignmentCpp
{
  switch(actionAlignmentCpp)
  {
    case AdaptiveCards::ActionAlignment::Left:
      return ACSActionAlignment::ACSActionAlignmentLeft;
    case AdaptiveCards::ActionAlignment::Center:
      return ACSActionAlignment::ACSActionAlignmentCenter;
    case AdaptiveCards::ActionAlignment::Right:
      return ACSActionAlignment::ACSActionAlignmentRight;
    case AdaptiveCards::ActionAlignment::Stretch:
      return ACSActionAlignment::ACSActionAlignmentStretch;
  }
}


+(AdaptiveCards::ActionAlignment) convertObj:(enum ACSActionAlignment) actionAlignmentObjc
{
  switch(actionAlignmentObjc)
  {
    case ACSActionAlignment::ACSActionAlignmentLeft:
      return AdaptiveCards::ActionAlignment::Left;
    case ACSActionAlignment::ACSActionAlignmentCenter:
      return AdaptiveCards::ActionAlignment::Center;
    case ACSActionAlignment::ACSActionAlignmentRight:
      return AdaptiveCards::ActionAlignment::Right;
    case ACSActionAlignment::ACSActionAlignmentStretch:
      return AdaptiveCards::ActionAlignment::Stretch;
  }
}

@end
