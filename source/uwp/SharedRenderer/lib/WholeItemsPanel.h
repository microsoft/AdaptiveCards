// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "WholeItemsPanel.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct DECLSPEC_UUID("32934D77-6248-4915-BD2A-8F52EF6C8322") WholeItemsPanel : public WholeItemsPanelT<WholeItemsPanel, ITypePeek>
    {
    public:
        WholeItemsPanel() = default;

        winrt::Size MeasureOverride(winrt::Size const& availableSize);
        winrt::Size ArrangeOverride(winrt::Size const& finalSize);

        virtual void OnApplyTemplate(void);

        virtual winrt::hstring GetAltText();

        // Method used inside the component to reduce the number of temporary allocations
        void AppendAltText(std::wstring& buffer);

        void SetMainPanel(bool value);
        void SetAdaptiveHeight(bool value);
        static void SetBleedMargin(uint32_t bleedMargin);

        virtual bool IsAllContentClippedOut() { return ((m_measuredCount > 0) && (m_visibleCount == 0)); }
        virtual bool IsTruncated() { return m_isTruncated; }

        void AddElementToStretchablesList(winrt::UIElement const& element);
        bool IsUIElementInStretchableList(winrt::UIElement const& element);
        void SetVerticalContentAlignment(winrt::VerticalContentAlignment verticalContentAlignment)
        {
            m_verticalContentAlignment = verticalContentAlignment;
        }

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        static uint32_t s_bleedMargin;

        uint32_t m_visibleCount{};
        uint32_t m_measuredCount{};

        uint32_t m_stretchableItemCount{};
        float m_calculatedSize{};
        bool m_allElementsRendered{};
        winrt::VerticalContentAlignment m_verticalContentAlignment{};

        // true if this represents the mainPanel.
        // Some rules such as images vertical stretching only apply for this panel
        // This is set when generating the XAML Tree corresponding to the Tile's payload.
        bool m_isMainPanel = false;

        // true if the Panel has been truncated, i.e. if some items could not be displayed.
        // This is set by the panel during measure and read in case of nested panels
        bool m_isTruncated = false;

        // If true, avoid vertical whitespace before and after the render.
        bool m_adaptiveHeight = false;

        bool IsAnySubgroupTruncated(winrt::Panel const& panel);

        static void LayoutCroppedImage(winrt::Shape const& shape, double availableWidth, double availableHeight);

        static void AppendText(winrt::hstring const& text, std::wstring& buffer);

        static void AppendAltTextToUIElement(winrt::UIElement const& pUIElement, std::wstring& buffer);

        static winrt::hstring GetAltAsString(winrt::UIElement const& element);

        static bool HasExplicitSize(winrt::FrameworkElement const& element);
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct WholeItemsPanel : WholeItemsPanelT<WholeItemsPanel, implementation::WholeItemsPanel>
    {
    };
}
