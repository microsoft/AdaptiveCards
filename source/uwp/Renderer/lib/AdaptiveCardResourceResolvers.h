#pragma once
#include "AdaptiveCards.Uwp.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveCardResourceResolvers :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveCardResourceResolvers>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveCardResourceResolvers, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING scheme, _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardResourceResolver* resolver);
        IFACEMETHODIMP Get(_In_ HSTRING scheme, _Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveCardResourceResolver** resolver);

    private:
        std::map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCardResourceResolver>> m_resourceResolvers;
    };

    ActivatableClass(AdaptiveCardResourceResolvers);
}}