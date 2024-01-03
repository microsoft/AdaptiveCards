#pragma once

#include "Container.h"

namespace AdaptiveCards
{
class BaseCardElement;

class CarouselPage : public Container
{
public:
    CarouselPage() : Container(CardElementType::CarouselPage){};
    CarouselPage(const CarouselPage&) = default;
    CarouselPage(CarouselPage&&) = default;
    CarouselPage& operator=(const CarouselPage&) = default;
    CarouselPage& operator=(CarouselPage&&) = default;
    virtual ~CarouselPage() = default;
};

class CarouselPageParser : public ContainerParser
{
public:
    CarouselPageParser() = default;
    CarouselPageParser(const CarouselPageParser&) = default;
    CarouselPageParser(CarouselPageParser&&) = default;
    CarouselPageParser& operator=(const CarouselPageParser&) = default;
    CarouselPageParser& operator=(CarouselPageParser&&) = default;
    virtual ~CarouselPageParser() = default;

    std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
};
} // namespace AdaptiveCards
