// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "StyledCollectionElement.h"
#include "CarouselPage.h"

namespace AdaptiveCards
{
class Carousel : public StyledCollectionElement
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

    unsigned int GetHeightInPixels() const;
    void SetHeightInPixels(const unsigned int value);

    std::optional<unsigned long> GetTimer() const;
    void SetTimer(const std::optional<unsigned long>& value);

    std::optional<unsigned int> GetInitialPage() const;
    void SetInitialPage(const std::optional<unsigned int>& value);

    std::optional<CarouselOrientation> GetOrientation() const;
    void SetOrientation(const std::optional<CarouselOrientation>& value);

    std::optional<bool> GetAutoLoop() const;
    void setAutoLoop(const std::optional<bool>& value);

    std::optional<bool> GetRtl() const;
    void SetRtl(const std::optional<bool>& value);

private:
    void PopulateKnownPropertiesSet();

    std::vector<std::shared_ptr<AdaptiveCards::CarouselPage>> m_pages;
    unsigned int m_heightInPixels{0};
    std::optional<unsigned int> m_timer;
    std::optional<unsigned int> m_initialPage;
    std::optional<CarouselOrientation> m_orientation;
    std::optional<bool> m_autoLoop;
    std::optional<bool> m_rtl;
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
