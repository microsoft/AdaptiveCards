// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSHorizontalAlignmentConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSHorizontalAlignment.h"

@implementation ACSHorizontalAlignmentConvertor


+(enum ACSHorizontalAlignment) convertCpp:(AdaptiveCards::HorizontalAlignment) horizontalAlignmentCpp
{
  switch(horizontalAlignmentCpp)
  {
    case AdaptiveCards::HorizontalAlignment::Left:
      return ACSHorizontalAlignment::ACSHorizontalAlignmentLeft;
    case AdaptiveCards::HorizontalAlignment::Center:
      return ACSHorizontalAlignment::ACSHorizontalAlignmentCenter;
    case AdaptiveCards::HorizontalAlignment::Right:
      return ACSHorizontalAlignment::ACSHorizontalAlignmentRight;
  }
}


+(AdaptiveCards::HorizontalAlignment) convertObj:(enum ACSHorizontalAlignment) horizontalAlignmentObjc
{
  switch(horizontalAlignmentObjc)
  {
    case ACSHorizontalAlignment::ACSHorizontalAlignmentLeft:
      return AdaptiveCards::HorizontalAlignment::Left;
    case ACSHorizontalAlignment::ACSHorizontalAlignmentCenter:
      return AdaptiveCards::HorizontalAlignment::Center;
    case ACSHorizontalAlignment::ACSHorizontalAlignmentRight:
      return AdaptiveCards::HorizontalAlignment::Right;
  }
}

@end
