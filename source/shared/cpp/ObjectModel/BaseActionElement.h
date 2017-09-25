#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"
#include "ParseUtil.h"

namespace AdaptiveCards
{
class BaseActionElement
{
public:
    BaseActionElement(ActionType type);

    virtual ~BaseActionElement();

    std::string GetTitle() const;
    void SetTitle(const std::string value);

    std::string GetId() const;
    void SetId(const std::string value);

    const ActionType GetElementType() const;

    virtual std::string Serialize() = 0;
    virtual Json::Value SerializeToJsonValue();

    template <typename T>
    static std::shared_ptr<T> Deserialize(const Json::Value& json);

private:
    ActionType m_type;
    std::string m_title;
    std::string m_id;
};

template <typename T>
std::shared_ptr<T> BaseActionElement::Deserialize(const Json::Value& json)
{
    std::shared_ptr<T> cardElement = std::make_shared<T>();
    std::shared_ptr<BaseActionElement> baseActionElement = cardElement;

    ParseUtil::ThrowIfNotJsonObject(json);

    baseActionElement->SetTitle(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Title, true));
    baseActionElement->SetId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Id));

    return cardElement;
}
}
