#pragma once

#include "pch.h"
#include "Enums.h"
#include "BaseActionElement.h"
#include "BaseCardElement.h"

namespace AdaptiveCards
{
class Column : public BaseCardElement
{
public:
    Column();
    Column(Spacing spacing, bool separation, std::string speak, std::string size, ContainerStyle style);
    Column(Spacing spacing, bool separation, std::string speak, std::string size, ContainerStyle style, std::vector<std::shared_ptr<BaseCardElement>>& items);

    virtual std::string Serialize();
    virtual Json::Value SerializeToJsonValue();

    static std::shared_ptr<Column> Deserialize(const Json::Value& root);
    static std::shared_ptr<Column> DeserializeFromString(const std::string& jsonString);

    std::string GetSize() const;
    void SetSize(const std::string value);

    ContainerStyle GetStyle() const;
    void SetStyle(const ContainerStyle value);

    std::vector<std::shared_ptr<BaseCardElement>>& GetItems();
    const std::vector<std::shared_ptr<BaseCardElement>>& GetItems() const;

    std::shared_ptr<BaseActionElement> GetSelectAction() const;
    void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

private:
    static const std::unordered_map<CardElementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, EnumHash> CardElementParsers;
    std::string m_size;
    std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>> m_items;
    std::shared_ptr<BaseActionElement> m_selectAction;
    ContainerStyle m_style;
};
}