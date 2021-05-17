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

        HorizontalAlignment GetHorizontalCellContentAlignment() const;
        void SetHorizontalCellContentAlignment(HorizontalAlignment value);

        VerticalAlignment GetVerticalCellContentAlignment() const;
        void SetVerticalCellContentAlignment(VerticalAlignment value);

        std::optional<unsigned int> GetWidth() const;
        void SetWidth(const std::optional<unsigned int>& value);

        // explicit width takes precedence over relative width
        std::optional<unsigned int> GetPixelWidth() const;
        void SetPixelWidth(const std::optional<unsigned int>& value);

        static std::shared_ptr<AdaptiveCards::TableColumnDefinition> Deserialize(ParseContext& context, const Json::Value& root);
        static std::shared_ptr<AdaptiveCards::TableColumnDefinition> DeserializeFromString(ParseContext& context,
                                                                                           const std::string& jsonString);

    private:
        HorizontalAlignment m_horizontalCellContentAlignment;
        VerticalAlignment m_verticalCellContentAlignment;

        std::optional<unsigned int> m_pixelWidth;
        std::optional<unsigned int> m_width;
    };
}
