// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    interface __declspec(uuid("0331D653-957C-4385-A327-D326750C10B6")) IElementTagContent : IInspectable
    {
    public:
        virtual HRESULT get_ColumnDefinition(_COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IColumnDefinition * *columnDefinition) = 0;
        virtual HRESULT get_AdaptiveCardElement(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement *
                                                *cardElement) = 0;
        virtual HRESULT get_Separator(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement * *separator) = 0;
        virtual HRESULT get_ParentPanel(_COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel * *parentPanel) = 0;
        // Auto size images hide themselves while they haven't finished loading even when they are expected to be
        // visible so the best way to track the intended visibility of the element and its separator is keeping this
        // flag to avoid comparing against the rendered visibility
        virtual HRESULT get_ExpectedVisibility(_Outptr_ boolean * expectedVisibility) = 0;
        virtual HRESULT set_ExpectedVisibility(boolean expectedVisibility) = 0;
        virtual HRESULT get_IsStretchable(_Outptr_ boolean * isStretchable) = 0;
        virtual HRESULT put_IsStretchable(boolean isStretchable) = 0;
    };

    class ElementTagContent
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, IElementTagContent>
    {
        AdaptiveRuntimeStringClass("ElementTagContent");

    public:
        ElementTagContent() : m_expectedVisibility(true), m_isStretchable(false) {}

        HRESULT RuntimeClassInitialize();

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* cardElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* separator,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IColumnDefinition* columnDefinition,
                                       boolean expectedVisibility,
                                       boolean isStretchable);

        virtual HRESULT get_ColumnDefinition(_COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IColumnDefinition** columnDefinition) override;
        virtual HRESULT get_AdaptiveCardElement(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement** cardElement) override;
        virtual HRESULT get_Separator(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** separator) override;
        virtual HRESULT get_ParentPanel(_COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel** parentPanel) override;
        virtual HRESULT get_ExpectedVisibility(_Outptr_ boolean* expectedVisibility) override;
        virtual HRESULT set_ExpectedVisibility(_In_ boolean expectedVisibility) override;
        virtual HRESULT get_IsStretchable(_Outptr_ boolean* isStretchable) override;
        virtual HRESULT put_IsStretchable(boolean isStretchable) override;

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement> m_cardElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::IColumnDefinition> m_columnDefinition;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_separator;
        Microsoft::WRL::WeakRef m_parentPanel;
        boolean m_expectedVisibility;
        boolean m_isStretchable;
    };
}
