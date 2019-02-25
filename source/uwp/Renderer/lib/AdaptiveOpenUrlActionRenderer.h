#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveNamespace
{
    class AdaptiveOpenUrlActionRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveActionRenderer,
                                              ABI::AdaptiveNamespace::IAdaptiveActionParser>
    {
        AdaptiveRuntime(AdaptiveOpenUrlActionRenderer);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
                              _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept override;

        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
                                _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
                                _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** element) noexcept override;
    };

    ActivatableClass(AdaptiveOpenUrlActionRenderer);
}
