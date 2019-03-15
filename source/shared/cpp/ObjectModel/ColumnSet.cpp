#include "pch.h"
#include "ColumnSet.h"
#include "Column.h"
#include "ParseUtil.h"
#include "Image.h"
#include "TextBlock.h"

using namespace AdaptiveSharedNamespace;

ColumnSet::ColumnSet() :
    CollectionTypeElement(CardElementType::ColumnSet)
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
    Json::Value root = CollectionTypeElement::SerializeToJsonValue();

    std::string const& propertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Columns);
    root[propertyName] = Json::Value(Json::arrayValue);
    for (const auto& column : m_columns)
    {
        root[propertyName].append(column->SerializeToJsonValue());
    }

    return root;
}

std::shared_ptr<BaseCardElement> ColumnSetParser::Deserialize(ParseContext& context, const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::ColumnSet);

    auto container = CollectionTypeElement::Deserialize<ColumnSet>(context, value);

    return container;
}

void ColumnSet::DeserializeChildren(ParseContext& context, const Json::Value& value)
{ 
    auto elementArray = ParseUtil::GetArray(value, AdaptiveCardSchemaKey::Columns, false);

    std::vector<std::shared_ptr<Column>> elements;
    if (elementArray.empty())
    {
        m_columns = elements;
        return;
    }

    const Json::ArrayIndex elemSize = elementArray.size();
    const size_t endElemIndex = elemSize - 1;
    elements.reserve(elemSize);

    // Child's bleed get more restricted as we walk down the tree
    // until padding is reset
    // padding get rested when padding is added to a collection type element
    // only left child LC or right child RC have access to the padding of their parents
    // but if parent also has restriction such as BleedToLeft and BleedToRight,
    // only child that has same restriction get bleed property
    // for example, if inherited bleed state was BleedToLeft, only LC gets the bleed,
    // the rest of children cannot bleed.
    ContainerBleedDirection previousBleedState = context.GetBleedDirection();

    if (elemSize == 1)
    {
        // items in signle column has no restriction
        context.SetBleedDirection(previousBleedState);
    }

    // Deserialize every element in the array
    for (Json::ArrayIndex i {0}; i < elemSize; i++)
    {
        Json::Value& curJsonValue = elementArray[i];
        // processing the cases where parent's bleed state is not restricted
        if (elemSize != 1)
        {
            if (i == 0)
            {
                if (previousBleedState == ContainerBleedDirection::BleedToBothEdges)
                {
                    context.SetBleedDirection(ContainerBleedDirection::ToLeadingEdge);
                }
                else if (previousBleedState != ContainerBleedDirection::ToLeadingEdge)
                {
                    context.SetBleedDirection(ContainerBleedDirection::Restricted);
                }
            }
            else if (i == endElemIndex)
            {
                if (previousBleedState == ContainerBleedDirection::BleedToBothEdges)
                {
                    context.SetBleedDirection(ContainerBleedDirection::ToTrailingEdge);
                }
                else if (previousBleedState != ContainerBleedDirection::ToTrailingEdge)
                {
                    context.SetBleedDirection(ContainerBleedDirection::Restricted);
                }
            } else
            {
                context.SetBleedDirection(ContainerBleedDirection::Restricted);
            }
        }

        // Parse the element
        auto el = Column::Deserialize(context, curJsonValue);
        if (el != nullptr)
        {
            elements.push_back(el);
            // restores the parent's bleed state
            context.SetBleedDirection(previousBleedState);
        }
    }

    m_columns = std::move(elements);
}

std::shared_ptr<BaseCardElement> ColumnSetParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ColumnSetParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void ColumnSet::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Columns),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)});
}

void ColumnSet::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    auto columns = GetColumns();
    CollectionTypeElement::GetResourceInformation<Column>(resourceInfo, columns);
    return;
}
