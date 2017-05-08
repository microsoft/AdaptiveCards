#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class InputDate : public BaseCardElement
{
public:
    InputDate();

    static std::shared_ptr<InputDate> Deserialize(const Json::Value& root);
    static std::shared_ptr<InputDate> DeserializeFromString(const std::string& jsonString);

    virtual std::string Serialize();

    std::string GetMax() const;
    void SetMax(const std::string value);

    std::string GetMin() const;
    void SetMin(const std::string value);

    std::string GetPlaceholder() const;
    void SetPlaceholder(const std::string value);

    std::string GetValue() const;
    void SetValue(const std::string value);

private:
    std::string m_max;
    std::string m_min;
    std::string m_placeholder;
    std::string m_value;
};
}