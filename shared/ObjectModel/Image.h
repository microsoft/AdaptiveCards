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
    Image(std::shared_ptr<Container> container,
        HorizontalAlignment horizontalAlignment,
        CardElementSize size,
        std::string speak,
        std::string uri,
        ImageStyle imageStyle);

    static std::shared_ptr<Image> Deserialize(const Json::Value& root);

    virtual std::string Serialize();

    std::string GetUri() const;
    void SetUri(const std::string value);

    ImageStyle GetImageStyle() const;
    void SetImageStyle(const ImageStyle value);

private:
    std::string m_uri;
    ImageStyle m_imageStyle;
};
}