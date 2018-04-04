#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Image.h"
#include "XamlBuilder.h"

AdaptiveNamespaceStart
    class AdaptiveImageRenderer :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespace::IAdaptiveElementRenderer,
        ABI::AdaptiveNamespace::IAdaptiveElementParser>
    {
        AdaptiveRuntime(AdaptiveImageRenderer)

    public:
        AdaptiveImageRenderer();
        AdaptiveImageRenderer(std::shared_ptr<AdaptiveNamespace::XamlBuilder> xamlBuilder);
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* cardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result);

        IFACEMETHODIMP FromJson(
            ABI::Windows::Data::Json::IJsonObject *,
            ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParsers,
            ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParsers,
            ABI::AdaptiveNamespace::IAdaptiveCardElement** element);

    private:
        std::shared_ptr<AdaptiveNamespace::XamlBuilder> m_xamlBuilder;
    };

    ActivatableClass(AdaptiveImageRenderer);
AdaptiveNamespaceEnd
