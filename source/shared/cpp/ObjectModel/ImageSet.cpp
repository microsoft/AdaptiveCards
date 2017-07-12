#include "ImageSet.h"
#include "ParseUtil.h"
#include "Image.h"

using namespace AdaptiveCards;

ImageSet::ImageSet() : 
    BaseCardElement(CardElementType::ImageSet),
    m_imageSize(ImageSize::Auto)
{
}

ImageSet::ImageSet(
    SeparationStyle separation,
    std::string speak,
    std::vector<std::shared_ptr<Image>>& images) :
    BaseCardElement(CardElementType::ImageSet, separation, speak),
    m_images(images),
    m_imageSize(ImageSize::Default)
{
}

ImageSet::ImageSet(
    SeparationStyle separation,
    std::string speak) :
    BaseCardElement(CardElementType::ImageSet, separation, speak),
    m_imageSize(ImageSize::Auto)
{
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

std::string ImageSet::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value ImageSet::SerializeToJsonValue()
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ImageSize)] = ImageSizeToString(GetImageSize());

    std::string itemsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Images);
    root[itemsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& image : GetImages())
    {
        root[itemsPropertyName].append(image->SerializeToJsonValue());
    }

    return root;
}

std::shared_ptr<ImageSet> ImageSet::Deserialize(const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::ImageSet);

    auto imageSet = BaseCardElement::Deserialize<ImageSet>(value);

    // Get ImageSize
    imageSet->m_imageSize = ParseUtil::GetEnumValue<ImageSize>(value, AdaptiveCardSchemaKey::ImageSize, ImageSize::Auto, ImageSizeFromString);

    // Parse Images
    auto imagesArray = ParseUtil::GetArray(value, AdaptiveCardSchemaKey::Images, true);
    std::vector<std::shared_ptr<Image>> images;

    // Deserialize every image in the array
    for (const Json::Value& element : imagesArray)
    {
        auto image = Image::Deserialize(element);
        if (image != nullptr)
        {
            images.push_back(image);
        }
    }

    imageSet->m_images = std::move(images);

    return imageSet;
}

std::shared_ptr<ImageSet> ImageSet::DeserializeFromString(const std::string& jsonString)
{
    return ImageSet::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}
