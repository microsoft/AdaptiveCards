#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "Container.h"
#include <windows.foundation.h>

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveColumn :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainer,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveColumn, BaseTrust)

    public:
        AdaptiveColumn();

        // IAdaptiveColumn
        IFACEMETHODIMP get_Size(_In_ HSTRING* size);
        IFACEMETHODIMP put_Size(_Out_ HSTRING size);

        // IAdaptiveContainer

        IFACEMETHODIMP get_Items(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>** items);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);

        IFACEMETHODIMP get_Separation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation);
        IFACEMETHODIMP put_Separation(_In_ ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation);

        IFACEMETHODIMP get_Speak(HSTRING *text);
        IFACEMETHODIMP put_Speak(HSTRING text);

    private:
        // TODO: Remove once Column shared object model type is ready. MSFT 11016964: Shared Object model: Card Elements
        Microsoft::WRL::Wrappers::HString m_size;

        // TODO: MSFT 11015796: Sync UWP Projection container classes to Shared object model counterparts.
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>> m_items;

        // Using Container as a backing element for now.
        // TODO: MSFT 11016964: Shared Object model: Card Elements
        std::unique_ptr<AdaptiveCards::Container> m_sharedColumn;
    };

    ActivatableClass(AdaptiveColumn);
}}
