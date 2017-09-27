#pragma once

#include "pch.h"
#include "Enums.h"
#include "Image.h"
#include "BaseCardElement.h"

namespace AdaptiveCards
{
class BaseCardElement;
    class ImageSet : public BaseCardElement
    {
        public:
        ImageSet();
        ImageSet(Spacing spacing, bool separation);
        ImageSet(Spacing spacing, bool separation, std::vector<std::shared_ptr<Image>>& images);

        virtual std::string Serialize();
        virtual Json::Value SerializeToJsonValue();

        ImageSize GetImageSize() const;
        void SetImageSize(const ImageSize value);

        std::vector<std::shared_ptr<Image>>& GetImages();
        const std::vector<std::shared_ptr<Image>>& GetImages() const;
        static std::shared_ptr<ImageSet> Deserialize(const Json::Value& root);
        static std::shared_ptr<ImageSet> DeserializeFromString(const std::string& jsonString);

        private:
        std::vector<std::shared_ptr<Image>> m_images;
        ImageSize m_imageSize;
    };
}