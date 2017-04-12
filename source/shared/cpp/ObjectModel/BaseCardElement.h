#pragma once

#include "pch.h"
#include "Enums.h"
#include "json\json.h"

namespace AdaptiveCards
{
class Container;
class BaseCardElement
{
public:
    BaseCardElement(CardElementType type, SeparationStyle separationStyle, std::string speak);
    BaseCardElement(CardElementType type);

    virtual ~BaseCardElement();

    SeparationStyle GetSeparationStyle() const;
    void SetSeparationStyle(const SeparationStyle value);

    std::string GetSpeak() const;
    void SetSpeak(const std::string value);

    const CardElementType GetElementType() const;

    virtual std::string Serialize() = 0;

    template <typename T>
    static std::shared_ptr<T> Deserialize(const Json::Value& json);

private:
    CardElementType m_type;
    SeparationStyle m_separationStyle;
    std::string m_speak;
};

}

