#include "Container.h"

using namespace AdaptiveCards;

Container::Container() : BaseCardElement(CardElementType::Container), m_style(ContainerStyle::None)
{
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

Json::Value Container::SerializeToJsonValue()
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ContainerStyleToString(GetStyle());

    std::string itemsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items);
    root[itemsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : GetItems())
    {
        root[itemsPropertyName].append(cardElement->SerializeToJsonValue());
    }

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] = BaseCardElement::SerializeSelectAction(GetSelectAction());

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
    auto cardElements = ParseUtil::GetElementCollection(elementParserRegistration, actionParserRegistration, value, AdaptiveCardSchemaKey::Items, true);
    container->m_items = std::move(cardElements);

    container->SetSelectAction(BaseCardElement::DeserializeSelectAction(elementParserRegistration, actionParserRegistration, value, AdaptiveCardSchemaKey::SelectAction));

    return container;
}

std::shared_ptr<BaseCardElement> ContainerParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return ContainerParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}