// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSVerticalContentAlignmentConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSVerticalContentAlignment.h"

@implementation ACSVerticalContentAlignmentConvertor


+(enum ACSVerticalContentAlignment) convertCpp:(AdaptiveCards::VerticalContentAlignment) verticalContentAlignmentCpp
{
  switch(verticalContentAlignmentCpp)
  {
    case AdaptiveCards::VerticalContentAlignment::Top:
      return ACSVerticalContentAlignment::ACSVerticalContentAlignmentTop;
    case AdaptiveCards::VerticalContentAlignment::Center:
      return ACSVerticalContentAlignment::ACSVerticalContentAlignmentCenter;
    case AdaptiveCards::VerticalContentAlignment::Bottom:
      return ACSVerticalContentAlignment::ACSVerticalContentAlignmentBottom;
  }
}


+(AdaptiveCards::VerticalContentAlignment) convertObj:(enum ACSVerticalContentAlignment) verticalContentAlignmentObjc
{
  switch(verticalContentAlignmentObjc)
  {
    case ACSVerticalContentAlignment::ACSVerticalContentAlignmentTop:
      return AdaptiveCards::VerticalContentAlignment::Top;
    case ACSVerticalContentAlignment::ACSVerticalContentAlignmentCenter:
      return AdaptiveCards::VerticalContentAlignment::Center;
    case ACSVerticalContentAlignment::ACSVerticalContentAlignmentBottom:
      return AdaptiveCards::VerticalContentAlignment::Bottom;
  }
}

@end
