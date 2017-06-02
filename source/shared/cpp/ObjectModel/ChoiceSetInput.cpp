#include "ChoiceInput.h"
#include "ChoiceSetInput.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

ChoiceSetInput::ChoiceSetInput() : BaseInputElement(CardElementType::ChoiceSetInput)
{
}

ChoiceSetInput::ChoiceSetInput(
    SeparationStyle separation,
    std::string speak,
    std::vector<std::shared_ptr<ChoiceInput>>& choices) :
    BaseInputElement(CardElementType::ChoiceSetInput, separation, speak),
    m_choices(choices)
{
}

ChoiceSetInput::ChoiceSetInput(
    SeparationStyle separation,
    std::string speak) :
    BaseInputElement(CardElementType::ChoiceSetInput, separation, speak)
{
}

const std::vector<std::shared_ptr<ChoiceInput>>& ChoiceSetInput::GetChoices() const
{
    return m_choices;
}

std::vector<std::shared_ptr<ChoiceInput>>& ChoiceSetInput::GetChoices()
{
    return m_choices;
}

std::string ChoiceSetInput::Serialize()
{
    return "";
}

bool AdaptiveCards::ChoiceSetInput::GetIsMultiSelect() const
{
    return m_isMultiSelect;
}

void AdaptiveCards::ChoiceSetInput::SetIsMultiSelect(const bool isMultiSelect)
{
    m_isMultiSelect = isMultiSelect;
}

bool AdaptiveCards::ChoiceSetInput::GetIsRequired() const
{
    return m_isRequired;
}

void AdaptiveCards::ChoiceSetInput::SetIsRequired(const bool isRequired)
{
    m_isRequired = isRequired;
}

ChoiceSetStyle AdaptiveCards::ChoiceSetInput::GetChoiceSetStyle() const
{
    return m_choiceSetStyle;
}

void AdaptiveCards::ChoiceSetInput::SetChoiceSetStyle(const ChoiceSetStyle choiceSetStyle)
{
    m_choiceSetStyle = choiceSetStyle;
}

std::shared_ptr<ChoiceSetInput> ChoiceSetInput::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::ChoiceSetInput);

    auto choiceSet = BaseInputElement::Deserialize<ChoiceSetInput>(json);

    choiceSet->SetChoiceSetStyle(ParseUtil::GetEnumValue<ChoiceSetStyle>(json, AdaptiveCardSchemaKey::Style, ChoiceSetStyle::Compact, ChoiceSetStyleFromString));
    choiceSet->SetIsMultiSelect(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsMultiSelect, false));
    choiceSet->SetIsRequired(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsRequired, false));
    
    // Parse Choices
    auto choicesArray = ParseUtil::GetArray(json, AdaptiveCardSchemaKey::Choices, true);
    std::vector<std::shared_ptr<ChoiceInput>> choices;

    // Deserialize every choice in the array
    for (const Json::Value& element : choicesArray)
    {
        auto choice = ChoiceInput::Deserialize(element);
        if (choice != nullptr)
        {
            choices.push_back(choice);
        }
    }

    choiceSet->m_choices = std::move(choices);
    return choiceSet;
}

std::shared_ptr<ChoiceSetInput> ChoiceSetInput::DeserializeFromString(const std::string& jsonString)
{
    return ChoiceSetInput::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}