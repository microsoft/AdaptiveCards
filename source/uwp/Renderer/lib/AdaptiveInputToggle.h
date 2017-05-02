#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "InputToggle.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveInputToggle :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveInputToggle,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveInputToggle, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::InputToggle>& sharedInputToggle);

        // IAdaptiveInputToggle
        IFACEMETHODIMP get_Title(_Out_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_Value(_Out_ HSTRING* value);
        IFACEMETHODIMP put_Value(_In_ HSTRING value);

        IFACEMETHODIMP get_ValueOff(_Out_ HSTRING* value);
        IFACEMETHODIMP put_ValueOff(_In_ HSTRING value);

        IFACEMETHODIMP get_ValueOn(_Out_ HSTRING* value);
        IFACEMETHODIMP put_ValueOn(_In_ HSTRING value);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);

        IFACEMETHODIMP get_Separation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation);
        IFACEMETHODIMP put_Separation(_In_ ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation);

        IFACEMETHODIMP get_Speak(_Out_ HSTRING *speak);
        IFACEMETHODIMP put_Speak(_In_ HSTRING speak);

    private:
        std::shared_ptr<AdaptiveCards::InputToggle> m_sharedInputToggle;
    };

    ActivatableClass(AdaptiveInputToggle);
}}