#include "InputTime.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

InputTime::InputTime() :
    BaseCardElement(CardElementType::InputTime)
{
}

std::shared_ptr<InputTime> InputTime::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::InputTime);

    std::shared_ptr<InputTime> inputTime = BaseCardElement::Deserialize<InputTime>(json);

    inputTime->SetMax(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Max));
    inputTime->SetMin(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Min));
    inputTime->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    inputTime->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));

    return inputTime;
}

std::shared_ptr<InputTime> InputTime::DeserializeFromString(const std::string& jsonString)
{
    Json::Value jsonValue(jsonString);

    return InputTime::Deserialize(jsonValue);
}

std::string InputTime::Serialize()
{
    return "";
}

std::string InputTime::GetMax() const
{
    return m_max;
}

void InputTime::SetMax(const std::string value)
{
    m_max = value;
}

std::string InputTime::GetMin() const
{
    return m_min;
}

void InputTime::SetMin(const std::string value)
{
    m_min = value;
}

std::string InputTime::GetPlaceholder() const
{
    return m_placeholder;
}

void InputTime::SetPlaceholder(const std::string value)
{
    m_placeholder = value;
}

std::string InputTime::GetValue() const
{
    return m_value;
}

void InputTime::SetValue(const std::string value)
{
    m_value = value;
}
