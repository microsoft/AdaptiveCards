// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include <windows.ui.xaml.shapes.h>

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("32934D77-6248-4915-BD2A-8F52EF6C8322") WholeItemsPanel
        : public Microsoft::WRL::RuntimeClass<ABI::AdaptiveNamespace::IWholeItemsPanel,
                                              ABI::Windows::UI::Xaml::IFrameworkElementOverrides,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::ComposableBase<ABI::Windows::UI::Xaml::Controls::IPanelFactory>>
    {
        AdaptiveRuntimeStringClass(WholeItemsPanel);

    public:
        HRESULT STDMETHODCALLTYPE RuntimeClassInitialize();

        // IFrameworkElementOverrides
        virtual HRESULT STDMETHODCALLTYPE MeasureOverride(
            /* [in] */ ABI::Windows::Foundation::Size availableSize,
            /* [out][retval] */ __RPC__out ABI::Windows::Foundation::Size* returnValue);

        virtual HRESULT STDMETHODCALLTYPE ArrangeOverride(
            /* [in] */ ABI::Windows::Foundation::Size finalSize,
            /* [out][retval] */ __RPC__out ABI::Windows::Foundation::Size* returnValue);

        virtual HRESULT STDMETHODCALLTYPE OnApplyTemplate(void);

        virtual HRESULT STDMETHODCALLTYPE GetAltText(__RPC__out HSTRING* pResult) noexcept;

        // Method used inside the component to reduce the number of temporary allocations
        _Check_return_ HRESULT AppendAltText(_Inout_ std::wstring& buffer);

        void SetMainPanel(bool value);
        void SetAdaptiveHeight(bool value);
        static void SetBleedMargin(UINT bleedMargin);

        virtual HRESULT STDMETHODCALLTYPE IsAllContentClippedOut(__RPC__out boolean* pResult);
        virtual HRESULT STDMETHODCALLTYPE IsTruncated(__RPC__out boolean* pResult);

        void AddElementToStretchablesList(_In_ ABI::Windows::UI::Xaml::IUIElement* element);
        bool IsUIElementInStretchableList(_In_ ABI::Windows::UI::Xaml::IUIElement* element);
        void SetVerticalContentAlignment(_In_ ABI::AdaptiveNamespace::VerticalContentAlignment verticalContentAlignment);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:

        static UINT s_bleedMargin;

        unsigned int m_visibleCount{};
        unsigned int m_measuredCount{};

        unsigned int m_accessKeyCount{};
        float m_calculatedSize{};
        bool m_allElementsRendered{};
        std::set<std::string> m_stretchableItems;
        ABI::AdaptiveNamespace::VerticalContentAlignment m_verticalContentAlignment{};

        // true if this represents the mainPanel.
        // Some rules such as images vertical stretching only apply for this panel
        // This is set when generating the XAML Tree corresponding to the Tile's payload.
        bool m_isMainPanel = false;

        // true if the Panel has been truncated, i.e. if some items could not be displayed.
        // This is set by the panel during measure and read in case of nested panels
        bool m_isTruncated = false;

        // If true, avoid vertical whitespace before and after the render.
        bool m_adaptiveHeight = false;

        _Check_return_ HRESULT IsAnySubgroupTruncated(_In_ ABI::Windows::UI::Xaml::Controls::IPanel* pPanel, _Out_ bool* childTruncated);

        static _Check_return_ HRESULT LayoutCroppedImage(_In_ ABI::Windows::UI::Xaml::Shapes::IShape* pShape,
                                                         _In_ double availableWidth,
                                                         _In_ double availableHeight);

        static void AppendText(_In_ HSTRING hText, _Inout_ std::wstring& buffer);

        static _Check_return_ HRESULT AppendAltTextToUIElement(_In_ ABI::Windows::UI::Xaml::IUIElement* pUIElement,
                                                               _Inout_ std::wstring& buffer);

        static _Check_return_ HRESULT GetAltAsString(_In_ ABI::Windows::UI::Xaml::IUIElement* pElement, _Out_ HSTRING* pResult);

        static bool HasExplicitSize(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* element);
    };

    ActivatableClass(WholeItemsPanel);
}
