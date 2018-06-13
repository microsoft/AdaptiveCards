#pragma once

#include "pch.h"
#include "Enums.h"
#include "Image.h"
#include "BaseCardElement.h"

namespace AdaptiveSharedNamespace {
class BaseCardElement;
class ImageSet : public BaseCardElement
{
friend class ImageSetParser;
public:
    ImageSet();

    Json::Value SerializeToJsonValue() const override;

    ImageSize GetImageSize() const;
    void SetImageSize(const ImageSize value);

    std::vector<std::shared_ptr<Image>>& GetImages();
    const std::vector<std::shared_ptr<Image>>& GetImages() const;

    void GetResourceUris(std::vector<std::string>& resourceUris) override;

private:
    void PopulateKnownPropertiesSet() override;

    std::vector<std::shared_ptr<Image>> m_images;
    ImageSize m_imageSize;
};

class ImageSetParser : public BaseCardElementParser
{
public:
    ImageSetParser() = default;
    ImageSetParser(const ImageSetParser&) = default;
    ImageSetParser(ImageSetParser&&) = default;
    ImageSetParser& operator=(const ImageSetParser&) = default;
    ImageSetParser& operator=(ImageSetParser&&) = default;
    virtual ~ImageSetParser() = default;

    std::shared_ptr<BaseCardElement> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const Json::Value& root) override;

    std::shared_ptr<BaseCardElement> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const std::string& jsonString);
};
}
