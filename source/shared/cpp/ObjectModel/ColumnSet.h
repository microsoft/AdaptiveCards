// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "CollectionTypeElement.h"

namespace AdaptiveSharedNamespace
{
    class Column;

    class ColumnSet : public CollectionTypeElement
    {
        friend class ColumnSetParser;

    public:
        ColumnSet();
        ColumnSet(const ColumnSet&) = default;
        ColumnSet(ColumnSet&&) = default;
        ColumnSet& operator=(const ColumnSet&) = default;
        ColumnSet& operator=(ColumnSet&&) = default;
        ~ColumnSet() = default;

        Json::Value SerializeToJsonValue() const override;
        void DeserializeChildren(ParseContext& context, const Json::Value& value) override;

        std::vector<std::shared_ptr<Column>>& GetColumns();
        const std::vector<std::shared_ptr<Column>>& GetColumns() const;

        void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

    private:
        void PopulateKnownPropertiesSet();

        std::vector<std::shared_ptr<Column>> m_columns;
    };

    class ColumnSetParser : public BaseCardElementParser
    {
    public:
        ColumnSetParser() = default;
        ColumnSetParser(const ColumnSetParser&) = default;
        ColumnSetParser(ColumnSetParser&&) = default;
        ColumnSetParser& operator=(const ColumnSetParser&) = default;
        ColumnSetParser& operator=(ColumnSetParser&&) = default;
        virtual ~ColumnSetParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
