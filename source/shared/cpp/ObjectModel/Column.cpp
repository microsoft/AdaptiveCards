#include "pch.h"
#include "ChoiceSetInput.h"
#include "Column.h"
#include "Util.h"

using namespace AdaptiveSharedNamespace;

Column::Column() : BaseCardElement(CardElementType::Column), m_width("Auto"), m_pixelWidth(0), m_style(ContainerStyle::None)
{
    PopulateKnownPropertiesSet();
}

std::string Column::GetWidth() const
{
    return m_width;
}

void Column::SetWidth(const std::string &value)
{
    m_width = ParseUtil::ToLowercase(value);
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

ContainerStyle Column::GetStyle() const
{
    return m_style;
}

void Column::SetStyle(const ContainerStyle value)
{
    m_style = value;
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
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value Column::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    if (!m_width.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Width)] = m_width;
    }

    if (m_style != ContainerStyle::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ContainerStyleToString(m_style);
    }

    std::string propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items);
    root[propertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : m_items)
    {
        root[propertyName].append(cardElement->SerializeToJsonValue());
    }

    if (m_selectAction != nullptr)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] = BaseCardElement::SerializeSelectAction(m_selectAction);
    }

    return root;
}

std::shared_ptr<Column> Column::Deserialize(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const Json::Value& value)
{
    auto column = BaseCardElement::Deserialize<Column>(value);

    std::string columnWidth = ParseUtil::GetValueAsString(value, AdaptiveCardSchemaKey::Width);
    if (columnWidth == "")
    {
        // Look in "size" for back-compat with pre V1.0 cards
        columnWidth = ParseUtil::GetValueAsString(value, AdaptiveCardSchemaKey::Size);
    }

    // validate user input; validation only applies to user input for explicit column width 
    // the other input checks are remained unchanged
    column->SetPixelWidth(0);
    if (!columnWidth.empty() && (isdigit(columnWidth.at(0)) || ('-' == columnWidth.at(0))))
    {
        const std::string unit = "px";
        std::size_t foundIndex = columnWidth.find(unit);
        /// check if width is determined explicitly
        if (std::string::npos != foundIndex) 
        {
            if (columnWidth.size() == foundIndex + unit.size())
            {
                std::vector<std::string> requestedDimensions = { columnWidth };
                std::vector<int> parsedDimensions;
                ValidateUserInputForDimensionWithUnit(unit, requestedDimensions, parsedDimensions);
                column->SetPixelWidth(parsedDimensions[0]);
            }
            else 
            {
                throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "unit is in inproper form: " + columnWidth);
            }
        }
    }

    column->SetWidth(columnWidth);

    column->SetStyle(
        ParseUtil::GetEnumValue<ContainerStyle>(value, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString));

    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection(elementParserRegistration, actionParserRegistration, value, AdaptiveCardSchemaKey::Items, false);
    column->m_items = std::move(cardElements);

    // Parse optional selectAction
    column->SetSelectAction(ParseUtil::GetSelectAction(elementParserRegistration, actionParserRegistration, value, AdaptiveCardSchemaKey::SelectAction, false));

    return column;
}

std::shared_ptr<Column> Column::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return Column::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}

std::shared_ptr<BaseActionElement> Column::GetSelectAction() const
{
    return m_selectAction;
}

void Column::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}

void Column::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Width));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style));
}

void Column::SetLanguage(const std::string& language)
{
    PropagateLanguage(language, m_items);
}

void Column::GetResourceUris(std::vector<std::string>& resourceUris)
{
    auto columnItems = GetItems();
    for (auto item : columnItems)
    {
        item->GetResourceUris(resourceUris);
    }
    return;
}
