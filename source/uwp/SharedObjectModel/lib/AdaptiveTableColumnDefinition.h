// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TableColumnDefinition.h"
#include "AdaptiveTableColumnDefinition.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("3ED8BE31-8D92-461B-8E8F-2C6C0F78E2ED") AdaptiveTableColumnDefinition
        : AdaptiveTableColumnDefinitionT<AdaptiveTableColumnDefinition, ITypePeek>
    {
        AdaptiveTableColumnDefinition() :
            AdaptiveTableColumnDefinition(std::make_shared<::AdaptiveCards::TableColumnDefinition>())
        {
        }
        AdaptiveTableColumnDefinition(std::shared_ptr<::AdaptiveCards::TableColumnDefinition> const& sharedTableColumnDefinition);

        property_opt<Uwp::VerticalContentAlignment> VerticalCellContentAlignment;
        property_opt<Uwp::HAlignment> HorizontalCellContentAlignment;
        property_opt<uint32_t> Width;
        property_opt<uint32_t> PixelWidth;

        virtual std::shared_ptr<::AdaptiveCards::TableColumnDefinition> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveTableColumnDefinition
        : AdaptiveTableColumnDefinitionT<AdaptiveTableColumnDefinition, implementation::AdaptiveTableColumnDefinition>
    {
    };
}
