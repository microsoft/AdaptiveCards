// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "ElementTagContent.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct DECLSPEC_UUID("0331D653-957C-4385-A327-D326750C10B6") ElementTagContent
        : public ElementTagContentT<ElementTagContent, ITypePeek>
    {
        ElementTagContent() = default;
        ElementTagContent(winrt::IAdaptiveCardElement const& cardElement,
                          winrt::Panel const& parentPanel,
                          winrt::UIElement const& separator,
                          winrt::ColumnDefinition const& columnDefinition,
                          boolean expectedVisibility,
                          boolean isStretchable);

        property<bool> ExpectedVisibility;
        property<bool> IsStretchable;

        winrt::UIElement Separator() { return m_separator; }
        winrt::Panel ParentPanel() { return m_parentPanel; }
        winrt::ColumnDefinition ColumnDefinition() { return m_columnDefinition; }
        winrt::IAdaptiveCardElement CardElement() { return m_cardElement; }

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        winrt::UIElement m_separator{nullptr};
        winrt::Panel m_parentPanel{nullptr};
        winrt::ColumnDefinition m_columnDefinition;
        winrt::IAdaptiveCardElement m_cardElement;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct ElementTagContent : ElementTagContentT<ElementTagContent, implementation::ElementTagContent>
    {
    };
}
