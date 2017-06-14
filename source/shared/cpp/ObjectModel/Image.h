#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class Image : public BaseCardElement
{
public:
    Image();
    Image(SeparationStyle separationStyle,
        std::string speak,
        std::string uri,
        ImageStyle imageStyle,
        ImageSize imageSize,
        std::string altText,
        HorizontalAlignment hAlignment);

    static std::shared_ptr<Image> Deserialize(const Json::Value& root);
    static std::shared_ptr<Image> DeserializeFromString(const std::string& jsonString);

    virtual std::string Serialize();
    virtual Json::Value SerializeToJsonValue();

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

private:
    std::string m_url;
    ImageStyle m_imageStyle;
    ImageSize m_imageSize;
    std::string m_altText;
    HorizontalAlignment m_hAlignment;
};
}