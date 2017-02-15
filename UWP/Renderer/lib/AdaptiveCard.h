#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveCard :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement
        >
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveCard, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize();

        // IAdaptiveCard
        IFACEMETHODIMP get_Items(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>** items);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);
        IFACEMETHODIMP put_ElementType(_In_ ABI::AdaptiveCards::XamlCardRenderer::ElementType elementType);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveCards::XamlCardRenderer::CardElementSize* size);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveCards::XamlCardRenderer::CardElementSize size);

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>> m_items;
        ABI::AdaptiveCards::XamlCardRenderer::CardElementSize m_size;
    };

    ActivatableClass(AdaptiveCard);
}}