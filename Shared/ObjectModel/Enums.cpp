#include "Enums.h"
#include <unordered_map>
#include <numeric>
#include <cctype>

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
    { "size", AdaptiveCardSchemaKey::Size },
    { "textSize", AdaptiveCardSchemaKey::TextSize },
    { "textWeight", AdaptiveCardSchemaKey::TextWeight },
    { "textWrap", AdaptiveCardSchemaKey::TextWrap },
    { "textColor", AdaptiveCardSchemaKey::TextColor },
    { "horizontalAlignment", AdaptiveCardSchemaKey::HorizontalAlignment },
    { "imageStyle", AdaptiveCardSchemaKey::ImageStyle},
    { "cardElement", AdaptiveCardSchemaKey::CardElement},
    { "text", AdaptiveCardSchemaKey::Text},
    { "speak", AdaptiveCardSchemaKey::Speak },
};

static std::unordered_map<AdaptiveCardSchemaKey, std::string> AdaptiveCardSchemaKeyEnumToName =
{
    { AdaptiveCardSchemaKey::Type, "@type"},
    { AdaptiveCardSchemaKey::Size, "size"},
    { AdaptiveCardSchemaKey::TextSize, "textSize"},
    { AdaptiveCardSchemaKey::TextWeight, "textWeight"},
    { AdaptiveCardSchemaKey::TextWrap, "textWrap"},
    { AdaptiveCardSchemaKey::TextColor, "textColor"},
    { AdaptiveCardSchemaKey::HorizontalAlignment, "horizontalAlignment"},
    { AdaptiveCardSchemaKey::ImageStyle, "imageStyle"},
    { AdaptiveCardSchemaKey::CardElement, "cardElement"},
    { AdaptiveCardSchemaKey::Text, "text"},
    { AdaptiveCardSchemaKey::Speak, "speak"},
};

static std::unordered_map<std::string, CardElementType, CaseInsensitiveHash, CaseInsensitiveEqualTo> CardElementTypeNameToEnum =
{
    {"AdaptiveCard", CardElementType::AdaptiveCardType},
    {"TextBlock", CardElementType::TextBlockType},
    //{ "Image", CardElementType::ImageType },
    //{ "FactGroup", CardElementType::FactGroupType },
    //{ "ColumnGroup", CardElementType::ColumnGroupType },
    //{ "ImageGallery", CardElementType::ImageGalleryType },
    //{ "ActionGroup", CardElementType::ActionGroupType },
    { "body", CardElementType::ContainerType},
};

static std::unordered_map<CardElementType, std::string> CardElementTypeEnumToName =
{
    { CardElementType::AdaptiveCardType, "AdaptiveCard" },
    { CardElementType::TextBlockType, "TextBlock" },
    //{ CardElementType::ImageType, "Image" },
    //{ CardElementType::FactGroupType, "FactGroup" },
    //{ CardElementType::ColumnGroupType, "ColumnGroup" },
    //{ CardElementType::ImageGalleryType, "ImageGallery" },
    //{ CardElementType::ActionGroupType, "ActionGroup" },
    { CardElementType::ContainerType, "body" },
};

static std::unordered_map<std::string, ImageStyle, CaseInsensitiveHash, CaseInsensitiveEqualTo> ImageStyleEnumToName =
{
    {"Normal", ImageStyle::Normal},
    {"Person", ImageStyle::Person},
};

static std::unordered_map<ImageStyle, std::string> ImageStyleNameToEnum =
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

static std::unordered_map<std::string, Size, CaseInsensitiveHash, CaseInsensitiveEqualTo> SizeNameToEnum =
{
    {"Auto", Size::Auto},
    {"Stretch", Size::Stretch},
    {"Small", Size::Small},
    {"Medium", Size::Medium},
    {"Large", Size::Large},
};

static std::unordered_map<Size, std::string> SizeEnumToName =
{
    {Size::Auto, "Auto"},
    {Size::Stretch, "Stretch"},
    {Size::Small, "Small"},
    {Size::Medium, "Medium"},
    {Size::Large, "Large"},
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

const std::string SizeToString(Size type)
{
    if (SizeEnumToName.find(type) == SizeEnumToName.end())
    {
        throw std::out_of_range("Invalid Size type");
    }
    return SizeEnumToName[type];
}

Size SizeFromString(const std::string& type)
{
    if (SizeNameToEnum.find(type) == SizeNameToEnum.end())
    {
        throw std::out_of_range("Invalid Size: " + type);
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

}
