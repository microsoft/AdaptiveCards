#pragma once

#include "pch.h"
#include "SharedAdaptiveCard.h"
#include "BaseActionElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class ShowCardAction : public BaseActionElement
{
public:
    ShowCardAction();

    static std::shared_ptr<ShowCardAction> Deserialize(const Json::Value& root);
    static std::shared_ptr<ShowCardAction> DeserializeFromString(const std::string& jsonString);

    virtual std::string Serialize();
    virtual Json::Value SerializeToJsonValue();

    std::shared_ptr<AdaptiveCards::AdaptiveCard> GetCard() const;
    void SetCard(const std::shared_ptr<AdaptiveCards::AdaptiveCard>);

private:
    std::shared_ptr<AdaptiveCard> m_card;
};
}