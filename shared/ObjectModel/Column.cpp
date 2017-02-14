#include "Column.h"

using namespace AdaptiveCards;

Column::Column()
{
}

Column::Column(std::string weight) : m_weight(weight)
{
}

std::shared_ptr<Column> AdaptiveCards::Column::Deserialize(const Json::Value & root)
{
    return std::shared_ptr<Column>();
}

std::string AdaptiveCards::Column::Serialize()
{
    return std::string();
}
