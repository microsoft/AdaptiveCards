#include "DateInput.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

DateInput::DateInput() :
    BaseInputElement(CardElementType::DateInput)
{
}

std::shared_ptr<DateInput> DateInput::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::DateInput);

    std::shared_ptr<DateInput> dateInput = BaseInputElement::Deserialize<DateInput>(json);

    dateInput->SetMax(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Max));
    dateInput->SetMin(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Min));
    dateInput->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    dateInput->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));

    return dateInput;
}

std::shared_ptr<DateInput> DateInput::DeserializeFromString(const std::string& jsonString)
{
    return DateInput::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string DateInput::Serialize()
{
    return "";
}

std::string DateInput::GetMax() const
{
    return m_max;
}

void DateInput::SetMax(const std::string value)
{
    m_max = value;
}

std::string DateInput::GetMin() const
{
    return m_min;
}

void DateInput::SetMin(const std::string value)
{
    m_min = value;
}

std::string DateInput::GetPlaceholder() const
{
    return m_placeholder;
}

void DateInput::SetPlaceholder(const std::string value)
{
    m_placeholder = value;
}

std::string DateInput::GetValue() const
{
    return m_value;
}

void DateInput::SetValue(const std::string value)
{
    m_value = value;
}
