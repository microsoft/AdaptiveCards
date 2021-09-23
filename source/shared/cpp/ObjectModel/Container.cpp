// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Container.h"
#include "TextBlock.h"
#include "ColumnSet.h"
#include "ParseUtil.h"
#include "Util.h"

using namespace AdaptiveCards;

// This ctor used by types that want to be exactly like Container, but with a different name (e.g. TableCell)
Container::Container(CardElementType derivedType) : StyledCollectionElement(derivedType)
{
    PopulateKnownPropertiesSet();
}

Container::Container() : StyledCollectionElement(CardElementType::Container)
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

// value is present if and only if "rtl" property is explicitly set
std::optional<bool> Container::GetRtl() const
{
    return m_rtl;
}

void Container::SetRtl(const std::optional<bool>& value)
{
    m_rtl = value;
}

Json::Value Container::SerializeToJsonValue() const
{
    Json::Value root = StyledCollectionElement::SerializeToJsonValue();
    std::string const& itemsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items);
    root[itemsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : m_items)
    {
        root[itemsPropertyName].append(cardElement->SerializeToJsonValue());
    }

    if (m_rtl.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Rtl)] = m_rtl.value_or("");
    }

    return root;
}

std::shared_ptr<BaseCardElement> ContainerParser::Deserialize(ParseContext& context, const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::Container);

    auto container = StyledCollectionElement::Deserialize<Container>(context, value);

    container->SetRtl(ParseUtil::GetOptionalBool(value, AdaptiveCardSchemaKey::Rtl));

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
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Rtl),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalContentAlignment),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items)});
}

void Container::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    auto items = GetItems();
    StyledCollectionElement::GetResourceInformation<BaseCardElement>(resourceInfo, items);
    return;
}
