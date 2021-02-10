// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSCardElementTypeConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSCardElementType.h"

@implementation ACSCardElementTypeConvertor


+(enum ACSCardElementType) convertCpp:(AdaptiveCards::CardElementType) cardElementTypeCpp
{
  switch(cardElementTypeCpp)
  {
    case AdaptiveCards::CardElementType::ActionSet:
      return ACSCardElementType::ACSCardElementTypeActionSet;
    case AdaptiveCards::CardElementType::AdaptiveCard:
      return ACSCardElementType::ACSCardElementTypeAdaptiveCard;
    case AdaptiveCards::CardElementType::ChoiceInput:
      return ACSCardElementType::ACSCardElementTypeChoiceInput;
    case AdaptiveCards::CardElementType::ChoiceSetInput:
      return ACSCardElementType::ACSCardElementTypeChoiceSetInput;
    case AdaptiveCards::CardElementType::Column:
      return ACSCardElementType::ACSCardElementTypeColumn;
    case AdaptiveCards::CardElementType::ColumnSet:
      return ACSCardElementType::ACSCardElementTypeColumnSet;
    case AdaptiveCards::CardElementType::Container:
      return ACSCardElementType::ACSCardElementTypeContainer;
    case AdaptiveCards::CardElementType::Custom:
      return ACSCardElementType::ACSCardElementTypeCustom;
    case AdaptiveCards::CardElementType::DateInput:
      return ACSCardElementType::ACSCardElementTypeDateInput;
    case AdaptiveCards::CardElementType::Fact:
      return ACSCardElementType::ACSCardElementTypeFact;
    case AdaptiveCards::CardElementType::FactSet:
      return ACSCardElementType::ACSCardElementTypeFactSet;
    case AdaptiveCards::CardElementType::Image:
      return ACSCardElementType::ACSCardElementTypeImage;
    case AdaptiveCards::CardElementType::ImageSet:
      return ACSCardElementType::ACSCardElementTypeImageSet;
    case AdaptiveCards::CardElementType::Media:
      return ACSCardElementType::ACSCardElementTypeMedia;
    case AdaptiveCards::CardElementType::NumberInput:
      return ACSCardElementType::ACSCardElementTypeNumberInput;
    case AdaptiveCards::CardElementType::RichTextBlock:
      return ACSCardElementType::ACSCardElementTypeRichTextBlock;
    case AdaptiveCards::CardElementType::TextBlock:
      return ACSCardElementType::ACSCardElementTypeTextBlock;
    case AdaptiveCards::CardElementType::TextInput:
      return ACSCardElementType::ACSCardElementTypeTextInput;
    case AdaptiveCards::CardElementType::TimeInput:
      return ACSCardElementType::ACSCardElementTypeTimeInput;
    case AdaptiveCards::CardElementType::ToggleInput:
      return ACSCardElementType::ACSCardElementTypeToggleInput;
    case AdaptiveCards::CardElementType::Unknown:
      return ACSCardElementType::ACSCardElementTypeUnknown;
  }
}


+(AdaptiveCards::CardElementType) convertObj:(enum ACSCardElementType) cardElementTypeObjc
{
  switch(cardElementTypeObjc)
  {
    case ACSCardElementType::ACSCardElementTypeActionSet:
      return AdaptiveCards::CardElementType::ActionSet;
    case ACSCardElementType::ACSCardElementTypeAdaptiveCard:
      return AdaptiveCards::CardElementType::AdaptiveCard;
    case ACSCardElementType::ACSCardElementTypeChoiceInput:
      return AdaptiveCards::CardElementType::ChoiceInput;
    case ACSCardElementType::ACSCardElementTypeChoiceSetInput:
      return AdaptiveCards::CardElementType::ChoiceSetInput;
    case ACSCardElementType::ACSCardElementTypeColumn:
      return AdaptiveCards::CardElementType::Column;
    case ACSCardElementType::ACSCardElementTypeColumnSet:
      return AdaptiveCards::CardElementType::ColumnSet;
    case ACSCardElementType::ACSCardElementTypeContainer:
      return AdaptiveCards::CardElementType::Container;
    case ACSCardElementType::ACSCardElementTypeCustom:
      return AdaptiveCards::CardElementType::Custom;
    case ACSCardElementType::ACSCardElementTypeDateInput:
      return AdaptiveCards::CardElementType::DateInput;
    case ACSCardElementType::ACSCardElementTypeFact:
      return AdaptiveCards::CardElementType::Fact;
    case ACSCardElementType::ACSCardElementTypeFactSet:
      return AdaptiveCards::CardElementType::FactSet;
    case ACSCardElementType::ACSCardElementTypeImage:
      return AdaptiveCards::CardElementType::Image;
    case ACSCardElementType::ACSCardElementTypeImageSet:
      return AdaptiveCards::CardElementType::ImageSet;
    case ACSCardElementType::ACSCardElementTypeMedia:
      return AdaptiveCards::CardElementType::Media;
    case ACSCardElementType::ACSCardElementTypeNumberInput:
      return AdaptiveCards::CardElementType::NumberInput;
    case ACSCardElementType::ACSCardElementTypeRichTextBlock:
      return AdaptiveCards::CardElementType::RichTextBlock;
    case ACSCardElementType::ACSCardElementTypeTextBlock:
      return AdaptiveCards::CardElementType::TextBlock;
    case ACSCardElementType::ACSCardElementTypeTextInput:
      return AdaptiveCards::CardElementType::TextInput;
    case ACSCardElementType::ACSCardElementTypeTimeInput:
      return AdaptiveCards::CardElementType::TimeInput;
    case ACSCardElementType::ACSCardElementTypeToggleInput:
      return AdaptiveCards::CardElementType::ToggleInput;
    case ACSCardElementType::ACSCardElementTypeUnknown:
      return AdaptiveCards::CardElementType::Unknown;
  }
}

@end
