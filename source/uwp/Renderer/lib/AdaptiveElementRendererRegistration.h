#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Util.h"

namespace AdaptiveCards { namespace Uwp {
    class AdaptiveElementRendererRegistration :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::Implements<ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration>,
        Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveElementRendererRegistration, BaseTrust)

        typedef std::unordered_map<
            std::string,
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveElementRenderer>,
            CaseInsensitiveHash,
            CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveElementRendererRegistration();
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveCards::Uwp::IAdaptiveElementRenderer* renderer);
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveElementRenderer** result);
        IFACEMETHODIMP Remove(_In_ HSTRING type);

    private:
        std::shared_ptr<RegistrationMap> m_registration;
    };

    ActivatableClass(AdaptiveElementRendererRegistration);
}}
