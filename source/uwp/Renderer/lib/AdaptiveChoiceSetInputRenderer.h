#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "ChoiceSetInput.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class AdaptiveChoiceSetInputRenderer :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRenderer,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParser>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveChoiceSetInputRenderer, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(
            _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement* cardElement,
            _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result);

        IFACEMETHODIMP FromJson(
            ABI::Windows::Data::Json::IJsonObject *,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration* elementParsers,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration* actionParsers,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** element);
    };

    ActivatableClass(AdaptiveChoiceSetInputRenderer);
}}}
