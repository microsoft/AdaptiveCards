#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Image.h"
#include "XamlBuilder.h"

AdaptiveNamespaceStart
    class AdaptiveImageRenderer :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespaceRef::IAdaptiveElementRenderer,
        ABI::AdaptiveNamespaceRef::IAdaptiveElementParser>
    {
        AdaptiveRuntime(AdaptiveImageRenderer)

    public:
        AdaptiveImageRenderer();
        AdaptiveImageRenderer(std::shared_ptr<AdaptiveNamespaceRef::XamlBuilder> xamlBuilder);
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(
            _In_ ABI::AdaptiveNamespaceRef::IAdaptiveCardElement* cardElement,
            _In_ ABI::AdaptiveNamespaceRef::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespaceRef::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result);

        IFACEMETHODIMP FromJson(
            ABI::Windows::Data::Json::IJsonObject *,
            ABI::AdaptiveNamespaceRef::IAdaptiveElementParserRegistration* elementParsers,
            ABI::AdaptiveNamespaceRef::IAdaptiveActionParserRegistration* actionParsers,
            ABI::AdaptiveNamespaceRef::IAdaptiveCardElement** element);

    private:
        std::shared_ptr<AdaptiveNamespaceRef::XamlBuilder> m_xamlBuilder;
    };

    ActivatableClass(AdaptiveImageRenderer);
AdaptiveNamespaceEnd
