#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include "ElementParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    class Image : public BaseCardElement
    {
    public:
        Image();
        Image(const Image&) = default;
        Image(Image&&) = default;
        Image& operator=(const Image&) = default;
        Image& operator=(Image&&) = default;
        ~Image() = default;

        Json::Value SerializeToJsonValue() const override;

        std::string GetUrl() const;
        void SetUrl(const std::string& value);

        std::string GetBackgroundColor() const;
        void SetBackgroundColor(const std::string& value);

        ImageStyle GetImageStyle() const;
        void SetImageStyle(const ImageStyle value);

        ImageSize GetImageSize() const;
        void SetImageSize(const ImageSize value);

        std::string GetAltText() const;
        void SetAltText(const std::string& value);

        HorizontalAlignment GetHorizontalAlignment() const;
        void SetHorizontalAlignment(const HorizontalAlignment value);

        std::shared_ptr<BaseActionElement> GetSelectAction() const;
        void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

        unsigned int GetPixelWidth() const;
        void SetPixelWidth(unsigned int value);

        unsigned int GetPixelHeight() const;
        void SetPixelHeight(unsigned int value);

        void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

    private:
        void PopulateKnownPropertiesSet() override;

        std::string m_url;
        std::string m_backgroundColor;
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
        ImageParser() = default;
        ImageParser(const ImageParser&) = default;
        ImageParser(ImageParser&&) = default;
        ImageParser& operator=(const ImageParser&) = default;
        ImageParser& operator=(ImageParser&&) = default;
        ~ImageParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeWithoutCheckingType(ParseContext& context, const Json::Value& root);
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
