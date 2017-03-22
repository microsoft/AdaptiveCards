#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "Container.h"
#include <windows.foundation.h>

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveColumnSet :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumnSet,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveColumnSet, BaseTrust)

    public:
        AdaptiveColumnSet();

        // IAdaptiveColumnSet
        IFACEMETHODIMP get_Columns(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*>** columns);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);

        IFACEMETHODIMP get_Separation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation);
        IFACEMETHODIMP put_Separation(_In_ ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation);

        IFACEMETHODIMP get_Speak(_In_ HSTRING *speak);
        IFACEMETHODIMP put_Speak(_Out_ HSTRING speak);

    private:
        // TODO: MSFT 11015796: Sync UWP Projection container classes to Shared object model counterparts.
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*>> m_columns;

        //Using a Container as backing element for now
        std::shared_ptr<AdaptiveCards::Container> m_sharedColumnSet;
    };

    ActivatableClass(AdaptiveColumnSet);
}}
