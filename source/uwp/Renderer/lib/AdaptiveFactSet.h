#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "FactSet.h"
#include <windows.foundation.h>

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveFactSet :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFactSet,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveFactSet, BaseTrust)

    public:
        AdaptiveFactSet();

        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::FactSet>& sharedFactSet);

        // IAdaptiveFactSet
        IFACEMETHODIMP get_Facts(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*>** columns);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::XamlCardRenderer::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::XamlCardRenderer::Spacing spacing);

        IFACEMETHODIMP get_Separator(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator** separator);
        IFACEMETHODIMP put_Separator(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator* separator);

        IFACEMETHODIMP get_Speak(_In_ HSTRING *speak);
        IFACEMETHODIMP put_Speak(_Out_ HSTRING speak);

    private:
        // TODO: MSFT 11015796: Sync UWP Projection container classes to Shared object model counterparts.
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*>> m_facts;

        //Using a Container as backing element for now
        std::shared_ptr<AdaptiveCards::FactSet> m_sharedFactSet;
    };

    ActivatableClass(AdaptiveFactSet);
}}
