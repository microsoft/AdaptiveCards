#include "pch.h"
#include "DateInput.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

DateInput::DateInput() : BaseInputElement(CardElementType::DateInput)
{
    PopulateKnownPropertiesSet();
}

Json::Value DateInput::SerializeToJsonValue() const
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
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = m_value;
    }

    return root;
}

std::string DateInput::GetMax() const
{
    return m_max;
}

void DateInput::SetMax(const std::string& value)
{
    m_max = value;
}

std::string DateInput::GetMin() const
{
    return m_min;
}

void DateInput::SetMin(const std::string& value)
{
    m_min = value;
}

std::string DateInput::GetPlaceholder() const
{
    return m_placeholder;
}

void DateInput::SetPlaceholder(const std::string& value)
{
    m_placeholder = value;
}

std::string DateInput::GetValue() const
{
    return m_value;
}

void DateInput::SetValue(const std::string& value)
{
    m_value = value;
}

std::shared_ptr<BaseCardElement> DateInputParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::DateInput);

    std::shared_ptr<DateInput> dateInput = BaseInputElement::Deserialize<DateInput>(context, json);

    dateInput->SetMax(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Max));
    dateInput->SetMin(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Min));
    dateInput->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    dateInput->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));

    return dateInput;
}

std::shared_ptr<BaseCardElement> DateInputParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return DateInputParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void DateInput::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Max),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Min),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Placeholder)});
}
