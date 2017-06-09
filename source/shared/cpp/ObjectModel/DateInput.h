#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class DateInput : public BaseInputElement
{
public:
    DateInput();

    static std::shared_ptr<DateInput> Deserialize(const Json::Value& root);
    static std::shared_ptr<DateInput> DeserializeFromString(const std::string& jsonString);

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