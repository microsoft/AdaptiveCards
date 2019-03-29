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
    const int parsedDimension = ParseSizeForPixelSize(m_width, warnings);
    SetPixelWidth(parsedDimension);
}

// explicit width takes precedence over relative width
int Column::GetPixelWidth() const
{
    return m_pixelWidth;
}

void Column::SetPixelWidth(const int value)
{
    m_pixelWidth = value;
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

std::shared_ptr<Column> Column::Deserialize(ParseContext& context, const Json::Value& value)
{
    auto column = CollectionTypeElement::Deserialize<Column>(context, value);

    std::string columnWidth = ParseUtil::GetValueAsString(value, AdaptiveCardSchemaKey::Width);
    if (columnWidth == "")
    {
        // Look in "size" for back-compat with pre V1.0 cards
        columnWidth = ParseUtil::GetValueAsString(value, AdaptiveCardSchemaKey::Size);
    }

    column->SetWidth(columnWidth, &context.warnings);

    return column;
}

void Column::DeserializeChildren(ParseContext& context, const Json::Value& value)
{
    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection(context, value, AdaptiveCardSchemaKey::Items, false);
    m_items = std::move(cardElements);
}

std::shared_ptr<Column> Column::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return Column::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
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
