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
    std::vector<std::shared_ptr<BaseActionElement>>& actions) :
    BaseCardElement(CardElementType::ActionSet),
    m_actions(actions)
{
    PopulateKnownPropertiesSet();
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

Json::Value ActionSet::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    std::string actionsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Actions);
    root[actionsPropertyName] = Json::Value(Json::arrayValue);

    if (GetOrientation() != ActionsOrientation::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Orientation)] = ActionsOrientationToString(GetOrientation());
    }

    for (auto actionElement : m_actions)
    {
        root[actionsPropertyName].append(actionElement->SerializeToJsonValue());
    }

    return root;
}

std::shared_ptr<BaseCardElement> ActionSetParser::Deserialize(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
	std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
    const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::ActionSet);

    auto actionSet = BaseCardElement::Deserialize<ActionSet>(value);

    actionSet->SetOrientation(ParseUtil::GetEnumValue<ActionsOrientation>(value, AdaptiveCardSchemaKey::Orientation, ActionsOrientation::None, ActionsOrientationFromString));

    // Parse Actions
    auto actionElements = ParseUtil::GetActionCollection(elementParserRegistration, actionParserRegistration, warnings, value, AdaptiveCardSchemaKey::Actions, false);
    actionSet->m_actions = std::move(actionElements);

    return actionSet;
}

std::shared_ptr<BaseCardElement> ActionSetParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
	std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
    const std::string& jsonString)
{
    return ActionSetParser::Deserialize(elementParserRegistration, actionParserRegistration, warnings, ParseUtil::GetJsonValueFromString(jsonString));
}

void ActionSet::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Actions));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Orientation));
}
