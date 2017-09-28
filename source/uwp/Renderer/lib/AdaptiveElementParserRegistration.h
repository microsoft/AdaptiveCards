#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Util.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveElementParserRegistration :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::Implements<ABI::AdaptiveCards::Uwp::IAdaptiveElementParserRegistration>,
        Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveElementParserRegistration, BaseTrust)

        typedef std::unordered_map<
            std::string,
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveElementParser>,
            CaseInsensitiveHash,
            CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveElementParserRegistration();
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveCards::Uwp::IAdaptiveElementParser* Parser);
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveElementParser** result);
        IFACEMETHODIMP Remove(_In_ HSTRING type);

    private:
        std::shared_ptr<RegistrationMap> m_registration;
    };

    class AdaptiveElementParserRegistrationStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveCards::Uwp::IAdaptiveElementParserRegistrationStatics>
    {
        InspectableClassStatic(RuntimeClass_AdaptiveCards_Uwp_AdaptiveElementParserRegistration, TrustLevel::BaseTrust);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveElementParserRegistration>(ppvObject);
        }

        // IAdaptiveElementParserRegistrationStatics
        IFACEMETHODIMP GetDefault(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveElementParserRegistration** result);
    };

    ActivatableClassWithFactory(AdaptiveElementParserRegistration, AdaptiveElementParserRegistrationStaticsImpl);
}}
