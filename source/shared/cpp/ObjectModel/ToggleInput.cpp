#include "ToggleInput.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

ToggleInput::ToggleInput() :
    BaseInputElement(CardElementType::ToggleInput),
    m_valueOn("true"),
    m_valueOff("false")
{
    PopulateKnownPropertiesSet();
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

std::shared_ptr<BaseCardElement> ToggleInputParser::Deserialize(
    std::shared_ptr<ElementParserRegistration>,
    std::shared_ptr<ActionParserRegistration>,
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
    const std::string& jsonString)
{
    return ToggleInputParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}

void ToggleInput::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ValueOn));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ValueOff));
}
