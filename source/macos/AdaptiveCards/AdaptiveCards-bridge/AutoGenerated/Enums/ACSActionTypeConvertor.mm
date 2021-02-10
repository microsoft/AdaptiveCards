// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSActionTypeConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSActionType.h"

@implementation ACSActionTypeConvertor


+(enum ACSActionType) convertCpp:(AdaptiveCards::ActionType) actionTypeCpp
{
  switch(actionTypeCpp)
  {
    case AdaptiveCards::ActionType::Unsupported:
      return ACSActionType::ACSActionTypeUnsupported;
    case AdaptiveCards::ActionType::ShowCard:
      return ACSActionType::ACSActionTypeShowCard;
    case AdaptiveCards::ActionType::Submit:
      return ACSActionType::ACSActionTypeSubmit;
    case AdaptiveCards::ActionType::OpenUrl:
      return ACSActionType::ACSActionTypeOpenUrl;
    case AdaptiveCards::ActionType::ToggleVisibility:
      return ACSActionType::ACSActionTypeToggleVisibility;
    case AdaptiveCards::ActionType::Custom:
      return ACSActionType::ACSActionTypeCustom;
    case AdaptiveCards::ActionType::UnknownAction:
      return ACSActionType::ACSActionTypeUnknownAction;
  }
}


+(AdaptiveCards::ActionType) convertObj:(enum ACSActionType) actionTypeObjc
{
  switch(actionTypeObjc)
  {
    case ACSActionType::ACSActionTypeUnsupported:
      return AdaptiveCards::ActionType::Unsupported;
    case ACSActionType::ACSActionTypeShowCard:
      return AdaptiveCards::ActionType::ShowCard;
    case ACSActionType::ACSActionTypeSubmit:
      return AdaptiveCards::ActionType::Submit;
    case ACSActionType::ACSActionTypeOpenUrl:
      return AdaptiveCards::ActionType::OpenUrl;
    case ACSActionType::ACSActionTypeToggleVisibility:
      return AdaptiveCards::ActionType::ToggleVisibility;
    case ACSActionType::ACSActionTypeCustom:
      return AdaptiveCards::ActionType::Custom;
    case ACSActionType::ACSActionTypeUnknownAction:
      return AdaptiveCards::ActionType::UnknownAction;
  }
}

@end
