#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class InputNumber : public BaseInputElement
{
public:
    InputNumber();

    static std::shared_ptr<InputNumber> Deserialize(const Json::Value& root);
    static std::shared_ptr<InputNumber> DeserializeFromString(const std::string& jsonString);

    virtual std::string Serialize();

    std::string GetPlaceholder() const;
    void SetPlaceholder(const std::string value);

    int GetValue() const;
    void SetValue(const int value);

    int GetMax() const;
    void SetMax(const int value);

    int GetMin() const;
    void SetMin(const int value);

private:
    std::string m_placeholder;
    int m_value;
    int m_max;
    int m_min;
};
}