#include "pch.h"
#include "Image.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

Image::Image() :
    BaseCardElement(CardElementType::Image),
    m_imageStyle(ImageStyle::Default),
    m_imageSize(ImageSize::None),
    m_width(0),
    m_height(0),
    m_hAlignment(HorizontalAlignment::Left)
{
    PopulateKnownPropertiesSet();
}

Image::Image(
    Spacing spacing,
    bool separator,
    std::string url,
    ImageStyle imageStyle,
    ImageSize imageSize,
    unsigned int width,
    unsigned int height,
    std::string altText,
    HorizontalAlignment hAlignment) :
    BaseCardElement(CardElementType::Image, spacing, separator),
    m_url(url),
    m_imageStyle(imageStyle),
    m_imageSize(imageSize),
    m_width(width),
    m_height(height),
    m_altText(altText),
    m_hAlignment(hAlignment)
{
    PopulateKnownPropertiesSet();
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

    std::shared_ptr<BaseActionElement> selectAction = GetSelectAction();
    if (selectAction != nullptr)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] = BaseCardElement::SerializeSelectAction(GetSelectAction());
    }

    return root;
}

std::string Image::GetUrl() const
{
    return m_url;
}

void Image::SetUrl(const std::string value)
{
    m_url = value;
}

ImageStyle Image::GetImageStyle() const
{
    return m_imageStyle;
}

void Image::SetImageStyle(const ImageStyle value)
{
    m_imageStyle = value;
}

ImageSize Image::GetImageSize() const
{
    return m_imageSize;
}

void Image::SetImageSize(const ImageSize value)
{
    m_imageSize = value;
}

std::string Image::GetAltText() const
{
    return m_altText;
}

void Image::SetAltText(const std::string value)
{
    m_altText = value;
}

HorizontalAlignment Image::GetHorizontalAlignment() const
{
    return m_hAlignment;
}

void Image::SetHorizontalAlignment(const HorizontalAlignment value)
{
    m_hAlignment = value;
}

std::shared_ptr<BaseActionElement> Image::GetSelectAction() const
{
    return m_selectAction;
}

void Image::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}

unsigned int Image::GetWidth() const 
{
    return m_width;
}

void Image::SetWidth(unsigned int value)
{
    m_width = value;
}

unsigned int Image::GetHeight() const
{
    return m_height;
}

void Image::SetHeight(unsigned int value)
{
    m_height = value;
}

std::shared_ptr<BaseCardElement> ImageParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return ImageParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}

std::shared_ptr<BaseCardElement> ImageParser::Deserialize(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::Image);
    return ImageParser::DeserializeWithoutCheckingType(elementParserRegistration, actionParserRegistration, json);
}

std::shared_ptr<BaseCardElement> ImageParser::DeserializeWithoutCheckingType(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const Json::Value& json)
{
    std::shared_ptr<Image> image = BaseCardElement::Deserialize<Image>(json);

    image->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, true));
    image->SetImageStyle(ParseUtil::GetEnumValue<ImageStyle>(json, AdaptiveCardSchemaKey::Style, ImageStyle::Default, ImageStyleFromString));
    image->SetImageSize(ParseUtil::GetEnumValue<ImageSize>(json, AdaptiveCardSchemaKey::Size, ImageSize::None, ImageSizeFromString));
    image->SetAltText(ParseUtil::GetString(json, AdaptiveCardSchemaKey::AltText));
    image->SetHorizontalAlignment(ParseUtil::GetEnumValue<HorizontalAlignment>(json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString));

    std::vector<std::string> requestedDimensions;
    requestedDimensions.push_back(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Width));
    requestedDimensions.push_back(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Height));

    // validate user inputs
    const std::string unit = "px";
    std::vector<int> parsedDimensions;
    for(auto eachDimension : requestedDimensions)
    { 
        if (eachDimension.empty())
        {
            parsedDimensions.push_back(0);
        }
        else
        {
            std::size_t foundIndex = eachDimension.find(unit);
            if (eachDimension.size() != foundIndex + unit.size())
            {
                throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "unit is either missing or inproper form: " + eachDimension);
            }
            try
            {
                parsedDimensions.push_back(stoi(eachDimension.substr(0, foundIndex)));
                if (parsedDimensions.back() < 0)
                {
                    throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "unsigned integer is accepted but received : " + eachDimension);
                }
            }
            catch (const std::invalid_argument &e)
            {
                (void)e;
                throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "unsigned integer is accepted but received : " + eachDimension);
            }
            catch (const std::out_of_range &e)
            {
                (void)e;
                throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "out of range: " + eachDimension);
            }
        }
    }

    image->SetWidth(parsedDimensions[0]);
    image->SetHeight(parsedDimensions[1]);
    image->SetSelectAction(BaseCardElement::DeserializeSelectAction(elementParserRegistration, actionParserRegistration, json, AdaptiveCardSchemaKey::SelectAction));

    return image;
}

void Image::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Url));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::AltText));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Width));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Height));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction));
}

void Image::GetResourceUris(std::vector<std::string>& resourceUris)
{
    auto url = GetUrl();
    resourceUris.push_back(url);
    return;
}