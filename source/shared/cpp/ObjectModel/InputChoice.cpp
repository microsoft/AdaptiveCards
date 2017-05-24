#include "InputChoice.h"
#include "ParseUtil.h"
#include "Enums.h"

using namespace AdaptiveCards;

InputChoice::InputChoice() :
    m_isSelected(false)
{
}

std::shared_ptr<InputChoice> InputChoice::Deserialize(const Json::Value& json)
{
    auto choice = std::make_shared<InputChoice>();

    choice->SetTitle(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Title, true));
    choice->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value, true));
    choice->SetSpeak(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Speak));
    choice->SetIsSelected(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsSelected, false));

    return choice;
}

std::shared_ptr<InputChoice> InputChoice::DeserializeFromString(const std::string& jsonString)
{
    return InputChoice::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string InputChoice::Serialize()
{
    return "";
}

std::string InputChoice::GetTitle() const
{
    return m_title;
}

void InputChoice::SetTitle(const std::string title)
{
    m_title = title;
}

std::string InputChoice::GetValue() const
{
    return m_value;
}

void InputChoice::SetValue(const std::string value)
{
    m_value = value;
}

bool AdaptiveCards::InputChoice::GetIsSelected() const
{
    return m_isSelected;
}

void AdaptiveCards::InputChoice::SetIsSelected(const bool isSelected)
{
    m_isSelected = isSelected;
}

std::string InputChoice::GetSpeak() const
{
    return m_speak;
}

void InputChoice::SetSpeak(const std::string value)
{
    m_speak = value;
}
