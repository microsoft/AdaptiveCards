// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

namespace AdaptiveCards
{
class AdaptiveCardParseWarning;
class ParseContext;

class TableColumnDefinition
{
public:
    TableColumnDefinition();

    std::string Serialize();
    Json::Value SerializeToJsonValue();

    std::optional<HorizontalAlignment> GetHorizontalCellContentAlignment() const;
    void SetHorizontalCellContentAlignment(std::optional<HorizontalAlignment> value);

    std::optional<VerticalContentAlignment> GetVerticalCellContentAlignment() const;
    void SetVerticalCellContentAlignment(std::optional<VerticalContentAlignment> value);

    std::optional<unsigned int> GetWidth() const;
    void SetWidth(const std::optional<unsigned int>& value);

    // explicit width takes precedence over relative width
    std::optional<unsigned int> GetPixelWidth() const;
    void SetPixelWidth(const std::optional<unsigned int>& value);

    static std::shared_ptr<AdaptiveCards::TableColumnDefinition> Deserialize(ParseContext& context, const Json::Value& root);
    static std::shared_ptr<AdaptiveCards::TableColumnDefinition> DeserializeFromString(ParseContext& context, const std::string& jsonString);

private:
    std::optional<HorizontalAlignment> m_horizontalCellContentAlignment;
    std::optional<VerticalContentAlignment> m_verticalCellContentAlignment;

    std::optional<unsigned int> m_pixelWidth;
    std::optional<unsigned int> m_width;
};
} // namespace AdaptiveCards
