#pragma once

#include "pch.h"
#include "CollectionCoreElement.h"
#include "CarouselPage.h"

namespace AdaptiveCards
{
class Carousel : public CollectionCoreElement
{
public:
    Carousel();
    Carousel(const Carousel&) = default;
    Carousel(Carousel&&) = default;
    Carousel& operator=(const Carousel&) = default;
    Carousel& operator=(Carousel&&) = default;
    virtual ~Carousel() = default;

    Json::Value SerializeToJsonValue() const override;
    void DeserializeChildren(ParseContext& context, const Json::Value& value) override;

    std::vector<std::shared_ptr<AdaptiveCards::CarouselPage>>& GetPages();
    const std::vector<std::shared_ptr<AdaptiveCards::CarouselPage>>& GetPages() const;
    void SetPages(const std::vector<std::shared_ptr<AdaptiveCards::CarouselPage>>& value);

    std::string GetHeightInPixels() const;
    void SetHeightInPixels(const std::string& value);

    std::optional<unsigned long> GetTimer() const;
    void SetTimer(const std::optional<unsigned long>& value);

    std::optional<unsigned int> GetInitialPage() const;
    void SetInitialPage(const std::optional<unsigned int>& value);

    std::optional<CarouselOrientation> GetOrientation() const;
    void SetOrientation(const std::optional<CarouselOrientation>& value);

    std::optional<bool> GetAutoLoop() const;
    void setAutoLoop(const std::optional<bool>& value);

private:
    void PopulateKnownPropertiesSet();

    std::vector<std::shared_ptr<AdaptiveCards::CarouselPage>> m_pages;
    std::string m_heightInPixels;
    std::optional<unsigned int> m_timer;
    std::optional<unsigned int> m_initialPage;
    std::optional<CarouselOrientation> m_orientation;
    std::optional<bool> m_autoLoop;
};

class CarouselParser : public BaseCardElementParser
{
public:
    CarouselParser() = default;
    CarouselParser(const CarouselParser&) = default;
    CarouselParser(CarouselParser&&) = default;
    CarouselParser& operator=(const CarouselParser&) = default;
    CarouselParser& operator=(CarouselParser&&) = default;
    virtual ~CarouselParser() = default;

    std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
    std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;

private:
    std::vector<std::string> m_prohibitedTypesList{
        CardElementTypeToString(CardElementType::Carousel),
        ActionTypeToString(ActionType::ShowCard),
        ActionTypeToString(ActionType::ToggleVisibility)};
};
} // namespace AdaptiveCards
