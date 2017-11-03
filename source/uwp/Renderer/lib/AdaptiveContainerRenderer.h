#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "Container.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveContainerRenderer :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Uwp::IAdaptiveElementRenderer,
        ABI::AdaptiveCards::Uwp::IAdaptiveElementParser>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveContainerRenderer, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* cardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result);

        IFACEMETHODIMP FromJson(
            ABI::Windows::Data::Json::IJsonObject *,
            ABI::AdaptiveCards::Uwp::IAdaptiveElementParserRegistration* elementParsers,
            ABI::AdaptiveCards::Uwp::IAdaptiveActionParserRegistration* actionParsers,
            ABI::AdaptiveCards::Uwp::IAdaptiveCardElement** element);
    };

    ActivatableClass(AdaptiveContainerRenderer);
}}
