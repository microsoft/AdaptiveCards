#include "ChoiceSetInput.h"
#include "Column.h"
#include "TextBlock.h"
#include "ColumnSet.h"
#include "Container.h"

using namespace AdaptiveCards;

Column::Column() : BaseCardElement(CardElementType::Column), m_width("Auto")
{
}

Column::Column(
    Spacing spacing,
    bool separation,
    std::string size,
    ContainerStyle style,
    std::vector<std::shared_ptr<BaseCardElement>>& items) :
    BaseCardElement(CardElementType::Column, spacing, separation), m_width(size), m_style(style), m_items(items)
{
}

Column::Column(
    Spacing spacing,
    bool separation,
    std::string width,
    ContainerStyle style) :
    BaseCardElement(CardElementType::Column, spacing, separation), m_width(width), m_style(style)
{
}

std::string Column::GetWidth() const
{
    return m_width;
}

void Column::SetWidth(const std::string value)
{
    m_width = ParseUtil::ToLowercase(value);
}

ContainerStyle AdaptiveCards::Column::GetStyle() const
{
    return m_style;
}

void AdaptiveCards::Column::SetStyle(const ContainerStyle value)
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

std::string Column::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value Column::SerializeToJsonValue()
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Width)] = GetWidth();

    ContainerStyle style = GetStyle();
    if (style != ContainerStyle::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ContainerStyleToString(GetStyle());
    }

    std::string propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Items);
    root[propertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : GetItems())
    {
        root[propertyName].append(cardElement->SerializeToJsonValue());
    }

    std::shared_ptr<BaseActionElement> selectAction = GetSelectAction();
    if (selectAction != nullptr)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] = BaseCardElement::SerializeSelectAction(GetSelectAction());
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
    column->SetWidth(columnWidth);

    column->SetStyle(
        ParseUtil::GetEnumValue<ContainerStyle>(value, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString));

    // Parse Items
    auto cardElements = ParseUtil::GetElementCollection(elementParserRegistration, actionParserRegistration, value, AdaptiveCardSchemaKey::Items, true);
    column->m_items = std::move(cardElements);

    column->SetSelectAction(BaseCardElement::DeserializeSelectAction(elementParserRegistration, actionParserRegistration, value, AdaptiveCardSchemaKey::SelectAction));

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

void Column::SetLanguage(const std::string& language)
{
    for (auto& item : m_items)
    {
        CardElementType elementType = item->GetElementType();

        if (elementType == CardElementType::Container)
        {
            auto element = std::static_pointer_cast<Container>(item);
            element->SetLanguage(language);
        }
        else if (elementType == CardElementType::ColumnSet)
        {
            auto element = std::static_pointer_cast<ColumnSet>(item);
            element->SetLanguage(language);
        }
        else if (elementType == CardElementType::TextBlock)
        {
            auto element = std::static_pointer_cast<TextBlock>(item);
            element->SetLanguage(language);
        }
    }
}