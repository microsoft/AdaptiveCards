#include "pch.h"
#include "ImageSet.h"
#include "ParseUtil.h"
#include "Image.h"

using namespace AdaptiveSharedNamespace;

ImageSet::ImageSet() :
    BaseCardElement(CardElementType::ImageSet),
    m_imageSize(ImageSize::None)
{
    PopulateKnownPropertiesSet();
}

ImageSize ImageSet::GetImageSize() const
{
    return m_imageSize;
}

void ImageSet::SetImageSize(const ImageSize value)
{
    m_imageSize = value;
}

const std::vector<std::shared_ptr<Image>>& ImageSet::GetImages() const
{
    return m_images;
}

std::vector<std::shared_ptr<Image>>& ImageSet::GetImages()
{
    return m_images;
}

Json::Value ImageSet::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    if (m_imageSize != ImageSize::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ImageSize)] = ImageSizeToString(GetImageSize());
    }

    std::string const &itemsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Images);
    root[itemsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& image : m_images)
    {
        root[itemsPropertyName].append(image->SerializeToJsonValue());
    }

    return root;
}

std::shared_ptr<BaseCardElement> ImageSetParser::Deserialize(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
    const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::ImageSet);

    auto imageSet = BaseCardElement::Deserialize<ImageSet>(value);

    // Get ImageSize
    imageSet->m_imageSize = ParseUtil::GetEnumValue<ImageSize>(value, AdaptiveCardSchemaKey::ImageSize, ImageSize::None, ImageSizeFromString);

    // Parse Images
    auto images = ParseUtil::GetElementCollection(elementParserRegistration, actionParserRegistration, warnings, value, AdaptiveCardSchemaKey::Images, true);

    for (auto image : images)
    {
        imageSet->m_images.push_back(std::static_pointer_cast<Image>(image));
    }

    return imageSet;
}

std::shared_ptr<BaseCardElement> ImageSetParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
    const std::string& jsonString)
{
    return ImageSetParser::Deserialize(elementParserRegistration, actionParserRegistration, warnings, ParseUtil::GetJsonValueFromString(jsonString));
}

void ImageSet::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Images),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ImageSize)});
}

void ImageSet::GetResourceUris(std::vector<std::string>& resourceUris)
{
    auto images = GetImages();
    for (auto image : images)
    {
        image->GetResourceUris(resourceUris);
    }
    return;
}
