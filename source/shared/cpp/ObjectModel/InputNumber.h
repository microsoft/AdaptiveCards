#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class InputNumber : public BaseCardElement
{
public:
    InputNumber();

    static std::shared_ptr<InputNumber> Deserialize(const Json::Value& root);
    static std::shared_ptr<InputNumber> DeserializeFromString(const std::string& jsonString);

    virtual std::string Serialize();

    std::string GetPlaceholder() const;
    void SetPlaceholder(const std::string value);

    std::string GetValue() const;
    void SetValue(const std::string value);

    unsigned int GetMax() const;
    void SetMax(const unsigned int value);

    unsigned int GetMin() const;
    void SetMin(const unsigned int value);

private:
    std::string m_placeholder;
    std::string m_value;
    int m_max;
    int m_min;
};
}