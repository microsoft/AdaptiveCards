#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "NumberInput.h"
#include "XamlBuilder.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveNumberInputRenderer :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Uwp::IAdaptiveElementRenderer,
        ABI::AdaptiveCards::Uwp::IAdaptiveElementParser>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveNumberInputRenderer, BaseTrust)

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
            ABI::AdaptiveCards::Uwp::IAdaptiveCardElement **);

    private:
        AdaptiveCards::Uwp::XamlBuilder m_xamlBuilder;
    };

    ActivatableClass(AdaptiveNumberInputRenderer);
}}
