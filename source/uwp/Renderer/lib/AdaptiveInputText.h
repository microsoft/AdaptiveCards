#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "InputText.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveInputText :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveInputText,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveInputText, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::InputText>& sharedInputText);

        // IAdaptiveInputText
        IFACEMETHODIMP get_Placeholder(_Out_ HSTRING* placeholder);
        IFACEMETHODIMP put_Placeholder(_In_ HSTRING placeholder);

        IFACEMETHODIMP get_Value(_Out_ HSTRING* text);
        IFACEMETHODIMP put_Value(_In_ HSTRING text);

        IFACEMETHODIMP get_IsMultiline(_Out_ boolean* isMultiline);
        IFACEMETHODIMP put_IsMultiline(_In_ boolean isMultiline);

        IFACEMETHODIMP get_MaxLength(_Out_ UINT32 *value);
        IFACEMETHODIMP put_MaxLength(_In_ UINT32 value);

        IFACEMETHODIMP get_TextInputStyle(_Out_ ABI::AdaptiveCards::XamlCardRenderer::TextInputStyle *textInputStyle);
        IFACEMETHODIMP put_TextInputStyle(_In_ ABI::AdaptiveCards::XamlCardRenderer::TextInputStyle textInputStyle);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);

        IFACEMETHODIMP get_Separation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation);
        IFACEMETHODIMP put_Separation(_In_ ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation);

        IFACEMETHODIMP get_Speak(_Out_ HSTRING* speak);
        IFACEMETHODIMP put_Speak(_In_ HSTRING speak);

    private:
        std::shared_ptr<AdaptiveCards::InputText> m_sharedInputText;
    };

    ActivatableClass(AdaptiveInputText);
}}