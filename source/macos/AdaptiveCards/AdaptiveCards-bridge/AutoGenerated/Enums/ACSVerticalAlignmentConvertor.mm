// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSVerticalAlignmentConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSVerticalAlignment.h"

@implementation ACSVerticalAlignmentConvertor


+(enum ACSVerticalAlignment) convertCpp:(AdaptiveCards::VerticalAlignment) verticalAlignmentCpp
{
  switch(verticalAlignmentCpp)
  {
    case AdaptiveCards::VerticalAlignment::Top:
      return ACSVerticalAlignment::ACSVerticalAlignmentTop;
    case AdaptiveCards::VerticalAlignment::Center:
      return ACSVerticalAlignment::ACSVerticalAlignmentCenter;
    case AdaptiveCards::VerticalAlignment::Bottom:
      return ACSVerticalAlignment::ACSVerticalAlignmentBottom;
  }
}


+(AdaptiveCards::VerticalAlignment) convertObj:(enum ACSVerticalAlignment) verticalAlignmentObjc
{
  switch(verticalAlignmentObjc)
  {
    case ACSVerticalAlignment::ACSVerticalAlignmentTop:
      return AdaptiveCards::VerticalAlignment::Top;
    case ACSVerticalAlignment::ACSVerticalAlignmentCenter:
      return AdaptiveCards::VerticalAlignment::Center;
    case ACSVerticalAlignment::ACSVerticalAlignmentBottom:
      return AdaptiveCards::VerticalAlignment::Bottom;
  }
}

@end
