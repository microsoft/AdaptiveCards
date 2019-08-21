// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Column.h"
#include "ParseContext.h"
#include "ParseUtil.h"
#include "Util.h"

using namespace AdaptiveSharedNamespace;

Column::Column() : CollectionTypeElement(CardElementType::Column), m_width("Auto"), m_pixelWidth(0)
{
    PopulateKnownPropertiesSet();
}

std::string Column::GetWidth() const
{
    return m_width;
}

void Column::SetWidth(const std::string& value)
{
    SetWidth(value, nullptr);
}

void Column::SetWidth(const std::string& value,
                      std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>>* warnings)
{
    m_width = ParseUtil::ToLowercase(value);
    m_pixelWidth = ParseSizeForPixelSize(m_width, warnings);
}

// explicit width takes precedence over relative width
int Column::GetPixelWidth() const
{
    return m_pixelWidth;
}

void Column::SetPixelWidth(const int value)
{
    m_pixelWidth = value;
    std::ostringstream pixelString;
    pixelString << value << "px";
    m_width = pixelString.str();
}

const std::vector<std::shared_ptr<BaseCardElement>>& Column::GetItems() const
{
    return m_items;
}

std::vector<std::shared_ptr<BaseCardElement>>& Column::GetItems()
{
    return m_items;
}

std::string Column::Serialize() const
{
    return ParseUtil::JsonToString(SerializeToJsonValue());
}

Json::Value Column::SerializeToJsonValue() const
{
    Json::Value root = CollectionTypeElement::SerializeToJsonValue();

    if (!m_width.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Width)] = m_width;
    }

    std::string propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items);
    root[propertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : m_items)
    {
        root[propertyName].append(cardElement->SerializeToJsonValue());
    }

    return root;
}

void Column::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Width),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalContentAlignment)});
}

void Column::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    auto columnItems = GetItems();
    CollectionTypeElement::GetResourceInformation<BaseCardElement>(resourceInfo, columnItems);
    return;
}

void Column::DeserializeChildren(ParseContext& context, const Json::Value& value)
{
    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection<BaseCardElement>(true, // isTopToBottomContainer
                                                                         context,
                                                                         value,
                                                                         AdaptiveCardSchemaKey::Items,
                                                                         false); // isRequired
    m_items = std::move(cardElements);
}

std::shared_ptr<BaseCardElement> ColumnParser::Deserialize(ParseContext& context, const Json::Value& value)
{
    auto column = CollectionTypeElement::Deserialize<Column>(context, value);

    auto fallbackElement = column->GetFallbackContent();
    if (fallbackElement)
    {
        if (CardElementTypeFromString(fallbackElement->GetElementTypeString()) != CardElementType::Column)
        {
            context.warnings.emplace_back(
                std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::UnknownElementType,
                                                           "Column Fallback must be a Column. Fallback content dropped."));

            column->SetFallbackContent(nullptr);
            column->SetFallbackType(FallbackType::None);
        }
    }

    std::string columnWidth = ParseUtil::GetValueAsString(value, AdaptiveCardSchemaKey::Width);
    if (columnWidth == "")
    {
        // Look in "size" for back-compat with pre V1.0 cards
        columnWidth = ParseUtil::GetValueAsString(value, AdaptiveCardSchemaKey::Size);
    }

    column->SetWidth(ParseUtil::ToLowercase(columnWidth), &context.warnings);

    return column;
}

std::shared_ptr<BaseCardElement> ColumnParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ColumnParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
