// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSAssociatedInputsConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSAssociatedInputs.h"

@implementation ACSAssociatedInputsConvertor


+(enum ACSAssociatedInputs) convertCpp:(AdaptiveCards::AssociatedInputs) associatedInputsCpp
{
  switch(associatedInputsCpp)
  {
    case AdaptiveCards::AssociatedInputs::Auto:
      return ACSAssociatedInputs::ACSAssociatedInputsAuto;
    case AdaptiveCards::AssociatedInputs::None:
      return ACSAssociatedInputs::ACSAssociatedInputsNone;
  }
}


+(AdaptiveCards::AssociatedInputs) convertObj:(enum ACSAssociatedInputs) associatedInputsObjc
{
  switch(associatedInputsObjc)
  {
    case ACSAssociatedInputs::ACSAssociatedInputsAuto:
      return AdaptiveCards::AssociatedInputs::Auto;
    case ACSAssociatedInputs::ACSAssociatedInputsNone:
      return AdaptiveCards::AssociatedInputs::None;
  }
}

@end
