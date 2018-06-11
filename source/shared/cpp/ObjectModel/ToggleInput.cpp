#include "pch.h"
#include "ToggleInput.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

ToggleInput::ToggleInput() :
    BaseInputElement(CardElementType::ToggleInput),
    m_valueOff("false"),
    m_valueOn("true")
{
    PopulateKnownPropertiesSet();
}

Json::Value ToggleInput::SerializeToJsonValue() const
{
    Json::Value root = BaseInputElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title)] = GetTitle();

    if (!m_value.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = m_value;
    }

    if (!m_valueOff.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ValueOff)] = m_valueOff;
    }

    if (!m_valueOn.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ValueOn)] = m_valueOn;
    }

    return root;
}

std::string ToggleInput::GetTitle() const
{
    return m_title;
}

void ToggleInput::SetTitle(const std::string &value)
{
    m_title = value;
}

std::string ToggleInput::GetValue() const
{
    return m_value;
}

void ToggleInput::SetValue(const std::string &value)
{
    m_value = value;
}
void ToggleInput::SetValueOff(const std::string &valueOff)
{
    m_valueOff = valueOff;
}

std::string ToggleInput::GetValueOff() const
{
    return m_valueOff;
}

std::string ToggleInput::GetValueOn() const
{
    return m_valueOn;
}

void ToggleInput::SetValueOn(const std::string &valueOn)
{
    m_valueOn = valueOn;
}

std::shared_ptr<BaseCardElement> ToggleInputParser::Deserialize(
    std::shared_ptr<ElementParserRegistration>,
    std::shared_ptr<ActionParserRegistration>,
    std::vector<std::shared_ptr<AdaptiveCardParseWarning>>&,
    const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::ToggleInput);

    std::shared_ptr<ToggleInput> toggleInput = BaseInputElement::Deserialize<ToggleInput>(json);

    toggleInput->SetTitle(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Title, true));
    toggleInput->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));

    std::string valueOff = ParseUtil::GetString(json, AdaptiveCardSchemaKey::ValueOff);
    if (valueOff != "")
    {
        toggleInput->SetValueOff(valueOff);
    }

    std::string valueOn = ParseUtil::GetString(json, AdaptiveCardSchemaKey::ValueOn);
    if (valueOn != "")
    {
        toggleInput->SetValueOn(valueOn);
    }

    return toggleInput;
}

std::shared_ptr<BaseCardElement> ToggleInputParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
    const std::string& jsonString)
{
    return ToggleInputParser::Deserialize(elementParserRegistration, actionParserRegistration, warnings, ParseUtil::GetJsonValueFromString(jsonString));
}

void ToggleInput::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title),
        AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value),
        AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ValueOn),
        AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ValueOff)});
}
