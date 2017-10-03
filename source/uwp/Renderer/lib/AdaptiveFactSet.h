#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "FactSet.h"
#include <windows.foundation.h>

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveFactSet :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveFactSet,
            ABI::AdaptiveCards::Uwp::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveFactSet, BaseTrust)

    public:
        AdaptiveFactSet();

        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::FactSet>& sharedFactSet);

        // IAdaptiveFactSet
        IFACEMETHODIMP get_Facts(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveFact*>** columns);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Uwp::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::Uwp::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::Uwp::Spacing spacing);

        IFACEMETHODIMP get_Separator(boolean* separator);
        IFACEMETHODIMP put_Separator(boolean separator);

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value);

    private:
        // TODO: MSFT 11015796: Sync UWP Projection container classes to Shared object model counterparts.
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveFact*>> m_facts;

        //Using a Container as backing element for now
        std::shared_ptr<AdaptiveCards::FactSet> m_sharedFactSet;
    };

    ActivatableClass(AdaptiveFactSet);
}}
