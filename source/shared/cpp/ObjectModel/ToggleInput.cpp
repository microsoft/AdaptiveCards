#include "ToggleInput.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

ToggleInput::ToggleInput() :
    BaseInputElement(CardElementType::ToggleInput),
    m_valueOn("true"),
    m_valueOff("false")
{
}

std::shared_ptr<ToggleInput> ToggleInput::Deserialize(const Json::Value& json)
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

std::shared_ptr<ToggleInput> ToggleInput::DeserializeFromString(const std::string& jsonString)
{
    return ToggleInput::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string ToggleInput::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value ToggleInput::SerializeToJsonValue()
{
    Json::Value root = BaseInputElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title)] = GetTitle();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = GetValue();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ValueOff)] = GetValueOff();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ValueOn)] = GetValueOn();

    return root;
}

std::string ToggleInput::GetTitle() const
{
    return m_title;
}

void ToggleInput::SetTitle(const std::string value)
{
    m_title = value;
}

std::string ToggleInput::GetValue() const
{
    return m_value;
}

void ToggleInput::SetValue(const std::string value)
{
    m_value = value;
}
void ToggleInput::SetValueOff(const std::string valueOff)
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

void ToggleInput::SetValueOn(const std::string valueOn)
{
    m_valueOn = valueOn;
}