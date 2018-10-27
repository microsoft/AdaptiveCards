#include "pch.h"
#include "ParseUtil.h"
#include "ToggleViewStateAction.h"

using namespace AdaptiveSharedNamespace;

ToggleViewStateAction::ToggleViewStateAction() : BaseActionElement(ActionType::ToggleViewState)
{
    PopulateKnownPropertiesSet();
}

std::string ToggleViewStateAction::GetNext() const
{
    return m_next;
}

void ToggleViewStateAction::SetNext(const std::string& value)
{
    m_next = value;
}

Json::Value ToggleViewStateAction::SerializeToJsonValue() const
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Next)] = GetNext();

    return root;
}

std::shared_ptr<BaseActionElement> ToggleViewStateActionParser::Deserialize(std::shared_ptr<ElementParserRegistration>,
                                                                   std::shared_ptr<ActionParserRegistration>,
                                                                   std::vector<std::shared_ptr<AdaptiveCardParseWarning>>&,
                                                                   const Json::Value& json)
{
    std::shared_ptr<ToggleViewStateAction> toggleViewStateAction = BaseActionElement::Deserialize<ToggleViewStateAction>(json);
    toggleViewStateAction->SetNext(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Next, true));
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
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Next)});
}
