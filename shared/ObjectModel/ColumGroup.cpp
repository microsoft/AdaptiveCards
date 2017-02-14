#include "ColumnGroup.h"

using namespace AdaptiveCards;


ColumnGroup::ColumnGroup() : BaseCardElement(CardElementType::ColumnGroup, nullptr, HorizontalAlignment::Left, CardElementSize::Auto, "")
{
}

ColumnGroup::ColumnGroup(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, CardElementSize size, std::string speak,
    std::vector<std::shared_ptr<Column>>& columns) :
    BaseCardElement(CardElementType::ColumnGroup, container, horizontalAlignment, size, speak),
    m_columns(columns)
{
}

std::vector<std::shared_ptr<Column>>& ColumnGroup::GetColumns()
{
    return m_columns;
}

std::shared_ptr<ColumnGroup> ColumnGroup::Deserialize(const Json::Value & root)
{
    return std::shared_ptr<ColumnGroup>();
}

std::string ColumnGroup::Serialize()
{
    return std::string();
}
