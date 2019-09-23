// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

namespace AdaptiveNamespace
{
    interface __declspec(uuid("0331D653-957C-4385-A327-D326750C10B6")) IElementTagContent : IInspectable
    {
    public:
        virtual HRESULT get_ColumnDefinition(_COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IColumnDefinition * *columnDefinition) = 0;
        virtual HRESULT get_AdaptiveCardElement(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement * *cardElement) = 0;
        virtual HRESULT get_Separator(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement * *separator) = 0;
        virtual HRESULT get_ParentPanel(_COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel * *parentPanel) = 0;
        // Auto size images hide themselves while they haven't finished loading even when they are expected to be
        // visible so the best way to track the intended visibility of the element and its separator is keeping this
        // flag to avoid comparing against the rendered visibility
        virtual HRESULT get_ExpectedVisibility(_Outptr_ boolean * expectedVisibility) = 0;
        virtual HRESULT set_ExpectedVisibility(_In_ boolean expectedVisibility) = 0;
    };

    class ElementTagContent
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, IElementTagContent>
    {
    public:
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* cardElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* separator,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IColumnDefinition* columnDefinition,
                                       _In_ boolean expectedVisibility);

        virtual HRESULT get_ColumnDefinition(_COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IColumnDefinition** columnDefinition) override;
        virtual HRESULT get_AdaptiveCardElement(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** cardElement) override;
        virtual HRESULT get_Separator(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** separator) override;
        virtual HRESULT get_ParentPanel(_COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel** parentPanel) override;
        virtual HRESULT get_ExpectedVisibility(_Outptr_ boolean* expectedVisibility) override;
        virtual HRESULT set_ExpectedVisibility(_In_ boolean expectedVisibility) override;

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardElement> m_cardElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::IColumnDefinition> m_columnDefinition;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_separator;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::IPanel> m_parentPanel;
        boolean m_expectedVisibility;
    };
}
