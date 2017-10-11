#include "DateInput.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

DateInput::DateInput() :
    BaseInputElement(CardElementType::DateInput)
{
}

std::string DateInput::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value DateInput::SerializeToJsonValue()
{
    Json::Value root = BaseInputElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Max)] = GetMax();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Min)] = GetMin();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Placeholder)] = GetPlaceholder();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = GetValue();

    return root;
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

std::shared_ptr<BaseCardElement> DateInputParser::Deserialize(
    std::shared_ptr<ElementParserRegistration>,
    std::shared_ptr<ActionParserRegistration>,
    const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::DateInput);

    std::shared_ptr<DateInput> dateInput = BaseInputElement::Deserialize<DateInput>(json);

    dateInput->SetMax(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Max));
    dateInput->SetMin(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Min));
    dateInput->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    dateInput->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));

    return dateInput;
}

std::shared_ptr<BaseCardElement> DateInputParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return DateInputParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}