#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "Fact.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveFact :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveFact>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveFact, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::Fact>& sharedFact);

        // IAdaptiveFact
        IFACEMETHODIMP get_Title(_In_ HSTRING* title);
        IFACEMETHODIMP put_Title(_Out_ HSTRING title);

        IFACEMETHODIMP get_Value(_In_ HSTRING* value);
        IFACEMETHODIMP put_Value(_Out_ HSTRING value);

        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Uwp::ElementType* elementType);

    private:
        std::shared_ptr<AdaptiveCards::Fact> m_sharedFact;
    };

    ActivatableClass(AdaptiveFact);
}}