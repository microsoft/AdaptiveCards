// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ActionSet.h"
#include "TextBlock.h"
#include "ColumnSet.h"
#include "Util.h"

using namespace AdaptiveCards;

ActionSet::ActionSet() : BaseCardElement(CardElementType::ActionSet), m_actions{}, m_orientation(ActionsOrientation::Vertical)
{
    PopulateKnownPropertiesSet();
}

ActionSet::ActionSet(std::vector<std::shared_ptr<BaseActionElement>>& actions) :
    BaseCardElement(CardElementType::ActionSet), m_actions(actions), m_orientation(ActionsOrientation::Vertical)
{
    PopulateKnownPropertiesSet();
}

std::vector<std::shared_ptr<BaseActionElement>>& ActionSet::GetActions()
{
    return m_actions;
}

const std::vector<std::shared_ptr<BaseActionElement>>& ActionSet::GetActions() const
{
    return m_actions;
}

Json::Value ActionSet::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    std::string actionsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Actions);
    root[actionsPropertyName] = Json::Value(Json::arrayValue);

    for (const auto& actionElement : m_actions)
    {
        root[actionsPropertyName].append(actionElement->SerializeToJsonValue());
    }

    return root;
}

std::shared_ptr<BaseCardElement> ActionSetParser::Deserialize(ParseContext& context, const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::ActionSet);

    auto actionSet = BaseCardElement::Deserialize<ActionSet>(context, value);

    // Parse Actions
    auto actionElements = ParseUtil::GetActionCollection(context, value, AdaptiveCardSchemaKey::Actions, false);
    actionSet->m_actions = std::move(actionElements);

    return actionSet;
}

std::shared_ptr<BaseCardElement> ActionSetParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ActionSetParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void ActionSet::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Actions));
}
