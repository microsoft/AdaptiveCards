// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSIsVisibleConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/ToggleVisibilityTarget.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSIsVisible.h"

@implementation ACSIsVisibleConvertor


+(enum ACSIsVisible) convertCpp:(AdaptiveCards::IsVisible) isVisibleCpp
{
  switch(isVisibleCpp)
  {
    case AdaptiveCards::IsVisible::IsVisibleToggle:
      return ACSIsVisible::ACSIsVisibleIsVisibleToggle;
    case AdaptiveCards::IsVisible::IsVisibleTrue:
      return ACSIsVisible::ACSIsVisibleIsVisibleTrue;
    case AdaptiveCards::IsVisible::IsVisibleFalse:
      return ACSIsVisible::ACSIsVisibleIsVisibleFalse;
  }
}


+(AdaptiveCards::IsVisible) convertObj:(enum ACSIsVisible) isVisibleObjc
{
  switch(isVisibleObjc)
  {
    case ACSIsVisible::ACSIsVisibleIsVisibleToggle:
      return AdaptiveCards::IsVisible::IsVisibleToggle;
    case ACSIsVisible::ACSIsVisibleIsVisibleTrue:
      return AdaptiveCards::IsVisible::IsVisibleTrue;
    case ACSIsVisible::ACSIsVisibleIsVisibleFalse:
      return AdaptiveCards::IsVisible::IsVisibleFalse;
  }
}

@end
