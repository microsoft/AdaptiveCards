// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ChoiceInput.h"
#include "ChoiceSetInput.h"
#include "ParseUtil.h"
#include "Util.h"

using namespace AdaptiveCards;

ChoiceSetInput::ChoiceSetInput() :
    BaseInputElement(CardElementType::ChoiceSetInput), m_wrap(false), m_isMultiSelect(false),
    m_choiceSetStyle(ChoiceSetStyle::Compact)
{
    PopulateKnownPropertiesSet();
}

const std::vector<std::shared_ptr<ChoiceInput>>& ChoiceSetInput::GetChoices() const
{
    return m_choices;
}

std::vector<std::shared_ptr<ChoiceInput>>& ChoiceSetInput::GetChoices()
{
    return m_choices;
}

Json::Value ChoiceSetInput::SerializeToJsonValue() const
{
    Json::Value root = BaseInputElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ChoiceSetStyleToString(m_choiceSetStyle);

    if (m_isMultiSelect)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsMultiSelect)] = m_isMultiSelect;
    }

    if (!m_value.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = m_value;
    }

    if (m_wrap)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Wrap)] = m_wrap;
    }

    if (m_choices.size())
    {
        const std::string& propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Choices);
        root[propertyName] = Json::Value(Json::arrayValue);
        for (const auto& choice : m_choices)
        {
            root[propertyName].append(choice->SerializeToJsonValue());
        }
    }

    return root;
}

bool ChoiceSetInput::GetIsMultiSelect() const
{
    return m_isMultiSelect;
}

void ChoiceSetInput::SetIsMultiSelect(const bool isMultiSelect)
{
    m_isMultiSelect = isMultiSelect;
}

ChoiceSetStyle ChoiceSetInput::GetChoiceSetStyle() const
{
    return m_choiceSetStyle;
}

void ChoiceSetInput::SetChoiceSetStyle(const ChoiceSetStyle choiceSetStyle)
{
    m_choiceSetStyle = choiceSetStyle;
}

std::string ChoiceSetInput::GetValue() const
{
    return m_value;
}

void ChoiceSetInput::SetValue(std::string const& value)
{
    m_value = value;
}

bool ChoiceSetInput::GetWrap() const
{
    return m_wrap;
}

void ChoiceSetInput::SetWrap(bool value)
{
    m_wrap = value;
}

std::string ChoiceSetInput::GetPlaceholder() const
{
    return m_placeholder;
}

void ChoiceSetInput::SetPlaceholder(const std::string& value)
{
    m_placeholder = value;
}

std::shared_ptr<BaseCardElement> ChoiceSetInputParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::ChoiceSetInput);

    auto choiceSet = BaseInputElement::Deserialize<ChoiceSetInput>(context, json);

    choiceSet->SetChoiceSetStyle(
        ParseUtil::GetEnumValue<ChoiceSetStyle>(json, AdaptiveCardSchemaKey::Style, ChoiceSetStyle::Compact, ChoiceSetStyleFromString));
    choiceSet->SetIsMultiSelect(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsMultiSelect, false));
    choiceSet->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value, false));
    choiceSet->SetWrap(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Wrap, false, false));
    choiceSet->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));

    // Parse Choices
    auto choices =
        ParseUtil::GetElementCollectionOfSingleType<ChoiceInput>(context, json, AdaptiveCardSchemaKey::Choices, ChoiceInput::Deserialize, false);
    choiceSet->m_choices = std::move(choices);

    if (choiceSet->GetIsMultiSelect() && choiceSet->GetChoiceSetStyle() == ChoiceSetStyle::Filtered)
    {
        context.warnings.emplace_back(
            std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::InvalidValue,
                                                       "Input.ChoiceSet does not support filtering with multiselect"));
    }

    return choiceSet;
}

std::shared_ptr<BaseCardElement> ChoiceSetInputParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ChoiceSetInputParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void ChoiceSetInput::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Choices),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsMultiSelect),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Placeholder),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Wrap)});
}
