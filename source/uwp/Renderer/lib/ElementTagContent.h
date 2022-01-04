// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once
#include "ElementTagContent.g.h"
#include "XamlBuilder.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct DECLSPEC_UUID("0331D653-957C-4385-A327-D326750C10B6") ElementTagContent
        : public ElementTagContentT<ElementTagContent, ITypePeek>
    {
        ElementTagContent() = default;
        ElementTagContent(rtom::IAdaptiveCardElement const& cardElement,
                          rtxaml::Controls::Panel const& parentPanel,
                          rtxaml::UIElement const& separator,
                          rtxaml::Controls::ColumnDefinition const& columnDefinition,
                          boolean expectedVisibility,
                          boolean isStretchable);

        property<bool> ExpectedVisibility;
        property<bool> IsStretchable;

        rtxaml::UIElement Separator() { return m_separator; }
        rtxaml::Controls::Panel ParentPanel() { return m_parentPanel; }
        rtxaml::Controls::ColumnDefinition ColumnDefinition() { return m_columnDefinition; }
        rtom::IAdaptiveCardElement CardElement() { return m_cardElement; }

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        rtxaml::UIElement m_separator{nullptr};
        rtxaml::Controls::Panel m_parentPanel{nullptr};
        rtxaml::Controls::ColumnDefinition m_columnDefinition;
        rtom::IAdaptiveCardElement m_cardElement;
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct ElementTagContent : ElementTagContentT<ElementTagContent, implementation::ElementTagContent>
    {
    };
}
