#include "pch.h"
#include "ActionSet.h"
#include "TextBlock.h"
#include "ColumnSet.h"
#include "Util.h"

using namespace AdaptiveCards;

ActionSet::ActionSet() : 
    BaseCardElement(CardElementType::ActionSet),
    m_orientation(ActionsOrientation::None)
{
    PopulateKnownPropertiesSet();
}

ActionSet::ActionSet(
    Spacing spacing,
    bool separator,
    std::vector<std::shared_ptr<BaseActionElement>>& actions) :
    BaseCardElement(CardElementType::ActionSet, spacing, separator),
    m_actions(actions)
{
    PopulateKnownPropertiesSet();
}

ActionSet::ActionSet(
    Spacing spacing,
    bool separator) :
    BaseCardElement(CardElementType::ActionSet, spacing, separator)
{
}

ActionsOrientation ActionSet::GetOrientation() const
{
    return m_orientation;
}

void ActionSet::SetOrientation(const ActionsOrientation value)
{
    m_orientation = value;
}

std::vector<std::shared_ptr<BaseActionElement>>& ActionSet::GetActions()
{
    return m_actions;
}

Json::Value ActionSet::SerializeToJsonValue()
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    std::string actionsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Actions);
    root[actionsPropertyName] = Json::Value(Json::arrayValue);

    if (GetOrientation() != ActionsOrientation::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Orientation)] = ActionsOrientationToString(GetOrientation());
    }

    for (const auto& actionElement : GetActions())
    {
        root[actionsPropertyName].append(actionElement->SerializeToJsonValue());
    }

    return root;
}

std::shared_ptr<BaseCardElement> ActionSetParser::Deserialize(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::ActionSet);

    auto actionSet = BaseCardElement::Deserialize<ActionSet>(value);

    actionSet->SetOrientation(ParseUtil::GetEnumValue<ActionsOrientation>(value, AdaptiveCardSchemaKey::Orientation, ActionsOrientation::None, ActionsOrientationFromString));

    // Parse Actions
    auto actionElements = ParseUtil::GetActionCollection(elementParserRegistration, actionParserRegistration, value, AdaptiveCardSchemaKey::Actions, false);
    actionSet->m_actions = std::move(actionElements);

    return actionSet;
}

std::shared_ptr<BaseCardElement> ActionSetParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return ActionSetParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}

void ActionSet::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Actions));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Orientation));
}
