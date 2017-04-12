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
    { "imageStyle", AdaptiveCardSchemaKey::ImageStyle },
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
    { AdaptiveCardSchemaKey::ImageStyle, "imageStyle" },
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
};

static std::unordered_map<std::string, CardElementType, CaseInsensitiveHash, CaseInsensitiveEqualTo> CardElementTypeNameToEnum =
{
    { "AdaptiveCard", CardElementType::AdaptiveCard },
    { "TextBlock", CardElementType::TextBlock },
    { "Image", CardElementType::Image },
    { "ColumnSet", CardElementType::ColumnSet },
    { "Column", CardElementType::Column },
    //{ "FactSet", CardElementType::FactSet },
    //{ "ImageGallery", CardElementType::ImageGallery },
    //{ "ActionSet", CardElementType::ActionSet },
    { "Container", CardElementType::Container }

};

static std::unordered_map<CardElementType, std::string, EnumHash> CardElementTypeEnumToName =
{
    { CardElementType::AdaptiveCard, "AdaptiveCard" },
    { CardElementType::TextBlock, "TextBlock" },
    { CardElementType::Image, "Image" },
    { CardElementType::Column, "Column" },
    { CardElementType::ColumnSet, "ColumnSet"},
    //{ CardElementType::FactSet, "FactSet" },
    //{ CardElementType::ImageGallery, "ImageGallery" },
    //{ CardElementType::ActionSet, "ActionSet" },
    { CardElementType::Container, "Container" }
};

static std::unordered_map<std::string, SeparationStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> SeparationStyleNameToEnum =
{
    { "default", SeparationStyle::Default },
    { "none", SeparationStyle::None },
    { "strong", SeparationStyle::Strong},
};

static std::unordered_map<SeparationStyle, std::string, EnumHash> SeparationStyleEnumToName =
{
    { SeparationStyle::Default, "default" },
    { SeparationStyle::None, "none" },
    { SeparationStyle::Strong, "strong" },
};

static std::unordered_map<std::string, ImageStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> ImageStyleNameToEnum =
{
    {"normal", ImageStyle::Normal},
    {"person", ImageStyle::Person},
};

static std::unordered_map<ImageStyle, std::string, EnumHash> ImageStyleEnumToName =
{
    {ImageStyle::Normal, "normal"},
    {ImageStyle::Person, "person"},
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
    { ImageSize::Large, "Large" }
};

static std::unordered_map<std::string, HorizontalAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo> HorizontalAlignmentNameToEnum =
{
    {"Left", HorizontalAlignment::Left},
    {"Center", HorizontalAlignment::Center},
    {"Right", HorizontalAlignment::Right},
};

static std::unordered_map<HorizontalAlignment, std::string, EnumHash> HorizontalAlignmentEnumToName =
{
    {HorizontalAlignment::Left, "Left"},
    {HorizontalAlignment::Center, "Center"},
    {HorizontalAlignment::Right, "Right"},
};

static std::unordered_map<std::string, TextColor, CaseInsensitiveHash, CaseInsensitiveEqualTo> TextColorNameToEnum =
{
    {"Default", TextColor::Default},
    {"Dark", TextColor::Dark},
    {"Light", TextColor::Light},
    {"Accent", TextColor::Accent},
    {"Good", TextColor::Good},
    {"Warning", TextColor::Warning},
    {"Attention", TextColor::Attention},
};

static std::unordered_map<TextColor, std::string, EnumHash> TextColorEnumToName =
{
    {TextColor::Default, "Default"},
    {TextColor::Dark, "Dark"},
    {TextColor::Light, "Light"},
    {TextColor::Accent, "Accent"},
    {TextColor::Good, "Good"},
    {TextColor::Warning, "Warning"},
    {TextColor::Attention, "Attention"},
};

static std::unordered_map<std::string, TextWeight, CaseInsensitiveHash, CaseInsensitiveEqualTo> TextWeightNameToEnum =
{
    {"Lighter", TextWeight::Lighter},
    {"Normal", TextWeight::Normal},
    {"Bolder", TextWeight::Bolder},
};
static std::unordered_map<TextWeight, std::string, EnumHash> TextWeightEnumToName =
{
    {TextWeight::Lighter, "Lighter"},
    {TextWeight::Normal, "Normal"},
    {TextWeight::Bolder, "Bolder"},
};

static std::unordered_map<std::string, TextSize, CaseInsensitiveHash, CaseInsensitiveEqualTo> TextSizeNameToEnum =
{
    {"Small", TextSize::Small},
    {"Normal", TextSize::Normal},
    {"Medium", TextSize::Medium},
    {"Large", TextSize::Large},
    {"ExtraLarge", TextSize::ExtraLarge},
};

static std::unordered_map<TextSize, std::string, EnumHash> TextSizeEnumToName =
{
    {TextSize::Small, "Small"},
    {TextSize::Normal, "Normal"},
    {TextSize::Medium, "Medium"},
    {TextSize::Large, "Large"},
    {TextSize::ExtraLarge, "ExtraLarge"},
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
}