// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "TableCell.h"

using namespace AdaptiveCards;

namespace AdaptiveCards
{
TableCell::TableCell() : Container(CardElementType::TableCell)
{
}

std::shared_ptr<TableCell> TableCell::DeserializeTableCell(ParseContext& context, const Json::Value& value)
{
    const auto& idProperty = ParseUtil::GetString(value, AdaptiveCardSchemaKey::Id);
    const InternalId internalId = InternalId::Next();

    context.PushElement(idProperty, internalId);

    auto cell = StyledCollectionElement::Deserialize<TableCell>(context, value);
    cell->SetRtl(ParseUtil::GetOptionalBool(value, AdaptiveCardSchemaKey::Rtl));

    context.PopElement();

    return cell;
}

std::shared_ptr<TableCell> TableCell::DeserializeTableCellFromString(ParseContext& context, const std::string& jsonString)
{
    return TableCell::DeserializeTableCell(context, ParseUtil::GetJsonValueFromString(jsonString));
}
} // namespace AdaptiveCards
