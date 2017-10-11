#include "ChoiceInput.h"
#include "ChoiceSetInput.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

ChoiceSetInput::ChoiceSetInput() : BaseInputElement(CardElementType::ChoiceSetInput)
{
}

ChoiceSetInput::ChoiceSetInput(
    Spacing spacing, 
    bool separation,
    std::vector<std::shared_ptr<ChoiceInput>>& choices) :
    BaseInputElement(CardElementType::ChoiceSetInput, spacing, separation),
    m_choices(choices)
{
}

ChoiceSetInput::ChoiceSetInput(
    Spacing spacing,
    bool separation) :
    BaseInputElement(CardElementType::ChoiceSetInput, spacing, separation)
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
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value ChoiceSetInput::SerializeToJsonValue()
{
    Json::Value root = BaseInputElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ChoiceSetStyleToString(GetChoiceSetStyle());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsMultiSelect)] = GetIsMultiSelect();

    std::string propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Choices);
    root[propertyName] = Json::Value(Json::arrayValue);
    for (const auto& choice : GetChoices())
    {
        root[propertyName].append(choice->SerializeToJsonValue());
    }

    return root;
}

bool AdaptiveCards::ChoiceSetInput::GetIsMultiSelect() const
{
    return m_isMultiSelect;
}

void AdaptiveCards::ChoiceSetInput::SetIsMultiSelect(const bool isMultiSelect)
{
    m_isMultiSelect = isMultiSelect;
}

ChoiceSetStyle AdaptiveCards::ChoiceSetInput::GetChoiceSetStyle() const
{
    return m_choiceSetStyle;
}

void AdaptiveCards::ChoiceSetInput::SetChoiceSetStyle(const ChoiceSetStyle choiceSetStyle)
{
    m_choiceSetStyle = choiceSetStyle;
}

std::shared_ptr<BaseCardElement> ChoiceSetInputParser::Deserialize(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration, 
    const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::ChoiceSetInput);

    auto choiceSet = BaseInputElement::Deserialize<ChoiceSetInput>(json);

    choiceSet->SetChoiceSetStyle(ParseUtil::GetEnumValue<ChoiceSetStyle>(json, AdaptiveCardSchemaKey::Style, ChoiceSetStyle::Compact, ChoiceSetStyleFromString));
    choiceSet->SetIsMultiSelect(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsMultiSelect, false));

    // Parse Choices
    auto choices = ParseUtil::GetElementCollectionOfSingleType<ChoiceInput>(elementParserRegistration, actionParserRegistration, json, AdaptiveCardSchemaKey::Choices, ChoiceInput::Deserialize, true);
    choiceSet->m_choices = std::move(choices);

    return choiceSet;
}

std::shared_ptr<BaseCardElement> ChoiceSetInputParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration, 
    const std::string& jsonString)
{
    return ChoiceSetInputParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}