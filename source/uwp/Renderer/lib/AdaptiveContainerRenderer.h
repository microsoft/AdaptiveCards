#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Container.h"

AdaptiveNamespaceStart
    class AdaptiveContainerRenderer :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespace::IAdaptiveElementRenderer,
        ABI::AdaptiveNamespace::IAdaptiveElementParser>
    {
        AdaptiveRuntime(AdaptiveContainerRenderer)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* cardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) override;

        IFACEMETHODIMP FromJson(
            ABI::Windows::Data::Json::IJsonObject *,
            ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParsers,
            ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParsers,
            ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveWarning*>* adaptiveWarnings,
            ABI::AdaptiveNamespace::IAdaptiveCardElement** element) override;
    };

    ActivatableClass(AdaptiveContainerRenderer);
AdaptiveNamespaceEnd
