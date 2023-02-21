// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Table.h"
#include "AdaptiveTable.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct DECLSPEC_UUID("CA752EA7-A7D4-4D1A-BAA3-3318A29FE52D") AdaptiveTable : AdaptiveTableT<AdaptiveTable, ITypePeek>,
        AdaptiveCardElementBase
    {
        AdaptiveTable() : AdaptiveTable(std::make_shared<::AdaptiveCards::Table>()) {}
        AdaptiveTable(std::shared_ptr<::AdaptiveCards::Table> const& sharedTable);

        auto ElementType() { return Xaml_OM::ElementType::Table; }

        property<winrt::Windows::Foundation::Collections::IVector<Xaml_OM::AdaptiveTableRow>> Rows;
        property<winrt::Windows::Foundation::Collections::IVector<Xaml_OM::AdaptiveTableColumnDefinition>> Columns;
        property<bool> ShowGridLines;
        property<bool> FirstRowAsHeaders;
        property_opt<Xaml_OM::VerticalContentAlignment> VerticalCellContentAlignment;
        property_opt<Xaml_OM::HAlignment> HorizontalCellContentAlignment;
        property<Xaml_OM::ContainerStyle> GridStyle;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        // AdaptiveCardElementBase
        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveTable : AdaptiveTableT<AdaptiveTable, implementation::AdaptiveTable>
    {
    };
}
