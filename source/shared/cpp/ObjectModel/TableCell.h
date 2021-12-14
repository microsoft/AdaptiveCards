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

    static std::shared_ptr<TableCell> DeserializeTableCellFromString(ParseContext& context, const std::string& root);
    static std::shared_ptr<TableCell> DeserializeTableCell(ParseContext& context, const Json::Value& root);
};
} // namespace AdaptiveCards
