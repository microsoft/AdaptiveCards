#include "pch.h"
#include "ParseUtil.h"
#include "TimeInput.h"

using namespace AdaptiveSharedNamespace;

TimeInput::TimeInput() : BaseInputElement(CardElementType::TimeInput)
{
    PopulateKnownPropertiesSet();
}

Json::Value TimeInput::SerializeToJsonValue() const
{
    Json::Value root = BaseInputElement::SerializeToJsonValue();

    if (!m_max.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Max)] = m_max;
    }

    if (!m_min.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Min)] = m_min;
    }

    if (!m_placeholder.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Placeholder)] = m_placeholder;
    }

    if (!m_value.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = GetValue();
    }

    return root;
}

std::string TimeInput::GetMax() const
{
    return m_max;
}

void TimeInput::SetMax(const std::string& value)
{
    m_max = value;
}

std::string TimeInput::GetMin() const
{
    return m_min;
}

void TimeInput::SetMin(const std::string& value)
{
    m_min = value;
}

std::string TimeInput::GetPlaceholder() const
{
    return m_placeholder;
}

void TimeInput::SetPlaceholder(const std::string& value)
{
    m_placeholder = value;
}

std::string TimeInput::GetValue() const
{
    return m_value;
}

void TimeInput::SetValue(const std::string& value)
{
    m_value = value;
}

std::shared_ptr<BaseCardElement> TimeInputParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::TimeInput);

    std::shared_ptr<TimeInput> timeInput = BaseInputElement::Deserialize<TimeInput>(context, json);

    timeInput->SetMax(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Max));
    timeInput->SetMin(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Min));
    timeInput->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    timeInput->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));

    return timeInput;
}

std::shared_ptr<BaseCardElement> TimeInputParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return TimeInputParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void TimeInput::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Max),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Min),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Placeholder),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)});
}
