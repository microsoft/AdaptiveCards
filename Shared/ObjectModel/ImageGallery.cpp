#include "ImageGallery.h"

using namespace AdaptiveCards;


ImageGallery::ImageGallery() : BaseCardElement(CardElementType::ImageGallery, nullptr, HorizontalAlignment::Left, CardElementSize::Auto, "")
{
}

ImageGallery::ImageGallery(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, CardElementSize size, std::string speak,
    std::vector<std::shared_ptr<Image>>& images) :
    BaseCardElement(CardElementType::ImageGallery, container, horizontalAlignment, size, speak),
    m_images(images)
{
}

std::vector<std::shared_ptr<Image>>& ImageGallery::GetImages()
{
    return m_images;
}

std::shared_ptr<ImageGallery> ImageGallery::Deserialize(const Json::Value & root)
{
    return std::shared_ptr<ImageGallery>();
}

std::string ImageGallery::Serialize()
{
    return std::string();
}
