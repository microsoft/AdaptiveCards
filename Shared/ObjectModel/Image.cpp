#include "Image.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

Image::Image() : BaseCardElement(CardElementType::Image, nullptr, HorizontalAlignment::Left, CardElementSize::Auto, "")
{
}

Image::Image(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, CardElementSize size, std::string speak, std::string uri, ImageStyle imageStyle) : BaseCardElement(CardElementType::Image, container, horizontalAlignment, size, speak), m_uri(uri), m_imageStyle(imageStyle) {}

std::shared_ptr<Image> Image::Deserialize(const Json::Value& json)
{
    return std::make_shared<Image>();
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
