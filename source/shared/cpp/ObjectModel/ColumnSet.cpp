#include "pch.h"
#include "ColumnSet.h"
#include "Column.h"
#include "ParseUtil.h"
#include "Image.h"
#include "TextBlock.h"
#include "Util.h"

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

    const size_t elemSize = elementArray.size();
    const size_t endElemIndex = elemSize - 1;
    elements.reserve(elemSize);

    size_t currentIndex = 0;

    // only Lc (LeftChild) & Rc (RightChild) get Padding
    // lc inherites bleedToLeading from parent who is Lc and bleedToLeading
    // or parent is BleedToBothEdges
    // same applies to Rc
    ContainerBleedState previousBleedState = context.GetBleedState();

    if (elemSize == 1)
    {
        // items in signle column has no restriction
        context.SetBleedState(ContainerBleedState::BleedToBothEdges);
    }

    // Deserialize every element in the array
    for (const Json::Value& curJsonValue : elementArray)
    {
        // processing the cases where parent's bleed state is not restricted
        if (elemSize != 1)
        {
            if (currentIndex == 0)
            {
                context.SetBleedState(ContainerBleedState::BleedToLeading);
            }
            else if (currentIndex == endElemIndex)
            {
                context.SetBleedState(ContainerBleedState::BleedToTrailing);
            } else
            {
                context.SetBleedState(ContainerBleedState::BleedRestricted);
            }
        }

        // Parse the element
        auto el = Column::Deserialize(context, curJsonValue);
        if (el != nullptr)
        {
            elements.push_back(el);
            // restores the parent's bleed state
            context.SetBleedState(previousBleedState);
        }
        ++currentIndex;
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
