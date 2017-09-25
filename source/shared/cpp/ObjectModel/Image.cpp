#include "Image.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

Image::Image() :
    BaseCardElement(CardElementType::Image),
    m_imageStyle(ImageStyle::Default),
    m_imageSize(ImageSize::Auto),
    m_hAlignment(HorizontalAlignment::Left)
{
}

Image::Image(
    Spacing spacing,
    bool separator,
    std::string url,
    ImageStyle imageStyle,
    ImageSize imageSize,
    std::string altText,
    HorizontalAlignment hAlignment) :
    BaseCardElement(CardElementType::Image, spacing, separator),
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

    return Image::DeserializeWithoutCheckingType(json);
}

std::shared_ptr<Image> Image::DeserializeWithoutCheckingType(const Json::Value& json)
{
    std::shared_ptr<Image> image = BaseCardElement::Deserialize<Image>(json);

    image->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, true));
    image->SetImageStyle(ParseUtil::GetEnumValue<ImageStyle>(json, AdaptiveCardSchemaKey::Style, ImageStyle::Default, ImageStyleFromString));
    image->SetImageSize(ParseUtil::GetEnumValue<ImageSize>(json, AdaptiveCardSchemaKey::Size, ImageSize::None, ImageSizeFromString));
    image->SetAltText(ParseUtil::GetString(json, AdaptiveCardSchemaKey::AltText));
    image->SetHorizontalAlignment(ParseUtil::GetEnumValue<HorizontalAlignment>(json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString));
    image->SetSelectAction(BaseCardElement::DeserializeSelectAction(json, AdaptiveCardSchemaKey::SelectAction));

    return image;
}

std::string Image::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value Image::SerializeToJsonValue()
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    ImageSize imageSize = GetImageSize();
    if (imageSize != ImageSize::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size)] = ImageSizeToString(GetImageSize());
    }

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ImageStyleToString(GetImageStyle());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Url)] = GetUrl();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment)] =
        HorizontalAlignmentToString(GetHorizontalAlignment());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::AltText)] = GetAltText();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] = BaseCardElement::SerializeSelectAction(GetSelectAction());

    return root;
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
    return Image::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::shared_ptr<BaseActionElement> Image::GetSelectAction() const
{
    return m_selectAction;
}

void Image::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}
