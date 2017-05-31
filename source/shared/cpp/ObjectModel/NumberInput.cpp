#include "NumberInput.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

NumberInput::NumberInput() :
    BaseInputElement(CardElementType::NumberInput),
    m_min(std::numeric_limits<int>::min()),
    m_max(std::numeric_limits<int>::max())
{
}

std::shared_ptr<NumberInput> NumberInput::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::NumberInput);

    std::shared_ptr<NumberInput> numberInput = BaseInputElement::Deserialize<NumberInput>(json);

    numberInput->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    numberInput->SetValue(ParseUtil::GetInt(json, AdaptiveCardSchemaKey::Value, 0));
    numberInput->SetMax(ParseUtil::GetInt(json, AdaptiveCardSchemaKey::Max, std::numeric_limits<int>::max()));
    numberInput->SetMin(ParseUtil::GetInt(json, AdaptiveCardSchemaKey::Min, std::numeric_limits<int>::min()));

    return numberInput;
}

std::shared_ptr<NumberInput> NumberInput::DeserializeFromString(const std::string& jsonString)
{
    return NumberInput::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string NumberInput::Serialize()
{
    return "";
}

std::string NumberInput::GetPlaceholder() const
{
    return m_placeholder;
}

void NumberInput::SetPlaceholder(const std::string value)
{
    m_placeholder = value;
}

int NumberInput::GetValue() const
{
    return m_value;
}

void NumberInput::SetValue(const int value)
{
    m_value = value;
}

int NumberInput::GetMax() const
{
    return m_max;
}

void NumberInput::SetMax(const int value)
{
    m_max = value;
}

int NumberInput::GetMin() const
{
    return m_min;
}

void NumberInput::SetMin(const int value)
{
    m_min = value;
}