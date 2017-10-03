#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Util.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveActionParserRegistration :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::Implements<ABI::AdaptiveCards::Uwp::IAdaptiveActionParserRegistration>,
        Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveActionParserRegistration, BaseTrust)

        typedef std::unordered_map<
            std::string,
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveActionParser>,
            CaseInsensitiveHash,
            CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveActionParserRegistration();
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveCards::Uwp::IAdaptiveActionParser* Parser);
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveActionParser** result);
        IFACEMETHODIMP Remove(_In_ HSTRING type);

    private:
        std::shared_ptr<RegistrationMap> m_registration;
    };

    class AdaptiveActionParserRegistrationStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveCards::Uwp::IAdaptiveActionParserRegistrationStatics>
    {
        InspectableClassStatic(RuntimeClass_AdaptiveCards_Uwp_AdaptiveActionParserRegistration, TrustLevel::BaseTrust);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveActionParserRegistration>(ppvObject);
        }
        
        // IAdaptiveActionParserRegistrationStatics
        IFACEMETHODIMP GetDefault(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveActionParserRegistration** result);
    };

    ActivatableClassWithFactory(AdaptiveActionParserRegistration, AdaptiveActionParserRegistrationStaticsImpl);
}}
