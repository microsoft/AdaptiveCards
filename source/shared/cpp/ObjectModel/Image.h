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
    Image(
        Spacing spacing,
        bool separator,
        std::string uri,
        ImageStyle imageStyle,
        ImageSize imageSize,
        unsigned int width,
        unsigned int height,
        std::string altText,
        HorizontalAlignment hAlignment);

    virtual Json::Value SerializeToJsonValue() override;

    std::string GetUrl() const;
    void SetUrl(const std::string value);

    ImageStyle GetImageStyle() const;
    void SetImageStyle(const ImageStyle value);

    ImageSize GetImageSize() const;
    void SetImageSize(const ImageSize value);

    std::string GetAltText() const;
    void SetAltText(const std::string value);

    HorizontalAlignment GetHorizontalAlignment() const;
    void SetHorizontalAlignment(const HorizontalAlignment value);

    std::shared_ptr<BaseActionElement> GetSelectAction() const;
    void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

    unsigned int GetWidth() const; 
    void SetWidth(unsigned int value);

    unsigned int GetHeight() const; 
    void SetHeight(unsigned int value);

    virtual void GetResourceUris(std::vector<std::string>& resourceUris) override;

private:
    void PopulateKnownPropertiesSet();

    std::string m_url;
    ImageStyle m_imageStyle;
    ImageSize m_imageSize;
    unsigned int m_width;
    unsigned int m_height;
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
