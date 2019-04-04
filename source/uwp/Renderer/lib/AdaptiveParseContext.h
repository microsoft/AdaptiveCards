#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("8b651035-0177-4eb4-8dbc-cdcf1c42213a") AdaptiveParseContext
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveParseContext,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveParseContext);

    public:
        AdaptiveParseContext();

        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_opt_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementRegistration,
                                       _In_opt_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionRegistration,
                                       _In_opt_ ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration* featureRegistration) noexcept;

        // IAdaptiveParseContext
        IFACEMETHODIMP get_ElementParsers(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration** elementRegistration);
        IFACEMETHODIMP get_ActionParsers(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration** actionRegistration);
        IFACEMETHODIMP get_Features(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration** featureRegistration);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration> m_elementRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration> m_actionRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration> m_featureRegistration;
    };

    ActivatableClass(AdaptiveParseContext);
}
