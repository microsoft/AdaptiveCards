// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "TableColumnDefinition.h"
#include "Util.h"

namespace AdaptiveCards
{
    TableColumnDefinition::TableColumnDefinition() :
        m_horizontalCellContentAlignment(HorizontalAlignment::Left),
        m_verticalCellContentAlignment(VerticalContentAlignment::Top), m_pixelWidth{}, m_width{}
    {
    }

    std::string TableColumnDefinition::Serialize() { return ParseUtil::JsonToString(SerializeToJsonValue()); }

    Json::Value TableColumnDefinition::SerializeToJsonValue()
    {
        Json::Value root;

        if (m_horizontalCellContentAlignment.has_value())
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalCellContentAlignment)] =
                HorizontalAlignmentToString(m_horizontalCellContentAlignment.value_or(HorizontalAlignment::Left));
        }

        if (m_verticalCellContentAlignment.has_value())
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalCellContentAlignment)] =
                VerticalContentAlignmentToString(m_verticalCellContentAlignment.value_or(VerticalContentAlignment::Top));
        }

        if (m_width.has_value())
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Width)] = *m_width;
        }

        if (m_pixelWidth.has_value())
        {
            std::ostringstream pixelStr;
            pixelStr << *m_pixelWidth << "px";
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Width)] = pixelStr.str();
        }

        return root;
    }

    std::optional<HorizontalAlignment> TableColumnDefinition::GetHorizontalCellContentAlignment() const
    {
        return m_horizontalCellContentAlignment;
    }

    void TableColumnDefinition::SetHorizontalCellContentAlignment(std::optional<HorizontalAlignment> value)
    {
        m_horizontalCellContentAlignment = value;
    }

    std::optional<VerticalContentAlignment> TableColumnDefinition::GetVerticalCellContentAlignment() const
    {
        return m_verticalCellContentAlignment;
    }

    void TableColumnDefinition::SetVerticalCellContentAlignment(std::optional<VerticalContentAlignment> value)
    {
        m_verticalCellContentAlignment = value;
    }

    std::optional<unsigned int> TableColumnDefinition::GetWidth() const { return m_width; }

    void TableColumnDefinition::SetWidth(const std::optional<unsigned int>& value)
    {
        m_pixelWidth = {};
        m_width = value;
    }

    std::optional<unsigned int> TableColumnDefinition::GetPixelWidth() const { return m_pixelWidth; }

    void TableColumnDefinition::SetPixelWidth(const std::optional<unsigned int>& value)
    {
        m_width = {};
        m_pixelWidth = value;
    }

    std::shared_ptr<TableColumnDefinition> TableColumnDefinition::Deserialize(ParseContext& context, const Json::Value& json)
    {
        auto tableColumnDefinition = std::make_shared<TableColumnDefinition>();

        tableColumnDefinition->SetHorizontalCellContentAlignment(ParseUtil::GetOptionalEnumValue<HorizontalAlignment>(
            json, AdaptiveCardSchemaKey::HorizontalCellContentAlignment, HorizontalAlignmentFromString));
        tableColumnDefinition->SetVerticalCellContentAlignment(ParseUtil::GetOptionalEnumValue<VerticalContentAlignment>(
            json, AdaptiveCardSchemaKey::VerticalCellContentAlignment, VerticalContentAlignmentFromString));

        if (const auto& widthValue = ParseUtil::ExtractJsonValue(json, AdaptiveCardSchemaKey::Width, false); !widthValue.empty())
        {
            if (widthValue.isInt())
            {
                tableColumnDefinition->SetWidth(widthValue.asInt());
            }
            else if (widthValue.isString())
            {
                if (const auto& pixelWidth = ParseSizeForPixelSize(widthValue.asString(), &(context.warnings));
                    pixelWidth.has_value())
                {
                    tableColumnDefinition->SetPixelWidth(*pixelWidth);
                }
                else if (!pixelWidth.has_value())
                {
                    context.warnings.emplace_back(
                        std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::InvalidDimensionSpecified,
                                                                   "Supplied value for \"width\" could not be parsed"));
                }
            }
            else
            {
                context.warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::InvalidValue,
                                                                                         "Invalid type for \"width\""));
            }
        }

        return tableColumnDefinition;
    }

    std::shared_ptr<TableColumnDefinition> TableColumnDefinition::DeserializeFromString(ParseContext& context,
                                                                                        const std::string& jsonString)
    {
        return Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
    }
}
