#include "pch.h"
#include "NumberInput.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

NumberInput::NumberInput() :
    BaseInputElement(CardElementType::NumberInput), m_value(0), m_max(std::numeric_limits<int>::max()),
    m_min(std::numeric_limits<int>::min())
{
    PopulateKnownPropertiesSet();
}

Json::Value NumberInput::SerializeToJsonValue() const
{
    Json::Value root = BaseInputElement::SerializeToJsonValue();

    if (m_min != std::numeric_limits<int>::min())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Min)] = m_min;
    }

    if (m_max != std::numeric_limits<int>::max())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Max)] = m_max;
    }

    if (m_value != 0)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = m_value;
    }

    if (!m_placeholder.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Placeholder)] = m_placeholder;
    }

    return root;
}

std::string NumberInput::GetPlaceholder() const
{
    return m_placeholder;
}

void NumberInput::SetPlaceholder(const std::string& value)
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

std::shared_ptr<BaseCardElement> NumberInputParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::NumberInput);

    std::shared_ptr<NumberInput> numberInput = BaseInputElement::Deserialize<NumberInput>(context, json);

    numberInput->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    numberInput->SetValue(ParseUtil::GetInt(json, AdaptiveCardSchemaKey::Value, 0));
    numberInput->SetMax(ParseUtil::GetInt(json, AdaptiveCardSchemaKey::Max, std::numeric_limits<int>::max()));
    numberInput->SetMin(ParseUtil::GetInt(json, AdaptiveCardSchemaKey::Min, std::numeric_limits<int>::min()));

    return numberInput;
}

std::shared_ptr<BaseCardElement>
NumberInputParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return NumberInputParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void NumberInput::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Placeholder),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Max),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Min)});
}
