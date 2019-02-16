#include "pch.h"
#include "ToggleInput.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

ToggleInput::ToggleInput() :
    BaseInputElement(CardElementType::ToggleInput), m_valueOff("false"), m_valueOn("true"), m_wrap(false)
{
    PopulateKnownPropertiesSet();
}

Json::Value ToggleInput::SerializeToJsonValue() const
{
    Json::Value root = BaseInputElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title)] = GetTitle();

    if (m_wrap)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Wrap)] = m_wrap;
    }

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

void ToggleInput::SetTitle(const std::string& value)
{
    m_title = value;
}

std::string ToggleInput::GetValue() const
{
    return m_value;
}

void ToggleInput::SetValue(const std::string& value)
{
    m_value = value;
}
void ToggleInput::SetValueOff(const std::string& valueOff)
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

void ToggleInput::SetValueOn(const std::string& valueOn)
{
    m_valueOn = valueOn;
}

bool ToggleInput::GetWrap() const
{
    return m_wrap;
}

void ToggleInput::SetWrap(bool value)
{
    m_wrap = value;
}

std::shared_ptr<BaseCardElement> ToggleInputParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::ToggleInput);

    std::shared_ptr<ToggleInput> toggleInput = BaseInputElement::Deserialize<ToggleInput>(context, json);

    toggleInput->SetTitle(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Title, true));
    toggleInput->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));
    toggleInput->SetWrap(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Wrap, false, false));

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

std::shared_ptr<BaseCardElement>
ToggleInputParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ToggleInputParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void ToggleInput::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ValueOn),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ValueOff),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Wrap)});
}
