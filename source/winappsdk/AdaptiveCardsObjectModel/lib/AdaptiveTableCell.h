// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TableCell.h"
#include "AdaptiveBackgroundImage.h"
#include "AdaptiveTableCell.g.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct DECLSPEC_UUID("8670BAA9-7DAC-4714-81F3-8D1553CD0E4E") AdaptiveTableCell : AdaptiveTableCellT < AdaptiveTableCell, ITypePeek>,
        AdaptiveCardElementBase
    {
        AdaptiveTableCell() : AdaptiveTableCell(std::make_shared<::AdaptiveCards::TableCell>()) {}
        AdaptiveTableCell(const std::shared_ptr<::AdaptiveCards::TableCell>& sharedTableCell);

        // IAdaptiveContainer
        property<winrt::Windows::Foundation::Collections::IVector<WinUI3::IAdaptiveCardElement>> Items;
        property_opt<WinUI3::VerticalContentAlignment> VerticalContentAlignment;
        property<WinUI3::AdaptiveBackgroundImage> BackgroundImage{nullptr};
        property_opt<bool> Rtl;

        // IAdaptiveContainerBase
        property<WinUI3::ContainerStyle> Style;
        property<WinUI3::IAdaptiveActionElement> SelectAction;
        property<bool> Bleed;
        property<WinUI3::BleedDirection> BleedDirection;
        property<uint32_t> MinHeight;

        // IAdaptiveCardElement
        auto ElementType() { return WinUI3::ElementType::TableCell; }

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::factory_implementation
{
    struct AdaptiveTableCell : AdaptiveTableCellT<AdaptiveTableCell, implementation::AdaptiveTableCell>
    {
    };
}
