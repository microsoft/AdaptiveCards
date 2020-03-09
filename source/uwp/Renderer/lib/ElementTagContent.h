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
        virtual HRESULT get_IsStretchable(_Outptr_ boolean * isStretchable) = 0;
        virtual HRESULT put_IsStretchable(boolean isStretchable) = 0;
    };

    class ElementTagContent
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, IElementTagContent>
    {
    public:
        ElementTagContent() : m_isStretchable(false) {}

        HRESULT RuntimeClassInitialize();

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* cardElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* separator,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IColumnDefinition* columnDefinition,
                                        boolean isStretchable);

        virtual HRESULT get_ColumnDefinition(_COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IColumnDefinition** columnDefinition) override;
        virtual HRESULT get_AdaptiveCardElement(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** cardElement) override;
        virtual HRESULT get_Separator(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** separator) override;
        virtual HRESULT get_ParentPanel(_COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel** parentPanel) override;
        virtual HRESULT get_IsStretchable(_Outptr_ boolean* isStretchable) override;
        virtual HRESULT put_IsStretchable(boolean isStretchable) override;

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardElement> m_cardElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::IColumnDefinition> m_columnDefinition;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_separator;
        Microsoft::WRL::WeakRef m_parentPanel;
        boolean m_isStretchable;
    };
}
