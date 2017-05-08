#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "InputChoice.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveInputChoice :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveInputChoice>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveInputChoice, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::InputChoice>& sharedInputChoice);

        // IAdaptiveInputChoice
        IFACEMETHODIMP get_Title(_In_ HSTRING* title);
        IFACEMETHODIMP put_Title(_Out_ HSTRING title);

        IFACEMETHODIMP get_Value(_In_ HSTRING* value);
        IFACEMETHODIMP put_Value(_Out_ HSTRING value);

        IFACEMETHODIMP get_Speak(_In_ HSTRING* speak);
        IFACEMETHODIMP put_Speak(_Out_ HSTRING speak);

        IFACEMETHODIMP get_IsSelected(_Out_ boolean* isSelected);
        IFACEMETHODIMP put_IsSelected(_In_ boolean isSelected);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);

    private:
        std::shared_ptr<AdaptiveCards::InputChoice> m_sharedInputChoice;
    };

    ActivatableClass(AdaptiveInputChoice);
}}