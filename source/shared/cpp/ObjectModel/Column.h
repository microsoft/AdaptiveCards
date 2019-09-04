// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "Enums.h"
#include "BackgroundImage.h"
#include "BaseActionElement.h"
#include "CollectionTypeElement.h"

namespace AdaptiveSharedNamespace
{
    class BaseActionElement;

    class Column : public CollectionTypeElement
    {
    public:
        Column();

        std::string Serialize() const override;
        Json::Value SerializeToJsonValue() const override;

        void DeserializeChildren(ParseContext& context, const Json::Value& value) override;

        std::string GetWidth() const;
        void SetWidth(const std::string& value);
        void SetWidth(const std::string& value,
                      std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>>* warnings);

        // explicit width takes precedence over relative width
        int GetPixelWidth() const;
        void SetPixelWidth(const int value);

        std::vector<std::shared_ptr<BaseCardElement>>& GetItems();
        const std::vector<std::shared_ptr<BaseCardElement>>& GetItems() const;

        void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

    private:
        void PopulateKnownPropertiesSet() override;
        std::string m_width;
        unsigned int m_pixelWidth;
        std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>> m_items;
    };

    class ColumnParser : public BaseCardElementParser
    {
    public:
        ColumnParser() = default;
        ColumnParser(const ColumnParser&) = default;
        ColumnParser(ColumnParser&&) = default;
        ColumnParser& operator=(const ColumnParser&) = default;
        ColumnParser& operator=(ColumnParser&&) = default;
        virtual ~ColumnParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
