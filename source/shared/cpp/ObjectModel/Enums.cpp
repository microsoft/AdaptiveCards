#include "Enums.h"

namespace AdaptiveCards
{
static std::unordered_map<AdaptiveCardSchemaKey, std::string, EnumHash> AdaptiveCardSchemaKeyEnumToName =
{
    { AdaptiveCardSchemaKey::Accent, "accent" },
    { AdaptiveCardSchemaKey::ActionAlignment, "actionAlignment" },
    { AdaptiveCardSchemaKey::ActionMode, "actionMode" },
    { AdaptiveCardSchemaKey::Actions, "actions" },
    { AdaptiveCardSchemaKey::ActionSetConfig, "actionSetConfig" },
    { AdaptiveCardSchemaKey::ActionsOrientation, "actionsOrientation" },
    { AdaptiveCardSchemaKey::AdaptiveCard, "adaptiveCard" },
    { AdaptiveCardSchemaKey::AllowCustomStyle, "allowCustomStyle" },
    { AdaptiveCardSchemaKey::AltText, "altText" },
    { AdaptiveCardSchemaKey::Attention, "attention" },
    { AdaptiveCardSchemaKey::BackgroundColor, "backgroundColor" },
    { AdaptiveCardSchemaKey::BackgroundImage, "backgroundImage" },
    { AdaptiveCardSchemaKey::BackgroundImageUrl, "backgroundImageUrl" },
    { AdaptiveCardSchemaKey::BaseCardElement, "baseCardElement" },
    { AdaptiveCardSchemaKey::Body, "body" },
    { AdaptiveCardSchemaKey::Bolder, "bolder" },
    { AdaptiveCardSchemaKey::BorderColor, "borderColor" },
    { AdaptiveCardSchemaKey::BorderThickness, "borderThickness" },
    { AdaptiveCardSchemaKey::Bottom, "bottom" },
    { AdaptiveCardSchemaKey::ButtonSpacing, "buttonSpacing" },
    { AdaptiveCardSchemaKey::Card, "card" },
    { AdaptiveCardSchemaKey::Center, "center" },
    { AdaptiveCardSchemaKey::Choices, "choices" },
    { AdaptiveCardSchemaKey::ChoiceSet, "choiceSet" },
    { AdaptiveCardSchemaKey::Color, "color" },
    { AdaptiveCardSchemaKey::ColorConfig, "colorConfig" },
    { AdaptiveCardSchemaKey::ForegroundColors, "foregroundColors" },
    { AdaptiveCardSchemaKey::Column, "column" },
    { AdaptiveCardSchemaKey::Columns, "columns" },
    { AdaptiveCardSchemaKey::ColumnSet, "columnSet" },
    { AdaptiveCardSchemaKey::Container, "container" },
    { AdaptiveCardSchemaKey::Dark, "dark" },
    { AdaptiveCardSchemaKey::Data, "data"},
    { AdaptiveCardSchemaKey::DateInput, "dateInput" },
    { AdaptiveCardSchemaKey::Default, "default" },
    { AdaptiveCardSchemaKey::Emphasis, "emphasis" },
    { AdaptiveCardSchemaKey::ExtraLarge, "extraLarge" },
    { AdaptiveCardSchemaKey::Facts, "facts" },
    { AdaptiveCardSchemaKey::FactSet, "factSet" },
    { AdaptiveCardSchemaKey::FallbackText, "fallbackText" },
    { AdaptiveCardSchemaKey::FontFamily, "fontFamily" },
    { AdaptiveCardSchemaKey::FontSizes, "fontSizes" },
    { AdaptiveCardSchemaKey::Good, "good" },
    { AdaptiveCardSchemaKey::HorizontalAlignment, "horizontalAlignment" },
    { AdaptiveCardSchemaKey::Id, "id" },
    { AdaptiveCardSchemaKey::Image, "image" },
    { AdaptiveCardSchemaKey::Images, "images" },
    { AdaptiveCardSchemaKey::ImageSet, "imageSet" },
    { AdaptiveCardSchemaKey::ImageSize, "imageSize" },
    { AdaptiveCardSchemaKey::ImageSizes, "imageSizes" },
    { AdaptiveCardSchemaKey::InlineTopMargin, "inlineTopMargin" },
    { AdaptiveCardSchemaKey::IsMultiline, "isMultiline" },
    { AdaptiveCardSchemaKey::IsMultiSelect, "isMultiSelect" },
    { AdaptiveCardSchemaKey::IsRequired, "isRequired" },
    { AdaptiveCardSchemaKey::IsSelected, "isSelected"},
    { AdaptiveCardSchemaKey::IsSubtle, "isSubtle" },
    { AdaptiveCardSchemaKey::Items, "items" },
    { AdaptiveCardSchemaKey::Large, "large" },
    { AdaptiveCardSchemaKey::Left, "left" },
    { AdaptiveCardSchemaKey::Light, "light" },
    { AdaptiveCardSchemaKey::Lighter, "lighter" },
    { AdaptiveCardSchemaKey::LineColor, "lineColor" },
    { AdaptiveCardSchemaKey::LineThickness, "lineThickness" },
    { AdaptiveCardSchemaKey::Max, "max" },
    { AdaptiveCardSchemaKey::MaxActions, "maxActions" },
    { AdaptiveCardSchemaKey::MaxLength, "maxLength" },
    { AdaptiveCardSchemaKey::MaxLines, "maxLines" },
    { AdaptiveCardSchemaKey::MaxWidth, "maxWidth" },
    { AdaptiveCardSchemaKey::Medium, "medium" },
    { AdaptiveCardSchemaKey::Method, "method" },
    { AdaptiveCardSchemaKey::Min, "min" },
    { AdaptiveCardSchemaKey::MinVersion, "minVersion" },
    { AdaptiveCardSchemaKey::NumberInput, "numberInput" },
    { AdaptiveCardSchemaKey::Padding, "padding" },
    { AdaptiveCardSchemaKey::Placeholder, "placeholder" },
    { AdaptiveCardSchemaKey::Right, "right" },
    { AdaptiveCardSchemaKey::SelectAction, "selectAction" },
    { AdaptiveCardSchemaKey::Separator, "separator" },
    { AdaptiveCardSchemaKey::Thickness, "thickness" },
    { AdaptiveCardSchemaKey::ShowActionMode, "showActionMode" },
    { AdaptiveCardSchemaKey::ShowCard, "showCard" },
    { AdaptiveCardSchemaKey::ShowCardActionConfig, "showCardActionConfig" },
    { AdaptiveCardSchemaKey::Size, "size" },
    { AdaptiveCardSchemaKey::Small, "small" },
    { AdaptiveCardSchemaKey::Spacing, "spacing" },
    { AdaptiveCardSchemaKey::SpacingDefinition, "spacingDefinition" },
    { AdaptiveCardSchemaKey::Speak, "speak" },
    { AdaptiveCardSchemaKey::Stretch, "stretch" },
    { AdaptiveCardSchemaKey::Style, "style" },
    { AdaptiveCardSchemaKey::Subtle, "subtle" },
    { AdaptiveCardSchemaKey::SupportsInteractivity, "supportsInteractivity" },
    { AdaptiveCardSchemaKey::Text, "text" },
    { AdaptiveCardSchemaKey::TextBlock, "textBlock" },
    { AdaptiveCardSchemaKey::TextConfig, "textConfig" },
    { AdaptiveCardSchemaKey::TextInput, "textInput" },
    { AdaptiveCardSchemaKey::TextWeight, "weight" },
    { AdaptiveCardSchemaKey::Thick, "thick" },
    { AdaptiveCardSchemaKey::Thickness, "thickness" },
    { AdaptiveCardSchemaKey::TimeInput, "timeInput" },
    { AdaptiveCardSchemaKey::Title, "title" },
    { AdaptiveCardSchemaKey::ToggleInput, "toggleInput" },
    { AdaptiveCardSchemaKey::Top, "top" },
    { AdaptiveCardSchemaKey::Type, "type" },
    { AdaptiveCardSchemaKey::Url, "url" },
    { AdaptiveCardSchemaKey::Value, "value" },
    { AdaptiveCardSchemaKey::ValueOff, "valueOff" },
    { AdaptiveCardSchemaKey::ValueOn, "valueOn" },
    { AdaptiveCardSchemaKey::Version, "version" },
    { AdaptiveCardSchemaKey::Warning, "warning" },
    { AdaptiveCardSchemaKey::Weight, "weight" },
    { AdaptiveCardSchemaKey::Width, "width" },
    { AdaptiveCardSchemaKey::Wrap, "wrap" },
};

static std::unordered_map<std::string, AdaptiveCardSchemaKey, CaseInsensitiveHash, CaseInsensitiveEqualTo> 
AdaptiveCardSchemaKeyNameToEnum = GenerateStringToEnumMap<AdaptiveCardSchemaKey>(AdaptiveCardSchemaKeyEnumToName);

static std::unordered_map<CardElementType, std::string, EnumHash> CardElementTypeEnumToName =
{
    { CardElementType::AdaptiveCard, "AdaptiveCard" },
    { CardElementType::Column, "Column" },
    { CardElementType::ColumnSet, "ColumnSet"},
    { CardElementType::Container, "Container" },
    { CardElementType::Fact, "Fact" },
    { CardElementType::FactSet, "FactSet" },
    { CardElementType::Image, "Image" },
    { CardElementType::ImageSet, "ImageSet" },
    { CardElementType::ChoiceSetInput, "Input.ChoiceSet" },
    { CardElementType::DateInput, "Input.Date" },
    { CardElementType::NumberInput, "Input.Number" },
    { CardElementType::TextInput, "Input.Text" },
    { CardElementType::TimeInput, "Input.Time" },
    { CardElementType::ToggleInput, "Input.Toggle" },
    { CardElementType::TextBlock, "TextBlock" },
};

static std::unordered_map<std::string, CardElementType, CaseInsensitiveHash, CaseInsensitiveEqualTo> 
CardElementTypeNameToEnum = GenerateStringToEnumMap<CardElementType>(CardElementTypeEnumToName);

static std::unordered_map<ActionType, std::string, EnumHash> ActionTypeEnumToName =
{
    { ActionType::OpenUrl, "Action.OpenUrl" },
    { ActionType::ShowCard, "Action.ShowCard" },
    { ActionType::Submit, "Action.Submit" }
};

static std::unordered_map<std::string, ActionType, CaseInsensitiveHash, CaseInsensitiveEqualTo>
ActionTypeNameToEnum = GenerateStringToEnumMap<ActionType>(ActionTypeEnumToName);

static std::unordered_map<Spacing, std::string, EnumHash> SpacingEnumToName =
{
    { Spacing::Default, "default" },
    { Spacing::None, "none" },
    { Spacing::Small, "small" },
    { Spacing::Medium, "medium" },
    { Spacing::Large, "large" },
    { Spacing::ExtraLarge, "extraLarge" },
};

static std::unordered_map<std::string, Spacing, CaseInsensitiveHash, CaseInsensitiveEqualTo>
SpacingNameToEnum = GenerateStringToEnumMap<Spacing>(SpacingEnumToName);

static std::unordered_map<SeparatorThickness, std::string, EnumHash> SeparatorThicknessEnumToName =
{
    { SeparatorThickness::Default, "default" },
    { SeparatorThickness::Thick, "thick" },
};

static std::unordered_map<std::string, SeparatorThickness, CaseInsensitiveHash, CaseInsensitiveEqualTo>
SeparatorThicknessNameToEnum = GenerateStringToEnumMap<SeparatorThickness>(SeparatorThicknessEnumToName);

static std::unordered_map<ImageStyle, std::string, EnumHash> ImageStyleEnumToName =
{
    {ImageStyle::Default, "default"},
    {ImageStyle::Person, "person"}
};

static std::unordered_map<std::string, ImageStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> ImageStyleNameToEnum = 
{
    { "default", ImageStyle::Default},
    { "person", ImageStyle::Person},
    { "normal", ImageStyle::Default} // Back compat to support "Normal" for "Default" for pre V1.0 payloads
};

static std::unordered_map<ImageSize, std::string, EnumHash> ImageSizeEnumToName =
{
    { ImageSize::Auto, "Auto" },
    { ImageSize::Large, "Large" },
    { ImageSize::Medium, "Medium" },
    { ImageSize::Small, "Small" },
    { ImageSize::Stretch, "Stretch" },
};

static std::unordered_map<std::string, ImageSize, CaseInsensitiveHash, CaseInsensitiveEqualTo>
ImageSizeNameToEnum = GenerateStringToEnumMap<ImageSize>(ImageSizeEnumToName);

static std::unordered_map<HorizontalAlignment, std::string, EnumHash> HorizontalAlignmentEnumToName = 
{
    {HorizontalAlignment::Center, "Center"},
    {HorizontalAlignment::Left, "Left"},
    {HorizontalAlignment::Right, "Right"}
};

static std::unordered_map<std::string, HorizontalAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo>
HorizontalAlignmentNameToEnum = GenerateStringToEnumMap<HorizontalAlignment>(HorizontalAlignmentEnumToName);

static std::unordered_map<ForegroundColor, std::string, EnumHash> ColorEnumToName =
{
    {ForegroundColor::Accent, "Accent"},
    {ForegroundColor::Attention, "Attention"},
    {ForegroundColor::Dark, "Dark" },
    {ForegroundColor::Default, "Default"},
    {ForegroundColor::Good, "Good"},
    {ForegroundColor::Light, "Light" },
    {ForegroundColor::Warning, "Warning"},
};

static std::unordered_map<std::string, ForegroundColor, CaseInsensitiveHash, CaseInsensitiveEqualTo>
ColorNameToEnum = GenerateStringToEnumMap<ForegroundColor>(ColorEnumToName);

static std::unordered_map<TextWeight, std::string, EnumHash> TextWeightEnumToName =
{
    {TextWeight::Bolder, "Bolder"},
    {TextWeight::Lighter, "Lighter"},
    {TextWeight::Default, "Default"},
};

static std::unordered_map<std::string, TextWeight, CaseInsensitiveHash, CaseInsensitiveEqualTo> TextWeightNameToEnum = 
{
    { "Bolder", TextWeight::Bolder},
    { "Lighter", TextWeight::Lighter},
    { "Default", TextWeight::Default},
    { "Normal", TextWeight::Default }, // Back compat to support "Normal" for "Default" for pre V1.0 payloads
};

static std::unordered_map<TextSize, std::string, EnumHash> TextSizeEnumToName =
{
    {TextSize::ExtraLarge, "ExtraLarge"},
    {TextSize::Large, "Large"},
    {TextSize::Medium, "Medium"},
    {TextSize::Default, "Default"},
    {TextSize::Small, "Small"},
};

static std::unordered_map<std::string, TextSize, CaseInsensitiveHash, CaseInsensitiveEqualTo> TextSizeNameToEnum = 
{
    { "ExtraLarge", TextSize::ExtraLarge },
    { "Large", TextSize::Large },
    { "Medium", TextSize::Medium },
    { "Default", TextSize::Default },
    { "Small", TextSize::Small },
    { "Normal", TextSize::Default }, // Back compat to support "Normal" for "Default" for pre V1.0 payloads
};

static std::unordered_map<ActionsOrientation, std::string, EnumHash> ActionsOrientationEnumToName =
{
    { ActionsOrientation::Horizontal, "Horizontal" },
    { ActionsOrientation::Vertical, "Vertical" },
};

static std::unordered_map<std::string, ActionsOrientation, CaseInsensitiveHash, CaseInsensitiveEqualTo>
ActionsOrientationNameToEnum = GenerateStringToEnumMap<ActionsOrientation>(ActionsOrientationEnumToName);

static std::unordered_map<ActionMode, std::string, EnumHash> ActionModeEnumToName =
{
    { ActionMode::Inline, "Inline" },
    { ActionMode::Popup, "Popup" }
};

static std::unordered_map<std::string, ActionMode, CaseInsensitiveHash, CaseInsensitiveEqualTo>
ActionModeNameToEnum = GenerateStringToEnumMap<ActionMode>(ActionModeEnumToName);

static std::unordered_map<ChoiceSetStyle, std::string, EnumHash> ChoiceSetStyleEnumToName =
{
    { ChoiceSetStyle::Compact, "Compact" },
    { ChoiceSetStyle::Expanded, "Expanded" }
};

static std::unordered_map<std::string, ChoiceSetStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo>
ChoiceSetStyleNameToEnum = GenerateStringToEnumMap<ChoiceSetStyle>(ChoiceSetStyleEnumToName);

static std::unordered_map<TextInputStyle, std::string, EnumHash> TextInputStyleEnumToName =
{
    { TextInputStyle::Email, "Email" },
    { TextInputStyle::Tel, "Tel" },
    { TextInputStyle::Text, "Text" },
    { TextInputStyle::Url, "Url" },
};

static std::unordered_map<std::string, TextInputStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo>
TextInputStyleNameToEnum = GenerateStringToEnumMap<TextInputStyle>(TextInputStyleEnumToName);

static std::unordered_map<ContainerStyle, std::string, EnumHash> ContainerStyleEnumToName =
{
    { ContainerStyle::Default, "Default" },
    { ContainerStyle::Emphasis, "Emphasis" },
};

static std::unordered_map<std::string, ContainerStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo>
ContainerStyleNameToEnum = GenerateStringToEnumMap<ContainerStyle>(ContainerStyleEnumToName);

static std::unordered_map<ActionAlignment, std::string, EnumHash> ActionAlignmentEnumToName =
{
    { ActionAlignment::Left, "Left" },
    { ActionAlignment::Center, "Center" },
    { ActionAlignment::Right, "Right" },
    { ActionAlignment::Stretch, "Stretch" },
};

static std::unordered_map<std::string, ActionAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo>
ActionAlignmentNameToEnum = GenerateStringToEnumMap<ActionAlignment>(ActionAlignmentEnumToName);

const std::string AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey type)
{
    if (AdaptiveCardSchemaKeyEnumToName.find(type) == AdaptiveCardSchemaKeyEnumToName.end())
    {
        throw std::out_of_range("Invalid AdaptiveCardSchemaKeys");
    }

    return AdaptiveCardSchemaKeyEnumToName[type];
}

AdaptiveCardSchemaKey AdaptiveCardSchemaKeyFromString(const std::string& type)
{
    if (AdaptiveCardSchemaKeyNameToEnum.find(type) == AdaptiveCardSchemaKeyNameToEnum.end())
    {
        throw std::out_of_range("Invalid AdaptiveCardSchemaKey: " + type);
    }

    return AdaptiveCardSchemaKeyNameToEnum[type];
}

const std::string CardElementTypeToString(CardElementType elementType)
{
    if (CardElementTypeEnumToName.find(elementType) == CardElementTypeEnumToName.end())
    {
        throw std::out_of_range("Invalid CardElementType");
    }

    return CardElementTypeEnumToName[elementType];
}

CardElementType CardElementTypeFromString(const std::string& elementType)
{
    if (CardElementTypeNameToEnum.find(elementType) == CardElementTypeNameToEnum.end())
    {
        throw std::out_of_range("Invalid CardElementType: " + elementType);
    }

    return CardElementTypeNameToEnum[elementType];
}

const std::string ActionTypeToString(ActionType actionType)
{
    if (ActionTypeEnumToName.find(actionType) == ActionTypeEnumToName.end())
    {
        throw std::out_of_range("Invalid ActionType");
    }

    return ActionTypeEnumToName[actionType];
}

ActionType ActionTypeFromString(const std::string& actionType)
{
    if (ActionTypeNameToEnum.find(actionType) == ActionTypeNameToEnum.end())
    {
        throw std::out_of_range("Invalid ActionType: " + actionType);
    }

    return ActionTypeNameToEnum[actionType];
}

const std::string HorizontalAlignmentToString(HorizontalAlignment alignment)
{
    if (HorizontalAlignmentEnumToName.find(alignment) == HorizontalAlignmentEnumToName.end())
    {
        throw std::out_of_range("Invalid HorizontalAlignment type");
    }
    return HorizontalAlignmentEnumToName[alignment];
}

HorizontalAlignment HorizontalAlignmentFromString(const std::string& alignment)
{
    if (HorizontalAlignmentNameToEnum.find(alignment) == HorizontalAlignmentNameToEnum.end())
    {
        throw std::out_of_range("Invalid HorizontalAlignment: " + alignment);
    }

    return HorizontalAlignmentNameToEnum[alignment];
}

const std::string ForegroundColorToString(ForegroundColor color)
{
    if (ColorEnumToName.find(color) == ColorEnumToName.end())
    {
        throw std::out_of_range("Invalid ForegroundColor type");
    }
    return ColorEnumToName[color];
}

ForegroundColor ForegroundColorFromString(const std::string& color)
{
    if (ColorNameToEnum.find(color) == ColorNameToEnum.end())
    {
        throw std::out_of_range("Invalid ForegroundColor: " + color);
    }

    return ColorNameToEnum[color];
}

const std::string TextWeightToString(TextWeight weight)
{
    if (TextWeightEnumToName.find(weight) == TextWeightEnumToName.end())
    {
        throw std::out_of_range("Invalid TextWeight type");
    }
    return TextWeightEnumToName[weight];
}

TextWeight TextWeightFromString(const std::string& weight)
{
    if (TextWeightNameToEnum.find(weight) == TextWeightNameToEnum.end())
    {
        throw std::out_of_range("Invalid TextWeight: " + weight);
    }

    return TextWeightNameToEnum[weight];
}

const std::string TextSizeToString(TextSize size)
{
    if (TextSizeEnumToName.find(size) == TextSizeEnumToName.end())
    {
        throw std::out_of_range("Invalid TextSize type");
    }
    return TextSizeEnumToName[size];
}

TextSize TextSizeFromString(const std::string& size)
{
    if (TextSizeNameToEnum.find(size) == TextSizeNameToEnum.end())
    {
        throw std::out_of_range("Invalid TextSize: " + size);
    }

    return TextSizeNameToEnum[size];
}

const std::string ImageSizeToString(ImageSize size)
{
    if (ImageSizeEnumToName.find(size) == ImageSizeEnumToName.end())
    {
        throw std::out_of_range("Invalid ImageSize type");
    }
    return ImageSizeEnumToName[size];
}

ImageSize ImageSizeFromString(const std::string& size)
{
    if (ImageSizeNameToEnum.find(size) == ImageSizeNameToEnum.end())
    {
        throw std::out_of_range("Invalid ImageSize: " + size);
    }

    return ImageSizeNameToEnum[size];
}

const std::string SpacingToString(Spacing spacing)
{
    if (SpacingEnumToName.find(spacing) == SpacingEnumToName.end())
    {
        throw std::out_of_range("Invalid Spacing type");
    }
    return SpacingEnumToName[spacing];
}

Spacing SpacingFromString(const std::string& spacing)
{
    if (SpacingNameToEnum.find(spacing) == SpacingNameToEnum.end())
    {
        throw std::out_of_range("Invalid Spacing: " + spacing);
    }

    return SpacingNameToEnum[spacing];
}

const std::string SeparatorThicknessToString(SeparatorThickness thickness)
{
    if (SeparatorThicknessEnumToName.find(thickness) == SeparatorThicknessEnumToName.end())
    {
        throw std::out_of_range("Invalid SeparatorThickness type");
    }
    return SeparatorThicknessEnumToName[thickness];
}

SeparatorThickness SeparatorThicknessFromString(const std::string& thickness)
{
    if (SeparatorThicknessNameToEnum.find(thickness) == SeparatorThicknessNameToEnum.end())
    {
        throw std::out_of_range("Invalid SeparatorThickness: " + thickness);
    }

    return SeparatorThicknessNameToEnum[thickness];
}

const std::string ImageStyleToString(ImageStyle style)
{
    if (ImageStyleEnumToName.find(style) == ImageStyleEnumToName.end())
    {
        throw std::out_of_range("Invalid ImageStyle style");
    }
    return ImageStyleEnumToName[style];
}

ImageStyle ImageStyleFromString(const std::string& style)
{
    if (ImageStyleNameToEnum.find(style) == ImageStyleNameToEnum.end())
    {
        throw std::out_of_range("Invalid ImageStyle: " + style);
    }

    return ImageStyleNameToEnum[style];
}

const std::string ActionsOrientationToString(ActionsOrientation orientation)
{
    if (ActionsOrientationEnumToName.find(orientation) == ActionsOrientationEnumToName.end())
    {
        throw std::out_of_range("Invalid ActionsOrientation type");
    }
    return ActionsOrientationEnumToName[orientation];
}

ActionsOrientation ActionsOrientationFromString(const std::string& orientation)
{
    if (ActionsOrientationNameToEnum.find(orientation) == ActionsOrientationNameToEnum.end())
    {
        throw std::out_of_range("Invalid ActionsOrientation: " + orientation);
    }
    return ActionsOrientationNameToEnum[orientation];
}

const std::string ActionModeToString(ActionMode mode)
{
    if (ActionModeEnumToName.find(mode) == ActionModeEnumToName.end())
    {
        throw std::out_of_range("Invalid ActionMode type");
    }
    return ActionModeEnumToName[mode];
}

ActionMode ActionModeFromString(const std::string& mode)
{
    if (ActionModeNameToEnum.find(mode) == ActionModeNameToEnum.end())
    {
        throw std::out_of_range("Invalid ActionMode: " + mode);
    }
    return ActionModeNameToEnum[mode];
}
const std::string ChoiceSetStyleToString(ChoiceSetStyle style)
{
    if (ChoiceSetStyleEnumToName.find(style) == ChoiceSetStyleEnumToName.end())
    {
        throw std::out_of_range("Invalid ChoiceSetStyle");
    }
    return ChoiceSetStyleEnumToName[style];
}
ChoiceSetStyle ChoiceSetStyleFromString(const std::string & style)
{
    if (ChoiceSetStyleNameToEnum.find(style) == ChoiceSetStyleNameToEnum.end())
    {
        throw std::out_of_range("Invalid ChoiceSetStyle: " + style);
    }
    return ChoiceSetStyleNameToEnum[style];
}

const std::string TextInputStyleToString(TextInputStyle style)
{
    if (TextInputStyleEnumToName.find(style) == TextInputStyleEnumToName.end())
    {
        throw std::out_of_range("Invalid TextInputStyle");
    }
    return TextInputStyleEnumToName[style];
}
TextInputStyle TextInputStyleFromString(const std::string & style)
{
    if (TextInputStyleNameToEnum.find(style) == TextInputStyleNameToEnum.end())
    {
        throw std::out_of_range("Invalid TextInputStyle: " + style);
    }
    return TextInputStyleNameToEnum[style];
}

const std::string ContainerStyleToString(ContainerStyle style)
{
    if (ContainerStyleEnumToName.find(style) == ContainerStyleEnumToName.end())
    {
        throw std::out_of_range("Invalid ContainerStyle");
    }
    return ContainerStyleEnumToName[style];
}
ContainerStyle ContainerStyleFromString(const std::string & style)
{
    if (ContainerStyleNameToEnum.find(style) == ContainerStyleNameToEnum.end())
    {
        throw std::out_of_range("Invalid ContainerStyle: " + style);
    }
    return ContainerStyleNameToEnum[style];
}

const std::string ActionAlignmentToString(ActionAlignment alignment)
{
    if (ActionAlignmentEnumToName.find(alignment) == ActionAlignmentEnumToName.end())
    {
        throw std::out_of_range("Invalid ActionAlignment");
    }
    return ActionAlignmentEnumToName[alignment];
}
ActionAlignment ActionAlignmentFromString(const std::string & alignment)
{
    if (ActionAlignmentNameToEnum.find(alignment) == ActionAlignmentNameToEnum.end())
    {
        throw std::out_of_range("Invalid ActionAlignment: " + alignment);
    }
    return ActionAlignmentNameToEnum[alignment];
}
}
