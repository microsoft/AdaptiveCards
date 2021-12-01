// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "Image.h"
#include "BaseCardElement.h"

namespace AdaptiveCards
{
    class BaseCardElement;
    class ImageSet : public BaseCardElement
    {
        friend class ImageSetParser;

    public:
        ImageSet();
        ImageSet(const ImageSet&) = default;
        ImageSet(ImageSet&&) = default;
        ImageSet& operator=(const ImageSet&) = default;
        ImageSet& operator=(ImageSet&&) = default;
        ~ImageSet() = default;

        Json::Value SerializeToJsonValue() const override;

        ImageSize GetImageSize() const;
        void SetImageSize(const ImageSize value);

        std::vector<std::shared_ptr<Image>>& GetImages();
        const std::vector<std::shared_ptr<Image>>& GetImages() const;

        void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

    private:
        void PopulateKnownPropertiesSet();

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

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
