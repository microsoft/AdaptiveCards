// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSActionModeConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSActionMode.h"

@implementation ACSActionModeConvertor


+(enum ACSActionMode) convertCpp:(AdaptiveCards::ActionMode) actionModeCpp
{
  switch(actionModeCpp)
  {
    case AdaptiveCards::ActionMode::Inline:
      return ACSActionMode::ACSActionModeInline;
    case AdaptiveCards::ActionMode::Popup:
      return ACSActionMode::ACSActionModePopup;
  }
}


+(AdaptiveCards::ActionMode) convertObj:(enum ACSActionMode) actionModeObjc
{
  switch(actionModeObjc)
  {
    case ACSActionMode::ACSActionModeInline:
      return AdaptiveCards::ActionMode::Inline;
    case ACSActionMode::ACSActionModePopup:
      return AdaptiveCards::ActionMode::Popup;
  }
}

@end
