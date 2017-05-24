#include "InputChoiceSet.h"
#include "ParseUtil.h"
#include "InputChoice.h"

using namespace AdaptiveCards;

InputChoiceSet::InputChoiceSet() : BaseCardElement(CardElementType::InputChoiceSet)
{
}

InputChoiceSet::InputChoiceSet(
    SeparationStyle separation,
    std::string speak,
    std::vector<std::shared_ptr<InputChoice>>& choices) :
    BaseCardElement(CardElementType::InputChoiceSet, separation, speak),
    m_choices(choices)
{
}

InputChoiceSet::InputChoiceSet(
    SeparationStyle separation,
    std::string speak) :
    BaseCardElement(CardElementType::InputChoiceSet, separation, speak)
{
}

const std::vector<std::shared_ptr<InputChoice>>& InputChoiceSet::GetChoices() const
{
    return m_choices;
}

std::vector<std::shared_ptr<InputChoice>>& InputChoiceSet::GetChoices()
{
    return m_choices;
}

std::string InputChoiceSet::Serialize()
{
    return "";
}

bool AdaptiveCards::InputChoiceSet::GetIsMultiSelect() const
{
    return m_isMultiSelect;
}

void AdaptiveCards::InputChoiceSet::SetIsMultiSelect(const bool isMultiSelect)
{
    m_isMultiSelect = isMultiSelect;
}

bool AdaptiveCards::InputChoiceSet::GetIsRequired() const
{
    return m_isRequired;
}

void AdaptiveCards::InputChoiceSet::SetIsRequired(const bool isRequired)
{
    m_isRequired = isRequired;
}

ChoiceSetStyle AdaptiveCards::InputChoiceSet::GetChoiceSetStyle() const
{
    return m_choiceSetStyle;
}

void AdaptiveCards::InputChoiceSet::SetChoiceSetStyle(const ChoiceSetStyle choiceSetStyle)
{
    m_choiceSetStyle = choiceSetStyle;
}

std::shared_ptr<InputChoiceSet> InputChoiceSet::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::InputChoiceSet);

    auto choiceSet = BaseCardElement::Deserialize<InputChoiceSet>(json);

    choiceSet->SetChoiceSetStyle(ParseUtil::GetEnumValue<ChoiceSetStyle>(json, AdaptiveCardSchemaKey::Style, ChoiceSetStyle::Compact, ChoiceSetStyleFromString));
    choiceSet->SetIsMultiSelect(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsMultiSelect, false));
    choiceSet->SetIsRequired(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsRequired, false));
    
    // Parse Choices
    auto choicesArray = ParseUtil::GetArray(json, AdaptiveCardSchemaKey::Choices, true);
    std::vector<std::shared_ptr<InputChoice>> choices;

    // Deserialize every choice in the array
    for (const Json::Value& element : choicesArray)
    {
        auto choice = InputChoice::Deserialize(element);
        if (choice != nullptr)
        {
            choices.push_back(choice);
        }
    }

    choiceSet->m_choices = std::move(choices);
    return choiceSet;
}

std::shared_ptr<InputChoiceSet> InputChoiceSet::DeserializeFromString(const std::string& jsonString)
{
    Json::Value jsonValue(jsonString);

    return InputChoiceSet::Deserialize(jsonValue);
}