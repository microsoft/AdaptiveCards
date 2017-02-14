#pragma once

#include "pch.h"
#include "Container.h"
#include "ColumnGroup.h"
#include "Enums.h"

namespace AdaptiveCards
{
    class Column : public Container
    {
    public:
        Column();
        Column(std::string weight);

        static std::shared_ptr<Column> Deserialize(const Json::Value& root);

        std::string Serialize();

    private:
        std::string m_weight;
    };
}