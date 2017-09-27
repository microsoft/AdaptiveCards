#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Util.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveElementParserRegistration :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::Implements<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveElementParserRegistration>,
        Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveElementParserRegistration, BaseTrust)

        typedef std::unordered_map<
            std::string,
            Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveElementParser>,
            CaseInsensitiveHash,
            CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveElementParserRegistration();
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveElementParser* Parser);
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveElementParser** result);
        IFACEMETHODIMP Remove(_In_ HSTRING type);

    private:
        std::shared_ptr<RegistrationMap> m_registration;
    };

    class AdaptiveElementParserRegistrationStaticsImpl WrlFinal
        : public Microsoft::WRL::AgileActivationFactory<
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveElementParserRegistrationStatics>
    {
        InspectableClassStatic(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveElementParserRegistration, TrustLevel::BaseTrust);

    public:
        IFACEMETHOD(ActivateInstance)(_COM_Outptr_ IInspectable** ppvObject) noexcept override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveElementParserRegistration>(ppvObject);
        }

        // IAdaptiveElementParserRegistrationStatics
        IFACEMETHODIMP GetDefault(_COM_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveElementParserRegistration** result);
    };

    ActivatableClassWithFactory(AdaptiveElementParserRegistration, AdaptiveElementParserRegistrationStaticsImpl);
}}
