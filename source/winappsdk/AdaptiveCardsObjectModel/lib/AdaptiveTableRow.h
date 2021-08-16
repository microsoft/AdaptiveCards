// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TableRow.h"
#include "AdaptiveTableRow.g.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct DECLSPEC_UUID("522B53A2-674E-43FA-A8A2-8595B2EE335A") AdaptiveTableRow : AdaptiveTableRowT<AdaptiveTableRow, ITypePeek>, AdaptiveCardElementBase
    {
        AdaptiveTableRow() : AdaptiveTableRow(std::make_shared<::AdaptiveCards::TableRow>()) {}
        AdaptiveTableRow(const std::shared_ptr<::AdaptiveCards::TableRow>& sharedTableRow);

        property<winrt::Windows::Foundation::Collections::IVector<WinUI3::AdaptiveTableCell>> Cells;
        property_opt<WinUI3::VerticalContentAlignment> VerticalCellContentAlignment;
        property_opt<WinUI3::HAlignment> HorizontalCellContentAlignment;
        property<WinUI3::ContainerStyle> Style;

        auto ElementType() { return WinUI3::ElementType::TableRow; }

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        // AdaptiveCardElementBase
        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;
    };
}

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::factory_implementation
{
    struct AdaptiveTableRow : AdaptiveTableRowT<AdaptiveTableRow, implementation::AdaptiveTableRow>
    {
    };
}
