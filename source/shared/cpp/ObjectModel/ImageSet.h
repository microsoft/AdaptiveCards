#pragma once

#include "pch.h"
#include "Enums.h"
#include "Image.h"
#include "BaseCardElement.h"

AdaptiveSharedNamespaceStart
class BaseCardElement;
class ImageSet : public BaseCardElement
{
friend class ImageSetParser;
public:
    ImageSet();
    ImageSet(Spacing spacing, bool separation);
    ImageSet(Spacing spacing, bool separation, std::vector<std::shared_ptr<Image>>& images);

    virtual Json::Value SerializeToJsonValue() override;

    ImageSize GetImageSize() const;
    void SetImageSize(const ImageSize value);

    std::vector<std::shared_ptr<Image>>& GetImages();
    const std::vector<std::shared_ptr<Image>>& GetImages() const;

    virtual void GetResourceUris(std::vector<std::string>& resourceUris) override;

private:
    void PopulateKnownPropertiesSet();

    std::vector<std::shared_ptr<Image>> m_images;
    ImageSize m_imageSize;
};
    
class ImageSetParser : public BaseCardElementParser
{
public:
    std::shared_ptr<BaseCardElement> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const Json::Value& root);

    std::shared_ptr<BaseCardElement> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const std::string& jsonString);
};
AdaptiveSharedNamespaceEnd
