#include "pch.h"
#include "ColumnSet.h"
#include "Column.h"
#include "ParseUtil.h"
#include "Image.h"
#include "TextBlock.h"
#include "Util.h"

using namespace AdaptiveSharedNamespace;

ColumnSet::ColumnSet() : CollectionTypeElement(CardElementType::ColumnSet)
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

    // Child's bleed get more restricted as we walk down the tree
    // until padding is reset
    // padding get reset when padding is added to a collection type element
    // only left child LC or right child RC have access to the padding of their parents
    // but if parent also has restriction such as BleedToLeft and BleedToRight,
    // only child that has same restriction get bleed property
    // for example, if inherited bleed state was BleedToLeft, only LC gets the bleed,
    // the rest of children cannot bleed.
    const ContainerBleedDirection previousBleedState = context.GetBleedDirection();

    // Deserialize every element in the array
    for (Json::Value& curJsonValue : elementArray)
    {
        ContainerBleedDirection currentBleedState = previousBleedState;

        // Items in single column have no restriction
        if (elemSize != 1)
        {
            if (currentIndex == 0)
            {
                // If we're in the left column, we can only bleed left
                if (previousBleedState != ContainerBleedDirection::BleedToLeading)
                {
                    currentBleedState = (previousBleedState == ContainerBleedDirection::BleedToBothEdges) ?
                        ContainerBleedDirection::BleedToLeading :
                        ContainerBleedDirection::BleedRestricted;
                }
            }
            else if (currentIndex == endElemIndex)
            {
                // If we're in the right column, we can only bleed right
                if (previousBleedState != ContainerBleedDirection::BleedToTrailing)
                {
                    currentBleedState = (previousBleedState == ContainerBleedDirection::BleedToBothEdges) ?
                        ContainerBleedDirection::BleedToTrailing :
                        ContainerBleedDirection::BleedRestricted;
                }
            }
            else
            {
                // If we're in an internal column, we can't bleed
                currentBleedState = ContainerBleedDirection::BleedRestricted;
            }
        }

        context.PushBleedDirection(currentBleedState);

        std::shared_ptr<BaseElement> el;
        const std::string typeString = ParseUtil::GetString(curJsonValue, AdaptiveCardSchemaKey::Type, "Column", false);
        if (typeString.compare("Column") != 0)
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Unable to parse element of type " + typeString);
        }

        // we are covering the case where type is left blank in the client's json
        curJsonValue[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = typeString;

        BaseElement::ParseJsonObject<Column>(context, curJsonValue, el);

        // Parse the element
        if (el != nullptr)
        {
            elements.push_back(std::static_pointer_cast<Column>(el));
        }

        // restores the parent's bleed state
        context.PopBleedDirection();

        ++currentIndex;
    }

    m_columns = std::move(elements);
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

std::shared_ptr<BaseCardElement> ColumnSetParser::Deserialize(ParseContext& context, const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::ColumnSet);

    auto container = CollectionTypeElement::Deserialize<ColumnSet>(context, value);

    return container;
}

std::shared_ptr<BaseCardElement> ColumnSetParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ColumnSetParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
