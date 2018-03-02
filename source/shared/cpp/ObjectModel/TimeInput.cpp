#include "ParseUtil.h"
#include "TimeInput.h"

using namespace AdaptiveCards;

TimeInput::TimeInput() :
    BaseInputElement(CardElementType::TimeInput)
{
    PopulateKnownPropertiesSet();
}

Json::Value TimeInput::SerializeToJsonValue()
{
    Json::Value root = BaseInputElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Max)] = GetMax();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Min)] = GetMin();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Placeholder)] = GetPlaceholder();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = GetValue();

    return root;
}

std::string TimeInput::GetMax() const
{
    return m_max;
}

void TimeInput::SetMax(const std::string value)
{
    m_max = value;
}

std::string TimeInput::GetMin() const
{
    return m_min;
}

void TimeInput::SetMin(const std::string value)
{
    m_min = value;
}

std::string TimeInput::GetPlaceholder() const
{
    return m_placeholder;
}

void TimeInput::SetPlaceholder(const std::string value)
{
    m_placeholder = value;
}

std::string TimeInput::GetValue() const
{
    return m_value;
}

void TimeInput::SetValue(const std::string value)
{
    m_value = value;
}

std::shared_ptr<BaseCardElement> TimeInputParser::Deserialize(
    std::shared_ptr<ElementParserRegistration>,
    std::shared_ptr<ActionParserRegistration>,
    const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::TimeInput);

    std::shared_ptr<TimeInput> timeInput = BaseInputElement::Deserialize<TimeInput>(json);

    timeInput->SetMax(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Max));
    timeInput->SetMin(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Min));
    timeInput->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    timeInput->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));

    return timeInput;
}

std::shared_ptr<BaseCardElement> TimeInputParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return TimeInputParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}

void TimeInput::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Max));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Min));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Placeholder));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value));
}
