#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "Image.h"
#include "Enums.h"

namespace AdaptiveCards
{
    class ImageGallery : BaseCardElement
    {
    public:
        ImageGallery();
        ImageGallery(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, CardElementSize size, std::string speak,
            std::vector<std::shared_ptr<Image>>& images = std::vector<std::shared_ptr<Image>>());

        std::vector<std::shared_ptr<Image>>& GetImages();

        static std::shared_ptr<ImageGallery> Deserialize(const Json::Value& root);

        virtual std::string Serialize();

    private:
        std::vector<std::shared_ptr<Image>> m_images;
    };
}