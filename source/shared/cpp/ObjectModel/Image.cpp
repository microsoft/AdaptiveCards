#include "Image.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

Image::Image() :
    BaseCardElement(CardElementType::Image),
    m_imageStyle(ImageStyle::Normal),
    m_imageSize(ImageSize::Auto),
    m_hAlignment(HorizontalAlignment::Left)
{
}

Image::Image(SeparationStyle separationStyle,
    std::string speak,
    std::string url,
    ImageStyle imageStyle,
    ImageSize imageSize,
    std::string altText,
    HorizontalAlignment hAlignment) :
    BaseCardElement(CardElementType::Image, separationStyle, speak),
    m_url(url),
    m_imageStyle(imageStyle),
    m_imageSize(imageSize),
    m_altText(altText),
    m_hAlignment(hAlignment)
{
}

std::shared_ptr<Image> Image::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::Image);

    std::shared_ptr<Image> image = BaseCardElement::Deserialize<Image>(json);

    image->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url));
    image->SetImageStyle(ParseUtil::GetEnumValue<ImageStyle>(json, AdaptiveCardSchemaKey::ImageStyle, ImageStyle::Normal, ImageStyleFromString));
    image->SetImageSize(ParseUtil::GetEnumValue<ImageSize>(json, AdaptiveCardSchemaKey::Size, ImageSize::Default, ImageSizeFromString));
    image->SetAltText(ParseUtil::GetString(json, AdaptiveCardSchemaKey::AltText));
    image->SetHorizontalAlignment(ParseUtil::GetEnumValue<HorizontalAlignment>(json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString));
    return image;
}

std::string Image::Serialize()
{
    return "";
}

std::string AdaptiveCards::Image::GetUrl() const
{
    return m_url;
}

void AdaptiveCards::Image::SetUrl(const std::string value)
{
    m_url = value;
}

ImageStyle AdaptiveCards::Image::GetImageStyle() const
{
    return m_imageStyle;
}

void AdaptiveCards::Image::SetImageStyle(const ImageStyle value)
{
    m_imageStyle = value;
}

ImageSize AdaptiveCards::Image::GetImageSize() const
{
    return m_imageSize;
}

void AdaptiveCards::Image::SetImageSize(const ImageSize value)
{
    m_imageSize = value;
}

std::string AdaptiveCards::Image::GetAltText() const
{
    return m_altText;
}

void AdaptiveCards::Image::SetAltText(const std::string value)
{
    m_altText = value;
}

HorizontalAlignment AdaptiveCards::Image::GetHorizontalAlignment() const
{
    return m_hAlignment;
}

void AdaptiveCards::Image::SetHorizontalAlignment(const HorizontalAlignment value)
{
    m_hAlignment = value;
}

std::shared_ptr<Image> Image::DeserializeFromString(const std::string& jsonString)
{
    Json::Value jsonValue(jsonString);

    return Image::Deserialize(jsonValue);
}

