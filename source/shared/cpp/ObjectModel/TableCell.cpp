// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "TableCell.h"

using namespace AdaptiveCards;

namespace AdaptiveCards
{
    TableCell::TableCell() : Container(CardElementType::TableCell) {}

    std::shared_ptr<BaseCardElement> TableCellParser::Deserialize(ParseContext& context, const Json::Value& value)
    {
        ParseUtil::ExpectTypeString(value, CardElementType::TableCell);

        auto cell = CollectionTypeElement::Deserialize<TableCell>(context, value);
        cell->SetRtl(ParseUtil::GetOptionalBool(value, AdaptiveCardSchemaKey::Rtl));

        return cell;
    }

    std::shared_ptr<BaseCardElement> TableCellParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
    {
        return TableCellParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
    }
}
