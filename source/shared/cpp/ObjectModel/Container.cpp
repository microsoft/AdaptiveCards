// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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

    auto container = CollectionTypeElement::Deserialize<Container>(context, value);

    return container;
}

void Container::DeserializeChildren(ParseContext& context, const Json::Value& value)
{
    // Parse items
    auto cardElements = ParseUtil::GetElementCollection<BaseCardElement>(true, // isTopToBottomContainer
                                                                         context,
                                                                         value,
                                                                         AdaptiveCardSchemaKey::Items,
                                                                         false); // isRequired
    m_items = std::move(cardElements);
}

std::shared_ptr<BaseCardElement> ContainerParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ContainerParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void Container::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Bleed),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalContentAlignment),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items)});
}

void Container::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    auto items = GetItems();
    CollectionTypeElement::GetResourceInformation<BaseCardElement>(resourceInfo, items);
    return;
}
