#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include "ElementParserRegistration.h"

AdaptiveSharedNamespaceStart
class Image : public BaseCardElement
{
public:
    Image();

    virtual Json::Value SerializeToJsonValue() const override;

    std::string GetUrl() const;
    void SetUrl(const std::string &value);

    ImageStyle GetImageStyle() const;
    void SetImageStyle(const ImageStyle value);

    ImageSize GetImageSize() const;
    void SetImageSize(const ImageSize value);

    std::string GetAltText() const;
    void SetAltText(const std::string &value);

    HorizontalAlignment GetHorizontalAlignment() const;
    void SetHorizontalAlignment(const HorizontalAlignment value);

    std::shared_ptr<BaseActionElement> GetSelectAction() const;
    void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

    unsigned int GetPixelWidth() const; 
    void SetPixelWidth(unsigned int value);

    unsigned int GetPixelHeight() const; 
    void SetPixelHeight(unsigned int value);

    virtual void GetResourceUris(std::vector<std::string>& resourceUris) override;

private:
    void PopulateKnownPropertiesSet();

    std::string m_url;
    ImageStyle m_imageStyle;
    ImageSize m_imageSize;
    unsigned int m_pixelWidth;
    unsigned int m_pixelHeight;
    std::string m_altText;
    HorizontalAlignment m_hAlignment;
    std::shared_ptr<BaseActionElement> m_selectAction;
};

class ImageParser : public BaseCardElementParser
{
public:
    std::shared_ptr<BaseCardElement> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const Json::Value& root);

    std::shared_ptr<BaseCardElement> DeserializeWithoutCheckingType(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const Json::Value& root);

    std::shared_ptr<BaseCardElement> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const std::string& jsonString);
};
AdaptiveSharedNamespaceEnd
