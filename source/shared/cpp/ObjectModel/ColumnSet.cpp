// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ColumnSet.h"
#include "Column.h"
#include "ParseUtil.h"
#include "Image.h"
#include "TextBlock.h"
#include "Util.h"

using namespace AdaptiveCards;

ColumnSet::ColumnSet() : StyledCollectionElement(CardElementType::ColumnSet)
{
    PopulateKnownPropertiesSet();
}

const std::vector<std::shared_ptr<Column>>& ColumnSet::GetColumns() const
{
    return m_columns;
}

std::vector<std::shared_ptr<Column>>& ColumnSet::GetColumns()
{
    return m_columns;
}

Json::Value ColumnSet::SerializeToJsonValue() const
{
    Json::Value root = StyledCollectionElement::SerializeToJsonValue();

    std::string const& propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Columns);
    root[propertyName] = Json::Value(Json::arrayValue);
    for (const auto& column : m_columns)
    {
        root[propertyName].append(column->SerializeToJsonValue());
    }

    if (m_horizontalAlignment.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment)] =
            HorizontalAlignmentToString(m_horizontalAlignment.value_or(HorizontalAlignment::Left));
    }
    return root;
}

void ColumnSet::DeserializeChildren(ParseContext& context, const Json::Value& value)
{
    m_columns = ParseUtil::GetElementCollection<Column>(
        false, // isTopToBottomContainer
        context,
        value,
        AdaptiveCardSchemaKey::Columns,
        false,                                             // isRequired
        CardElementTypeToString(CardElementType::Column)); // impliedType
}

std::optional<HorizontalAlignment> AdaptiveCards::ColumnSet::GetHorizontalAlignment() const
{
    return m_horizontalAlignment;
}

void AdaptiveCards::ColumnSet::SetHorizontalAlignment(std::optional<HorizontalAlignment> value)
{
    m_horizontalAlignment = value;
}

void ColumnSet::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert(
        {AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Bleed),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Columns),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)});
}

void ColumnSet::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    auto columns = GetColumns();
    StyledCollectionElement::GetResourceInformation<Column>(resourceInfo, columns);
    return;
}

std::shared_ptr<BaseCardElement> ColumnSetParser::Deserialize(ParseContext& context, const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::ColumnSet);

    auto container = StyledCollectionElement::Deserialize<ColumnSet>(context, value);

    container->SetHorizontalAlignment(ParseUtil::GetOptionalEnumValue<HorizontalAlignment>(
        value, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignmentFromString));

    return container;
}

std::shared_ptr<BaseCardElement> ColumnSetParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ColumnSetParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
