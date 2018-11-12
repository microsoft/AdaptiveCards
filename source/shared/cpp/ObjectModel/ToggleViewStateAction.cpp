#include "pch.h"
#include "ParseUtil.h"
#include "ToggleViewStateAction.h"

using namespace AdaptiveSharedNamespace;

ToggleViewStateAction::ToggleViewStateAction() : BaseActionElement(ActionType::ToggleViewState)
{
    PopulateKnownPropertiesSet();
}

std::string ToggleViewStateAction::GetToggleId() const
{
    return m_toggleId;
}

void ToggleViewStateAction::SetToggleId(const std::string& value)
{
    m_toggleId = value;
}

std::string ToggleViewStateAction::GetToggleTitle() const
{
    return m_toggleTitle;
}

void ToggleViewStateAction::SetToggleTitle(const std::string& value)
{
    m_toggleTitle = value;
}

Json::Value ToggleViewStateAction::SerializeToJsonValue() const
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ToggleId)] = GetToggleId();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ToggleTitle)] = GetToggleTitle();

    return root;
}

std::shared_ptr<BaseActionElement> ToggleViewStateActionParser::Deserialize(std::shared_ptr<ElementParserRegistration>,
                                                                   std::shared_ptr<ActionParserRegistration>,
                                                                   std::vector<std::shared_ptr<AdaptiveCardParseWarning>>&,
                                                                   const Json::Value& json)
{
    std::shared_ptr<ToggleViewStateAction> toggleViewStateAction = BaseActionElement::Deserialize<ToggleViewStateAction>(json);
    toggleViewStateAction->SetToggleId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::ToggleId, true));
    toggleViewStateAction->SetToggleTitle(ParseUtil::GetString(json, AdaptiveCardSchemaKey::ToggleTitle));
    return toggleViewStateAction;
}

std::shared_ptr<BaseActionElement>
ToggleViewStateActionParser::DeserializeFromString(std::shared_ptr<ElementParserRegistration> elementParserRegistration,
                                          std::shared_ptr<ActionParserRegistration> actionParserRegistration,
                                          std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
                                          const std::string& jsonString)
{
    return ToggleViewStateActionParser::Deserialize(elementParserRegistration,
                                           actionParserRegistration,
                                           warnings,
                                           ParseUtil::GetJsonValueFromString(jsonString));
}

void ToggleViewStateAction::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ToggleId)});
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ToggleTitle)});
}
