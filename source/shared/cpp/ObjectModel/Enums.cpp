#include "Enums.h"

namespace AdaptiveCards
{
static std::unordered_map<std::string, AdaptiveCardSchemaKey, CaseInsensitiveHash, CaseInsensitiveEqualTo> AdaptiveCardSchemaKeyNameToEnum =
{
    { "type", AdaptiveCardSchemaKey::Type },
    { "body", AdaptiveCardSchemaKey::Body },
    { "version", AdaptiveCardSchemaKey::Version },
    { "minVersion", AdaptiveCardSchemaKey::MinVersion },
    { "fallbackText", AdaptiveCardSchemaKey::FallbackText },
    { "baseCardElement", AdaptiveCardSchemaKey::BaseCardElement },
    { "separation", AdaptiveCardSchemaKey::Separation },
    { "speak", AdaptiveCardSchemaKey::Speak },
    { "type", AdaptiveCardSchemaKey::Type },
    { "url", AdaptiveCardSchemaKey::Url },
    { "style", AdaptiveCardSchemaKey::ImageStyle },
    { "imageSize", AdaptiveCardSchemaKey::ImageSize },
    { "altText", AdaptiveCardSchemaKey::AltText },
    { "horizontalAlignment", AdaptiveCardSchemaKey::HorizontalAlignment },
    { "text", AdaptiveCardSchemaKey::Text },
    { "size", AdaptiveCardSchemaKey::TextSize },
    { "weight", AdaptiveCardSchemaKey::TextWeight },
    { "color", AdaptiveCardSchemaKey::TextColor },
    { "isSubtle", AdaptiveCardSchemaKey::IsSubtle },
    { "wrap", AdaptiveCardSchemaKey::Wrap },
    { "maxLines", AdaptiveCardSchemaKey::MaxLines },
    { "items", AdaptiveCardSchemaKey::Items },
    { "columns", AdaptiveCardSchemaKey::Columns },
    { "size", AdaptiveCardSchemaKey::Size },
    { "facts", AdaptiveCardSchemaKey::Facts },
    { "title", AdaptiveCardSchemaKey::Title },
    { "value", AdaptiveCardSchemaKey::Value },
    { "images", AdaptiveCardSchemaKey::Images },
    { "placeholder", AdaptiveCardSchemaKey::Placeholder },
    { "isMultiline", AdaptiveCardSchemaKey::IsMultiline },
    { "maxLength", AdaptiveCardSchemaKey::MaxLength },
    { "valueOff", AdaptiveCardSchemaKey::ValueOff },
    { "valueOn", AdaptiveCardSchemaKey::ValueOn },
    { "max", AdaptiveCardSchemaKey::Max },
    { "min", AdaptiveCardSchemaKey::Min },
    { "choices", AdaptiveCardSchemaKey::Choices },
    { "isSelected", AdaptiveCardSchemaKey::IsSelected },
    { "style", AdaptiveCardSchemaKey::Style },
    { "isMultiSelect", AdaptiveCardSchemaKey::IsMultiSelect },
    { "isRequired", AdaptiveCardSchemaKey::IsRequired },
    { "backgroundImageUrl", AdaptiveCardSchemaKey::BackgroundImageUrl},
    { "actions", AdaptiveCardSchemaKey::Actions },
    { "method", AdaptiveCardSchemaKey::Method },
    { "card", AdaptiveCardSchemaKey::Card },
    { "style", AdaptiveCardSchemaKey::ContainerStyle },
};

static std::unordered_map<AdaptiveCardSchemaKey, std::string, EnumHash> AdaptiveCardSchemaKeyEnumToName =
{
    { AdaptiveCardSchemaKey::Type, "type" },
    { AdaptiveCardSchemaKey::Body, "body" },
    { AdaptiveCardSchemaKey::Version, "version" },
    { AdaptiveCardSchemaKey::MinVersion, "minVersion" },
    { AdaptiveCardSchemaKey::FallbackText, "fallbackText" },
    { AdaptiveCardSchemaKey::BaseCardElement, "baseCardElement" },
    { AdaptiveCardSchemaKey::Separation, "separation" },
    { AdaptiveCardSchemaKey::Speak, "speak" },
    { AdaptiveCardSchemaKey::Type, "type" },
    { AdaptiveCardSchemaKey::Url, "url" },
    { AdaptiveCardSchemaKey::ImageStyle, "style" },
    { AdaptiveCardSchemaKey::ImageSize, "imageSize" },
    { AdaptiveCardSchemaKey::AltText, "altText" },
    { AdaptiveCardSchemaKey::HorizontalAlignment, "horizontalAlignment" },
    { AdaptiveCardSchemaKey::Text, "text" },
    { AdaptiveCardSchemaKey::TextSize, "size" },
    { AdaptiveCardSchemaKey::TextWeight, "weight" },
    { AdaptiveCardSchemaKey::TextColor, "color" },
    { AdaptiveCardSchemaKey::IsSubtle, "isSubtle" },
    { AdaptiveCardSchemaKey::Wrap, "wrap" },
    { AdaptiveCardSchemaKey::MaxLines, "maxLines" },
    { AdaptiveCardSchemaKey::Items, "items" },
    { AdaptiveCardSchemaKey::Columns, "columns" },
    { AdaptiveCardSchemaKey::Size, "size" },
    { AdaptiveCardSchemaKey::Facts, "facts" },
    { AdaptiveCardSchemaKey::Title, "title" },
    { AdaptiveCardSchemaKey::Value, "value" },
    { AdaptiveCardSchemaKey::Images, "images" },
    { AdaptiveCardSchemaKey::Placeholder, "placeholder" },
    { AdaptiveCardSchemaKey::IsMultiline, "isMultiline" },
    { AdaptiveCardSchemaKey::MaxLength, "maxLength" },
    { AdaptiveCardSchemaKey::ValueOff, "valueOff" },
    { AdaptiveCardSchemaKey::ValueOn, "valueOn" },
    { AdaptiveCardSchemaKey::Max, "max" },
    { AdaptiveCardSchemaKey::Min, "min" },
    { AdaptiveCardSchemaKey::Choices, "choices" },
    { AdaptiveCardSchemaKey::IsSelected, "isSelected"},
    { AdaptiveCardSchemaKey::Style, "style"},
    { AdaptiveCardSchemaKey::IsMultiSelect, "isMultiSelect" },
    { AdaptiveCardSchemaKey::IsRequired, "isRequired" },
    { AdaptiveCardSchemaKey::BackgroundImageUrl, "backgroundImageUrl" },
    { AdaptiveCardSchemaKey::Actions, "actions" },
    { AdaptiveCardSchemaKey::Method, "method" },
    { AdaptiveCardSchemaKey::Card, "card" },
    { AdaptiveCardSchemaKey::ContainerStyle, "style" },
};

static std::unordered_map<std::string, CardElementType, CaseInsensitiveHash, CaseInsensitiveEqualTo> CardElementTypeNameToEnum =
{
    { "AdaptiveCard", CardElementType::AdaptiveCard },
    { "TextBlock", CardElementType::TextBlock },
    { "Image", CardElementType::Image },
    { "ColumnSet", CardElementType::ColumnSet },
    { "Column", CardElementType::Column },
    { "FactSet", CardElementType::FactSet },
    { "Fact", CardElementType::Fact },
    { "ImageSet", CardElementType::ImageSet },
    { "Container", CardElementType::Container },
    { "Input.ChoiceSet", CardElementType::InputChoiceSet },
    { "Input.Date", CardElementType::InputDate },
    { "Input.Number", CardElementType::InputNumber },
    { "Input.Text", CardElementType::InputText },
    { "Input.Time", CardElementType::InputTime},
    { "Input.Toggle", CardElementType::InputToggle },
};

static std::unordered_map<CardElementType, std::string, EnumHash> CardElementTypeEnumToName =
{
    { CardElementType::AdaptiveCard, "AdaptiveCard" },
    { CardElementType::TextBlock, "TextBlock" },
    { CardElementType::Image, "Image" },
    { CardElementType::Column, "Column" },
    { CardElementType::ColumnSet, "ColumnSet"},
    { CardElementType::FactSet, "FactSet" },
    { CardElementType::Fact, "Fact" },
    { CardElementType::ImageSet, "ImageSet" },
    { CardElementType::Container, "Container" },
    { CardElementType::InputChoiceSet, "Input.ChoiceSet" },
    { CardElementType::InputDate, "Input.Date" },
    { CardElementType::InputNumber, "Input.Number" },
    { CardElementType::InputText, "Input.Text" },
    { CardElementType::InputTime, "Input.Time" },
    { CardElementType::InputToggle, "Input.Toggle" },
};

static std::unordered_map<std::string, ActionType, CaseInsensitiveHash, CaseInsensitiveEqualTo> ActionTypeNameToEnum =
{
    { "Action.Http", ActionType::Http },
    { "Action.OpenUrl", ActionType::OpenUrl },
    { "Action.ShowCard", ActionType::ShowCard },
    { "Action.Submit", ActionType::Submit }
};

static std::unordered_map<ActionType, std::string, EnumHash> ActionTypeEnumToName =
{
    { ActionType::Http, "Action.Http" },
    { ActionType::OpenUrl, "Action.OpenUrl" },
    { ActionType::ShowCard, "Action.ShowCard" },
    { ActionType::Submit, "Action.Submit" }
};

static std::unordered_map<std::string, SeparationStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> SeparationStyleNameToEnum =
{
    { "default", SeparationStyle::Default },
    { "none", SeparationStyle::None },
    { "strong", SeparationStyle::Strong}
};

static std::unordered_map<SeparationStyle, std::string, EnumHash> SeparationStyleEnumToName =
{
    { SeparationStyle::Default, "default" },
    { SeparationStyle::None, "none" },
    { SeparationStyle::Strong, "strong" }
};

static std::unordered_map<std::string, ImageStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> ImageStyleNameToEnum =
{
    {"normal", ImageStyle::Normal},
    {"person", ImageStyle::Person}
};

static std::unordered_map<ImageStyle, std::string, EnumHash> ImageStyleEnumToName =
{
    {ImageStyle::Normal, "normal"},
    {ImageStyle::Person, "person"}
};

static std::unordered_map<std::string, ImageSize, CaseInsensitiveHash, CaseInsensitiveEqualTo> ImageSizeNameToEnum =
{
    { "Auto", ImageSize::Auto },
    { "Stretch", ImageSize::Stretch },
    { "Small", ImageSize::Small },
    { "Medium", ImageSize::Medium },
    { "Large", ImageSize::Large }
};

static std::unordered_map<ImageSize, std::string, EnumHash> ImageSizeEnumToName =
{
    { ImageSize::Auto, "Auto" },
    { ImageSize::Stretch, "Stretch" },
    { ImageSize::Small, "Small" },
    { ImageSize::Medium, "Medium" },
    { ImageSize::Large, "Large" },
    { ImageSize::Default, "Auto" },
};

static std::unordered_map<std::string, HorizontalAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo> HorizontalAlignmentNameToEnum =
{
    {"Left", HorizontalAlignment::Left},
    {"Center", HorizontalAlignment::Center},
    {"Right", HorizontalAlignment::Right}
};

static std::unordered_map<HorizontalAlignment, std::string, EnumHash> HorizontalAlignmentEnumToName =
{
    {HorizontalAlignment::Left, "Left"},
    {HorizontalAlignment::Center, "Center"},
    {HorizontalAlignment::Right, "Right"}
};

static std::unordered_map<std::string, TextColor, CaseInsensitiveHash, CaseInsensitiveEqualTo> TextColorNameToEnum =
{
    {"Default", TextColor::Default},
    {"Dark", TextColor::Dark},
    {"Light", TextColor::Light},
    {"Accent", TextColor::Accent},
    {"Good", TextColor::Good},
    {"Warning", TextColor::Warning},
    {"Attention", TextColor::Attention}
};

static std::unordered_map<TextColor, std::string, EnumHash> TextColorEnumToName =
{
    {TextColor::Default, "Default"},
    {TextColor::Dark, "Dark"},
    {TextColor::Light, "Light"},
    {TextColor::Accent, "Accent"},
    {TextColor::Good, "Good"},
    {TextColor::Warning, "Warning"},
    {TextColor::Attention, "Attention"}
};

static std::unordered_map<std::string, TextWeight, CaseInsensitiveHash, CaseInsensitiveEqualTo> TextWeightNameToEnum =
{
    {"Lighter", TextWeight::Lighter},
    {"Normal", TextWeight::Normal},
    {"Bolder", TextWeight::Bolder}
};
static std::unordered_map<TextWeight, std::string, EnumHash> TextWeightEnumToName =
{
    {TextWeight::Lighter, "Lighter"},
    {TextWeight::Normal, "Normal"},
    {TextWeight::Bolder, "Bolder"}
};

static std::unordered_map<std::string, TextSize, CaseInsensitiveHash, CaseInsensitiveEqualTo> TextSizeNameToEnum =
{
    {"Small", TextSize::Small},
    {"Normal", TextSize::Normal},
    {"Medium", TextSize::Medium},
    {"Large", TextSize::Large},
    {"ExtraLarge", TextSize::ExtraLarge}
};

static std::unordered_map<TextSize, std::string, EnumHash> TextSizeEnumToName =
{
    {TextSize::Small, "Small"},
    {TextSize::Normal, "Normal"},
    {TextSize::Medium, "Medium"},
    {TextSize::Large, "Large"},
    {TextSize::ExtraLarge, "ExtraLarge"}
};

static std::unordered_map<std::string, ActionsOrientation, CaseInsensitiveHash, CaseInsensitiveEqualTo> ActionsOrientationNameToEnum =
{
    { "Vertical", ActionsOrientation::Vertical },
    { "Horizontal", ActionsOrientation::Horizontal }
};

static std::unordered_map<ActionsOrientation, std::string, EnumHash> ActionsOrientationEnumToName =
{
    { ActionsOrientation::Vertical, "Vertical" },
    { ActionsOrientation::Horizontal, "Horizontal" }
};

static std::unordered_map<std::string, ActionMode, CaseInsensitiveHash, CaseInsensitiveEqualTo> ActionModeNameToEnum =
{
    { "Inline", ActionMode::Inline },
    { "Popup", ActionMode::Popup }
};

static std::unordered_map<ActionMode, std::string, EnumHash> ActionModeEnumToName =
{
    { ActionMode::Inline, "Inline" },
    { ActionMode::Popup, "Popup" }
};

static std::unordered_map<std::string, ChoiceSetStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> ChoiceSetStyleNameToEnum =
{
    { "Compact", ChoiceSetStyle::Compact },
    { "Expanded", ChoiceSetStyle::Expanded }
};

static std::unordered_map<ChoiceSetStyle, std::string, EnumHash> ChoiceSetStyleEnumToName =
{
    { ChoiceSetStyle::Compact, "Compact" },
    { ChoiceSetStyle::Expanded, "Expanded" }
};

static std::unordered_map<std::string, TextInputStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> InputTextStyleNameToEnum =
{
    { "Text", TextInputStyle::Text },
    { "Tel", TextInputStyle::Tel },
    { "Url", TextInputStyle::Url },
    { "Email", TextInputStyle::Email },
};

static std::unordered_map<TextInputStyle, std::string, EnumHash> InputTextStyleEnumToName =
{
    { TextInputStyle::Text, "Text" },
    { TextInputStyle::Tel, "Tel" },
    { TextInputStyle::Url, "Url" },
    { TextInputStyle::Email, "Email" },
};

static std::unordered_map<std::string, ContainerStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> ContainerStyleNameToEnum =
{
    { "Normal", ContainerStyle::Normal},
    { "Emphasis", ContainerStyle::Emphasis },
};

static std::unordered_map<ContainerStyle, std::string, EnumHash> ContainerStyleEnumToName =
{
    { ContainerStyle::Normal, "Normal" },
    { ContainerStyle::Emphasis, "Emphasis" },
};

const std::string AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey type)
{
    if (AdaptiveCardSchemaKeyEnumToName.find(type) == AdaptiveCardSchemaKeyEnumToName.end())
    {
        throw std::out_of_range("Invalid AdaptiveCardsSchemaKeys");
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

const std::string HorizontalAlignmentToString(HorizontalAlignment type)
{
    if (HorizontalAlignmentEnumToName.find(type) == HorizontalAlignmentEnumToName.end())
    {
        throw std::out_of_range("Invalid HorizontalAlignment type");
    }
    return HorizontalAlignmentEnumToName[type];
}

HorizontalAlignment HorizontalAlignmentFromString(const std::string& type)
{
    if (HorizontalAlignmentNameToEnum.find(type) == HorizontalAlignmentNameToEnum.end())
    {
        throw std::out_of_range("Invalid HorizontalAlignment: " + type);
    }

    return HorizontalAlignmentNameToEnum[type];
}

const std::string TextColorToString(TextColor type)
{
    if (TextColorEnumToName.find(type) == TextColorEnumToName.end())
    {
        throw std::out_of_range("Invalid TextColor type");
    }
    return TextColorEnumToName[type];
}

TextColor TextColorFromString(const std::string& type)
{
    if (TextColorNameToEnum.find(type) == TextColorNameToEnum.end())
    {
        throw std::out_of_range("Invalid TextColor: " + type);
    }

    return TextColorNameToEnum[type];
}

const std::string TextWeightToString(TextWeight type)
{
    if (TextWeightEnumToName.find(type) == TextWeightEnumToName.end())
    {
        throw std::out_of_range("Invalid TextWeight type");
    }
    return TextWeightEnumToName[type];
}

TextWeight TextWeightFromString(const std::string& type)
{
    if (TextWeightNameToEnum.find(type) == TextWeightNameToEnum.end())
    {
        throw std::out_of_range("Invalid TextWeight: " + type);
    }

    return TextWeightNameToEnum[type];
}

const std::string TextSizeToString(TextSize type)
{
    if (TextSizeEnumToName.find(type) == TextSizeEnumToName.end())
    {
        throw std::out_of_range("Invalid TextSize type");
    }
    return TextSizeEnumToName[type];
}

TextSize TextSizeFromString(const std::string& type)
{
    if (TextSizeNameToEnum.find(type) == TextSizeNameToEnum.end())
    {
        throw std::out_of_range("Invalid TextSize: " + type);
    }

    return TextSizeNameToEnum[type];
}

const std::string ImageSizeToString(ImageSize type)
{
    if (ImageSizeEnumToName.find(type) == ImageSizeEnumToName.end())
    {
        throw std::out_of_range("Invalid ImageSize type");
    }
    return ImageSizeEnumToName[type];
}

ImageSize ImageSizeFromString(const std::string& type)
{
    if (ImageSizeNameToEnum.find(type) == ImageSizeNameToEnum.end())
    {
        throw std::out_of_range("Invalid ImageSize: " + type);
    }

    return ImageSizeNameToEnum[type];
}

const std::string SeparationStyleToString(SeparationStyle type)
{
    if (SeparationStyleEnumToName.find(type) == SeparationStyleEnumToName.end())
    {
        throw std::out_of_range("Invalid SeparationStyle type");
    }
    return SeparationStyleEnumToName[type];
}

SeparationStyle SeparationStyleFromString(const std::string& type)
{
    if (SeparationStyleNameToEnum.find(type) == SeparationStyleNameToEnum.end())
    {
        throw std::out_of_range("Invalid SeparationStyle: " + type);
    }

    return SeparationStyleNameToEnum[type];
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
    if (InputTextStyleEnumToName.find(style) == InputTextStyleEnumToName.end())
    {
        throw std::out_of_range("Invalid InputTextStyle");
    }
    return InputTextStyleEnumToName[style];
}
TextInputStyle TextInputStyleFromString(const std::string & style)
{
    if (InputTextStyleNameToEnum.find(style) == InputTextStyleNameToEnum.end())
    {
        throw std::out_of_range("Invalid InputTextStyle: " + style);
    }
    return InputTextStyleNameToEnum[style];
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
}