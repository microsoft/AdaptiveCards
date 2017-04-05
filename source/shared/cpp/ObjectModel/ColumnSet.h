#pragma once

#include "pch.h"
#include "Enums.h"
#include "BaseCardElement.h"
#include "Column.h"

namespace AdaptiveCards
{
class BaseCardElement;
class Column;
class ColumnSet : public BaseCardElement
{
public:
    ColumnSet();
    ColumnSet(std::vector<std::shared_ptr<Column>>& columns);

    virtual std::string Serialize();

    std::vector<std::shared_ptr<Column>>& GetColumns();
    const std::vector<std::shared_ptr<Column>>& GetColumns() const;
    static std::shared_ptr<ColumnSet> Deserialize(const Json::Value& root);

private:
    static const std::unordered_map<CardElementType, std::function<std::shared_ptr<Column>(const Json::Value&)>> ColumnParser;
    std::vector<std::shared_ptr<Column>> m_columns;
};
}