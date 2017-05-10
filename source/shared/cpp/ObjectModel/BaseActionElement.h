#pragma once

#include "pch.h"
#include "Enums.h"
#include "json\json.h"
#include "ParseUtil.h"

namespace AdaptiveCards
{
class Container;
class BaseActionElement
{
public:
    BaseActionElement(ActionType type, std::string speak);
    BaseActionElement(ActionType type);

    virtual ~BaseActionElement();

    std::string GetSpeak() const;
    void SetSpeak(const std::string value);

    std::string GetTitle() const;
    void SetTitle(const std::string value);

    const ActionType GetElementType() const;

    virtual std::string Serialize() = 0;

    template <typename T>
    static std::shared_ptr<T> Deserialize(const Json::Value& json);

private:
    ActionType m_type;
    std::string m_speak;
    std::string m_title;
};

template <typename T>
std::shared_ptr<T> BaseActionElement::Deserialize(const Json::Value& json)
{
    std::shared_ptr<T> cardElement = std::make_shared<T>();
    std::shared_ptr<BaseActionElement> BaseActionElement = cardElement;

    ParseUtil::ThrowIfNotJsonObject(json);

    BaseActionElement->SetSpeak(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Speak));

    return cardElement;
}
}

