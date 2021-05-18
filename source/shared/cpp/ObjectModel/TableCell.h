// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "Container.h"

namespace AdaptiveCards
{
    class BaseCardElement;

    class TableCell : public Container
    {
    public:
        TableCell();
        TableCell(const TableCell&) = default;
        TableCell(TableCell&&) = default;
        TableCell& operator=(const TableCell&) = default;
        TableCell& operator=(TableCell&&) = default;
        virtual ~TableCell() = default;
    };

    class TableCellParser : public ContainerParser
    {
    public:
        TableCellParser() = default;
        TableCellParser(const TableCellParser&) = default;
        TableCellParser(TableCellParser&&) = default;
        TableCellParser& operator=(const TableCellParser&) = default;
        TableCellParser& operator=(TableCellParser&&) = default;
        virtual ~TableCellParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
