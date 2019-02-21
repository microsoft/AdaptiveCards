#include "pch.h"
#include "Container.h"
#include "TextBlock.h"
#include "ColumnSet.h"
#include "ParseUtil.h"
#include "Util.h"

using namespace AdaptiveSharedNamespace;

Container::Container() : CollectionTypeElement(CardElementType::Container)
{
    PopulateKnownPropertiesSet();
}

const std::vector<std::shared_ptr<BaseCardElement>>& Container::GetItems() const
{
    return m_items;
}

std::vector<std::shared_ptr<BaseCardElement>>& Container::GetItems()
{
    return m_items;
}

Json::Value Container::SerializeToJsonValue() const
{
    Json::Value root = CollectionTypeElement::SerializeToJsonValue();

    std::string const& itemsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items);
    root[itemsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : m_items)
    {
        root[itemsPropertyName].append(cardElement->SerializeToJsonValue());
    }

    return root;
}

std::shared_ptr<BaseCardElement> ContainerParser::Deserialize(ParseContext& context, const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::Container);

    auto container = BaseCardElement::Deserialize<Container>(context, value);
    container->SetStyle(ParseUtil::GetEnumValue<ContainerStyle>(value, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString));

    container->SetVerticalContentAlignment(ParseUtil::GetEnumValue<VerticalContentAlignment>(
        value, AdaptiveCardSchemaKey::VerticalContentAlignment, VerticalContentAlignment::Top, VerticalContentAlignmentFromString));

    container->SetBleed(ParseUtil::GetBool(value, AdaptiveCardSchemaKey::Bleed, false));

    // configures for cotainer style
    container->ConfigForContainerStyle(context);

    // we walk parse tree dfs inorder, so we need to save current style,
    // before we walk back up to a parent.
    context.SaveContextForCollectionTypeElement(container); 

    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection(context, value, AdaptiveCardSchemaKey::Items, false);
    container->m_items = std::move(cardElements);

    // since we are walking dfs, we have to restore the style before we back up
    context.RestoreContextForCollectionTypeElement(container);

    // Parse optional selectAction
    container->SetSelectAction(ParseUtil::GetAction(context, value, AdaptiveCardSchemaKey::SelectAction, false));

    return container;
}

std::shared_ptr<BaseCardElement> ContainerParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ContainerParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void Container::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalContentAlignment),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items)});
}

void Container::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    auto items = GetItems();
    for (const auto& item : items)
    {
        item->GetResourceInformation(resourceInfo);
    }
    return;
}
