// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ParseUtil.h"
#include "ExecuteAction.h"

using namespace AdaptiveCards;

ExecuteAction::ExecuteAction() : BaseActionElement(ActionType::Execute), m_associatedInputs(AssociatedInputs::Auto)
{
    PopulateKnownPropertiesSet();
}

std::string ExecuteAction::GetDataJson() const
{
    return ParseUtil::JsonToString(m_dataJson);
}

Json::Value ExecuteAction::GetDataJsonAsValue() const
{
    return m_dataJson;
}

void ExecuteAction::SetDataJson(const std::string value)
{
    SetDataJson(ParseUtil::GetJsonValueFromString(value));
}

void ExecuteAction::SetDataJson(const Json::Value& value)
{
    m_dataJson = value;
}

std::string ExecuteAction::GetVerb() const
{
    return m_verb;
}

void ExecuteAction::SetVerb(const std::string verb)
{
    m_verb = verb;
}

AssociatedInputs ExecuteAction::GetAssociatedInputs() const
{
    return m_associatedInputs;
}

void ExecuteAction::SetAssociatedInputs(const AssociatedInputs value)
{
    m_associatedInputs = value;
}

Json::Value ExecuteAction::SerializeToJsonValue() const
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    if (!m_dataJson.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Data)] = m_dataJson;
    }

    if (!m_verb.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Verb)] = m_verb;
    }

    if (m_associatedInputs != AssociatedInputs::Auto)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::AssociatedInputs)] = AssociatedInputsToString(m_associatedInputs);
    }

    return root;
}

std::shared_ptr<BaseActionElement> ExecuteActionParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<ExecuteAction> executeAction = BaseActionElement::Deserialize<ExecuteAction>(context, json);

    executeAction->SetDataJson(ParseUtil::ExtractJsonValue(json, AdaptiveCardSchemaKey::Data));
    executeAction->SetVerb(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Verb));
    executeAction->SetAssociatedInputs(ParseUtil::GetEnumValue<AssociatedInputs>(
        json, AdaptiveCardSchemaKey::AssociatedInputs, AssociatedInputs::Auto, AssociatedInputsFromString));

    return executeAction;
}

std::shared_ptr<BaseActionElement> ExecuteActionParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ExecuteActionParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void ExecuteAction::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert(
        {AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Data),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Verb),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::AssociatedInputs)});
}
