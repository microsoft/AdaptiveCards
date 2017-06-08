#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class NumberInput : public BaseInputElement
{
public:
    NumberInput();

    static std::shared_ptr<NumberInput> Deserialize(const Json::Value& root);
    static std::shared_ptr<NumberInput> DeserializeFromString(const std::string& jsonString);

    virtual std::string Serialize();
    virtual Json::Value SerializeToJsonValue();

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