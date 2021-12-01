// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ImageSet.h"
#include "ParseUtil.h"
#include "Image.h"
#include "Util.h"

using namespace AdaptiveCards;

ImageSet::ImageSet() : BaseCardElement(CardElementType::ImageSet), m_imageSize(ImageSize::None)
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

    const std::string& itemsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Images);
    root[itemsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& image : m_images)
    {
        root[itemsPropertyName].append(image->SerializeToJsonValue());
    }

    return root;
}

std::shared_ptr<BaseCardElement> ImageSetParser::Deserialize(ParseContext& context, const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::ImageSet);

    auto imageSet = BaseCardElement::Deserialize<ImageSet>(context, value);
    // Get ImageSize
    imageSet->m_imageSize =
        ParseUtil::GetEnumValue<ImageSize>(value, AdaptiveCardSchemaKey::ImageSize, ImageSize::None, ImageSizeFromString);

    // Parse Images
    auto images = ParseUtil::GetElementCollection<Image>(
        true, context, value, AdaptiveCardSchemaKey::Images, true, CardElementTypeToString(CardElementType::Image));

    for (auto image : images)
    {
        imageSet->m_images.push_back(std::static_pointer_cast<Image>(image));
    }

    return imageSet;
}

std::shared_ptr<BaseCardElement> ImageSetParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ImageSetParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void ImageSet::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Images),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ImageSize)});
}

void ImageSet::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    auto images = GetImages();
    for (auto image : images)
    {
        image->GetResourceInformation(resourceInfo);
    }
    return;
}
