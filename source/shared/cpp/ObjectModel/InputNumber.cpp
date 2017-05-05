#include "InputNumber.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

InputNumber::InputNumber() :
    BaseCardElement(CardElementType::InputNumber),
    m_min(0),
    m_max(std::numeric_limits<int>::max())
{
}

std::shared_ptr<InputNumber> InputNumber::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::InputNumber);

    std::shared_ptr<InputNumber> inputNumber = BaseCardElement::Deserialize<InputNumber>(json);

    inputNumber->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    inputNumber->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));
    inputNumber->SetMax(ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Max, INT_MAX));
    inputNumber->SetMin(ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::Min, 0));

    return inputNumber;
}

std::shared_ptr<InputNumber> InputNumber::DeserializeFromString(const std::string& jsonString)
{
    Json::Value jsonValue(jsonString);

    return InputNumber::Deserialize(jsonValue);
}

std::string InputNumber::Serialize()
{
    return "";
}

std::string InputNumber::GetPlaceholder() const
{
    return m_placeholder;
}

void InputNumber::SetPlaceholder(const std::string value)
{
    m_placeholder = value;
}

std::string InputNumber::GetValue() const
{
    return m_value;
}

void InputNumber::SetValue(const std::string value)
{
    m_value = value;
}

unsigned int InputNumber::GetMax() const
{
    return m_max;
}

void InputNumber::SetMax(const unsigned int value)
{
    m_max = value;
}

unsigned int InputNumber::GetMin() const
{
    return m_min;
}

void InputNumber::SetMin(const unsigned int value)
{
    m_min = value;
}