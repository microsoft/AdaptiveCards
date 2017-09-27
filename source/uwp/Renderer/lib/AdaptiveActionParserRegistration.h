#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Util.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveActionParserRegistration :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::Implements<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionParserRegistration>,
        Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveActionParserRegistration, BaseTrust)

        typedef std::unordered_map<
            std::string,
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionParser>,
            CaseInsensitiveHash,
            CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveActionParserRegistration();
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionParser* Parser);
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionParser** result);
        IFACEMETHODIMP Remove(_In_ HSTRING type);

    private:
        std::shared_ptr<RegistrationMap> m_registration;
    };

    class AdaptiveActionParserRegistrationStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionParserRegistrationStatics>
    {
        InspectableClassStatic(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveActionParserRegistration, TrustLevel::BaseTrust);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveActionParserRegistration>(ppvObject);
        }
        
        // IAdaptiveActionParserRegistrationStatics
        IFACEMETHODIMP GetDefault(_COM_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionParserRegistration** result);
    };

    ActivatableClassWithFactory(AdaptiveActionParserRegistration, AdaptiveActionParserRegistrationStaticsImpl);
}}
