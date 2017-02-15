#include "Image.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

Image::Image() : BaseCardElement(CardElementType::Image)
{
}

Image::Image(
    std::shared_ptr<Container> container,
    HorizontalAlignment horizontalAlignment,
    CardElementSize size,
    std::string speak,
    std::string uri,
    ImageStyle imageStyle) :
    BaseCardElement(CardElementType::Image, container, horizontalAlignment, size, speak),
    m_uri(uri),
    m_imageStyle(imageStyle)
{
}

std::shared_ptr<Image> Image::Deserialize(const Json::Value& json)
{
    ParseUtil::ThrowIfNotJsonObject(json);
    ParseUtil::ExpectTypeString(json, CardElementType::Image);

    // Parse common stuff
    std::string speak = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Speak);
    CardElementSize size = ParseUtil::GetEnumValue<CardElementSize>(json, AdaptiveCardSchemaKey::CardElementSize, CardElementSize::Auto, SizeFromString);
    HorizontalAlignment horAlignment = ParseUtil::GetEnumValue<HorizontalAlignment>(json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString);

    // Parse image stuff
    std::string uri = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Uri);
    ImageStyle imageStyle = ParseUtil::GetEnumValue<ImageStyle>(json, AdaptiveCardSchemaKey::ImageStyle, ImageStyle::Normal, ImageStyleFromString);


    auto image = std::make_shared<Image>(nullptr, horAlignment, size, speak, uri, imageStyle);
    return image;
}

std::string Image::Serialize()
{
    return "";
}

std::string AdaptiveCards::Image::GetUri() const
{
    return m_uri;
}

void AdaptiveCards::Image::SetUri(const std::string value)
{
    m_uri = value;
}

ImageStyle AdaptiveCards::Image::GetImageStyle() const
{
    return m_imageStyle;
}

void AdaptiveCards::Image::SetImageStyle(const ImageStyle value)
{
    m_imageStyle = value;
}
