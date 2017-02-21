#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "Container.h"
#include <windows.foundation.h>

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveContainer :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainer,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveContainer, BaseTrust)

    public:
        AdaptiveContainer();

        // IAdaptiveContainer
        IFACEMETHODIMP get_StartGroup(_In_ boolean* uri);
        IFACEMETHODIMP put_StartGroup(_Out_ boolean uri);

        IFACEMETHODIMP get_Items(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>** items);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);
        IFACEMETHODIMP put_ElementType(_In_ ABI::AdaptiveCards::XamlCardRenderer::ElementType elementType);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveCards::XamlCardRenderer::CardElementSize* size);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveCards::XamlCardRenderer::CardElementSize size);

    private:
        // TODO: MSTF 11015796: Sync UWP Projection containers to Shared object model.
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>> m_items;
        std::unique_ptr<AdaptiveCards::Container> m_container;
    };

    ActivatableClass(AdaptiveContainer);
}
}