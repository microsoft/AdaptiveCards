#include "Enums.h"

namespace AdaptiveCards
{
struct CaseInsensitiveEqualTo {
    bool operator() (const std::string& lhs, const std::string& rhs) const {
        return _strnicmp(lhs.c_str(), rhs.c_str(), CHAR_MAX) == 0;
    }
};

struct CaseInsensitiveHash {
    size_t operator() (const std::string& keyval) const {
        return std::accumulate(keyval.begin(), keyval.end(), 0, [](size_t acc, char c) { return acc + (size_t)std::tolower(c); });
    }
};

static std::unordered_map<std::string, AdaptiveCardSchemaKey, CaseInsensitiveHash, CaseInsensitiveEqualTo> AdaptiveCardSchemaKeyNameToEnum =
{
    { "@type", AdaptiveCardSchemaKey::Type },
    { "size", AdaptiveCardSchemaKey::CardElementSize },
    { "textSize", AdaptiveCardSchemaKey::TextSize },
    { "textWeight", AdaptiveCardSchemaKey::TextWeight },
    { "textWrap", AdaptiveCardSchemaKey::TextWrap },
    { "textColor", AdaptiveCardSchemaKey::TextColor },
    { "horizontalAlignment", AdaptiveCardSchemaKey::HorizontalAlignment },
    { "imageStyle", AdaptiveCardSchemaKey::ImageStyle},
    { "BaseCardElement", AdaptiveCardSchemaKey::BaseCardElement},
    { "text", AdaptiveCardSchemaKey::Text},
    { "speak", AdaptiveCardSchemaKey::Speak },
    { "uri", AdaptiveCardSchemaKey::Uri },
};

static std::unordered_map<AdaptiveCardSchemaKey, std::string> AdaptiveCardSchemaKeyEnumToName =
{
    { AdaptiveCardSchemaKey::Type, "@type"},
    { AdaptiveCardSchemaKey::CardElementSize, "size"},
    { AdaptiveCardSchemaKey::TextSize, "textSize"},
    { AdaptiveCardSchemaKey::TextWeight, "textWeight"},
    { AdaptiveCardSchemaKey::TextWrap, "textWrap"},
    { AdaptiveCardSchemaKey::TextColor, "textColor"},
    { AdaptiveCardSchemaKey::HorizontalAlignment, "horizontalAlignment"},
    { AdaptiveCardSchemaKey::ImageStyle, "imageStyle"},
    { AdaptiveCardSchemaKey::BaseCardElement, "BaseCardElement"},
    { AdaptiveCardSchemaKey::Text, "text"},
    { AdaptiveCardSchemaKey::Speak, "speak"},
    { AdaptiveCardSchemaKey::Uri, "uri"},
};

static std::unordered_map<std::string, CardElementType, CaseInsensitiveHash, CaseInsensitiveEqualTo> CardElementTypeNameToEnum =
{
    {"AdaptiveCard", CardElementType::AdaptiveCard},
    {"TextBlock", CardElementType::TextBlock},
    { "Image", CardElementType::Image },
    //{ "FactGroup", CardElementType::FactGroup },
    //{ "ColumnGroup", CardElementType::ColumnGroup },
    //{ "ImageGallery", CardElementType::ImageGallery },
    //{ "ActionGroup", CardElementType::ActionGroup },
    { "body", CardElementType::Container},
};

static std::unordered_map<CardElementType, std::string> CardElementTypeEnumToName =
{
    { CardElementType::AdaptiveCard, "AdaptiveCard" },
    { CardElementType::TextBlock, "TextBlock" },
    { CardElementType::Image, "Image" },
    //{ CardElementType::FactGroup, "FactGroup" },
    //{ CardElementType::ColumnGroup, "ColumnGroup" },
    //{ CardElementType::ImageGallery, "ImageGallery" },
    //{ CardElementType::ActionGroup, "ActionGroup" },
    { CardElementType::Container, "body" },
};

static std::unordered_map<std::string, ImageStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> ImageStyleNameToEnum =
{
    {"Normal", ImageStyle::Normal},
    {"Person", ImageStyle::Person},
};

static std::unordered_map<ImageStyle, std::string> ImageStyleEnumToName =
{
    {ImageStyle::Normal, "Normal"},
    {ImageStyle::Person, "Person"},
};

static std::unordered_map<std::string, HorizontalAlignment, CaseInsensitiveHash, CaseInsensitiveEqualTo> HorizontalAlignmentNameToEnum =
{
    {"Left", HorizontalAlignment::Left},
    {"Center", HorizontalAlignment::Center},
    {"Right", HorizontalAlignment::Right},
};

static std::unordered_map<HorizontalAlignment, std::string> HorizontalAlignmentEnumToName =
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

static std::unordered_map<TextColor, std::string> TextColorEnumToName =
{
    {TextColor::Default, "Default"},
    {TextColor::Dark, "Dark"},
    {TextColor::Light, "Light"},
    {TextColor::Accent, "Accent"},
    {TextColor::Good, "Good"},
    {TextColor::Warning, "Warning"},
    {TextColor::Attention, "Attention"},
};

static std::unordered_map<std::string, TextWrap, CaseInsensitiveHash, CaseInsensitiveEqualTo> TextWrapNameToEnum =
{
    { "NoWrap", TextWrap::NoWrap },
    { "Wrap", TextWrap::Wrap },
};

static std::unordered_map<TextWrap, std::string> TextWrapEnumToName =
{
    { TextWrap::NoWrap, "NoWrap"},
    { TextWrap::Wrap, "Wrap"},
};

static std::unordered_map<std::string, TextWeight, CaseInsensitiveHash, CaseInsensitiveEqualTo> TextWeightNameToEnum =
{
    {"Lighter", TextWeight::Lighter},
    {"Normal", TextWeight::Normal},
    {"Bolder", TextWeight::Bolder},
};
static std::unordered_map<TextWeight, std::string> TextWeightEnumToName =
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

static std::unordered_map<TextSize, std::string> TextSizeEnumToName =
{
    {TextSize::Small, "Small"},
    {TextSize::Normal, "Normal"},
    {TextSize::Medium, "Medium"},
    {TextSize::Large, "Large"},
    {TextSize::ExtraLarge, "ExtraLarge"},
};

static std::unordered_map<std::string, CardElementSize, CaseInsensitiveHash, CaseInsensitiveEqualTo> SizeNameToEnum =
{
    {"Auto", CardElementSize::Auto},
    {"Stretch", CardElementSize::Stretch},
    {"Small", CardElementSize::Small},
    {"Medium", CardElementSize::Medium},
    {"Large", CardElementSize::Large},
};

static std::unordered_map<CardElementSize, std::string> SizeEnumToName =
{
    {CardElementSize::Auto, "Auto"},
    {CardElementSize::Stretch, "Stretch"},
    {CardElementSize::Small, "Small"},
    {CardElementSize::Medium, "Medium"},
    {CardElementSize::Large, "Large"},
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

const std::string SizeToString(CardElementSize type)
{
    if (SizeEnumToName.find(type) == SizeEnumToName.end())
    {
        throw std::out_of_range("Invalid CardElementSize type");
    }
    return SizeEnumToName[type];
}

CardElementSize SizeFromString(const std::string& type)
{
    if (SizeNameToEnum.find(type) == SizeNameToEnum.end())
    {
        throw std::out_of_range("Invalid CardElementSize: " + type);
    }

    return SizeNameToEnum[type];
}

const std::string TextWrapToString(TextWrap type)
{
    if (TextWrapEnumToName.find(type) == TextWrapEnumToName.end())
    {
        throw std::out_of_range("Invalid TextWrap type");
    }
    return TextWrapEnumToName[type];
}

TextWrap TextWrapFromString(const std::string& type)
{
    if (TextWrapNameToEnum.find(type) == TextWrapNameToEnum.end())
    {
        throw std::out_of_range("Invalid TextWrap: " + type);
    }

    return TextWrapNameToEnum[type];
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