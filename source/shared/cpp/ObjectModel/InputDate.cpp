#include "InputDate.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

InputDate::InputDate() :
    BaseInputElement(CardElementType::InputDate)
{
}

std::shared_ptr<InputDate> InputDate::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::InputDate);

    std::shared_ptr<InputDate> inputDate = BaseInputElement::Deserialize<InputDate>(json);

    inputDate->SetMax(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Max));
    inputDate->SetMin(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Min));
    inputDate->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    inputDate->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));

    return inputDate;
}

std::shared_ptr<InputDate> InputDate::DeserializeFromString(const std::string& jsonString)
{
    return InputDate::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string InputDate::Serialize()
{
    return "";
}

std::string InputDate::GetMax() const
{
    return m_max;
}

void InputDate::SetMax(const std::string value)
{
    m_max = value;
}

std::string InputDate::GetMin() const
{
    return m_min;
}

void InputDate::SetMin(const std::string value)
{
    m_min = value;
}

std::string InputDate::GetPlaceholder() const
{
    return m_placeholder;
}

void InputDate::SetPlaceholder(const std::string value)
{
    m_placeholder = value;
}

std::string InputDate::GetValue() const
{
    return m_value;
}

void InputDate::SetValue(const std::string value)
{
    m_value = value;
}
