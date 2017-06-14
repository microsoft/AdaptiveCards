#pragma once

#include "Enums.h"
#include "pch.h"
#include "BaseCardElement.h"

namespace AdaptiveCards
{
class Container : public BaseCardElement
{
public:
    Container();
    Container(SeparationStyle separation, std::string speak, ContainerStyle style);
    Container(SeparationStyle separation, std::string speak, ContainerStyle style, std::vector<std::shared_ptr<BaseCardElement>>& items);

    virtual std::string Serialize();
    Json::Value SerializeToJsonValue();

    std::vector<std::shared_ptr<BaseCardElement>>& GetItems();
    const std::vector<std::shared_ptr<BaseCardElement>>& GetItems() const;

    ContainerStyle GetContainerStyle() const;
    void SetContainerStyle(const ContainerStyle value);

    static std::shared_ptr<Container> Deserialize(const Json::Value& root);
    static std::shared_ptr<Container> DeserializeFromString(const std::string& jsonString);

private:
    static const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, EnumHash> CardElementParsers;

    ContainerStyle m_style;
    std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>> m_items;
};
}