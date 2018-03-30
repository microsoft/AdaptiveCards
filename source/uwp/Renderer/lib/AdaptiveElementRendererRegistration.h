#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Util.h"

AdaptiveNamespaceStart
    class AdaptiveElementRendererRegistration :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::Implements<ABI::AdaptiveNamespaceRef::IAdaptiveElementRendererRegistration>,
        Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveElementRendererRegistration)

        typedef std::unordered_map<
            std::string,
            Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveElementRenderer>,
            CaseInsensitiveHash,
            CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveElementRendererRegistration();
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveNamespaceRef::IAdaptiveElementRenderer* renderer);
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveElementRenderer** result);
        IFACEMETHODIMP Remove(_In_ HSTRING type);

    private:
        std::shared_ptr<RegistrationMap> m_registration;
    };

    ActivatableClass(AdaptiveElementRendererRegistration);
AdaptiveNamespaceEnd
