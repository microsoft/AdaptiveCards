#include "pch.h"
#include "ParseUtil.h"
#include "ToggleVisibilityAction.h"

using namespace AdaptiveSharedNamespace;

ToggleVisibilityAction::ToggleVisibilityAction() : BaseActionElement(ActionType::ToggleVisibility)
{
    PopulateKnownPropertiesSet();
}

const std::vector<std::shared_ptr<ToggleVisibilityTarget>>& ToggleVisibilityAction::GetTargetElements() const
{
    return m_targetElements;
}

std::vector<std::shared_ptr<ToggleVisibilityTarget>>& ToggleVisibilityAction::GetTargetElements()
{
    return m_targetElements;
}

Json::Value ToggleVisibilityAction::SerializeToJsonValue() const
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    std::string targetElementsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::TargetElements);
    root[targetElementsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& targetElement : GetTargetElements())
    {
        root[targetElementsPropertyName].append(targetElement->SerializeToJsonValue());
    }
    return root;
}

std::shared_ptr<BaseActionElement> ToggleVisibilityActionParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<ToggleVisibilityAction> toggleVisibilityAction = BaseActionElement::Deserialize<ToggleVisibilityAction>(context, json);

    auto targetElements = ParseUtil::GetElementCollectionOfSingleType<ToggleVisibilityTarget>(
        context, json, AdaptiveCardSchemaKey::TargetElements, ToggleVisibilityTarget::Deserialize, true);
    toggleVisibilityAction->m_targetElements = std::move(targetElements);

    return toggleVisibilityAction;
}

std::shared_ptr<BaseActionElement> ToggleVisibilityActionParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ToggleVisibilityActionParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void ToggleVisibilityAction::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::TargetElements)});
}
