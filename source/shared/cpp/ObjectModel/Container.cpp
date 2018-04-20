#include "pch.h"
#include "Container.h"
#include "TextBlock.h"
#include "ColumnSet.h"
#include "Util.h"

using namespace AdaptiveSharedNamespace;

Container::Container() : BaseCardElement(CardElementType::Container), m_style(ContainerStyle::None)
{
    PopulateKnownPropertiesSet();
}

Container::Container(
    Spacing spacing,
    bool separator,
    ContainerStyle style,
    std::vector<std::shared_ptr<BaseCardElement>>& items) :
    BaseCardElement(CardElementType::Container, spacing, separator),
    m_style(style),
    m_items(items)
{
    PopulateKnownPropertiesSet();
}

Container::Container(
    Spacing spacing,
    bool separator,
    ContainerStyle style) :
    BaseCardElement(CardElementType::Container, spacing, separator),
    m_style(style)
{
}

const std::vector<std::shared_ptr<BaseCardElement>>& Container::GetItems() const
{
    return m_items;
}

std::vector<std::shared_ptr<BaseCardElement>>& Container::GetItems()
{
    return m_items;
}

ContainerStyle Container::GetStyle() const
{
    return m_style;
}

void Container::SetStyle(const ContainerStyle value)
{
    m_style = value;
}

std::shared_ptr<BaseActionElement> Container::GetSelectAction() const
{
    return m_selectAction;
}

void Container::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}

void Container::SetLanguage(const std::string& value)
{
    PropagateLanguage(value, m_items);
}

Json::Value Container::SerializeToJsonValue()
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    ContainerStyle style = GetStyle();
    if (style != ContainerStyle::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ContainerStyleToString(GetStyle());
    }

    std::string itemsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items);
    root[itemsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : GetItems())
    {
        root[itemsPropertyName].append(cardElement->SerializeToJsonValue());
    }

    std::shared_ptr<BaseActionElement> selectAction = GetSelectAction();
    if (selectAction != nullptr)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] = BaseCardElement::SerializeSelectAction(GetSelectAction());
    }

    return root;
}

std::shared_ptr<BaseCardElement> ContainerParser::Deserialize(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::Container);

    auto container = BaseCardElement::Deserialize<Container>(value);

    container->SetStyle(
        ParseUtil::GetEnumValue<ContainerStyle>(value, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString));

    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection(elementParserRegistration, actionParserRegistration, value, AdaptiveCardSchemaKey::Items, false);
    container->m_items = std::move(cardElements);

    // Parse optional selectAction
    container->SetSelectAction(ParseUtil::GetSelectAction(elementParserRegistration, actionParserRegistration, value, AdaptiveCardSchemaKey::SelectAction, false));

    return container;
}

std::shared_ptr<BaseCardElement> ContainerParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return ContainerParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}

void Container::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items));
}

void Container::GetResourceUris(std::vector<std::string>& resourceUris)
{
    auto items = GetItems();
    for (auto item : items)
    {
        item->GetResourceUris(resourceUris);
    }
    return;
}