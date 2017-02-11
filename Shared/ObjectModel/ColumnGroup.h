#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "Column.h"
#include "Enums.h"

namespace AdaptiveCards
{
    class Column;
    class ColumnGroup : BaseCardElement
    {
    public:
        ColumnGroup();
        ColumnGroup(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, CardElementSize size, std::string speak,
            std::vector<std::shared_ptr<Column>>& columns = std::vector<std::shared_ptr<Column>>());

        std::vector<std::shared_ptr<Column>>& GetColumns();

        static std::shared_ptr<ColumnGroup> Deserialize(const Json::Value& root);

        virtual std::string Serialize();

    private:
        std::vector<std::shared_ptr<Column>> m_columns;
    };
}