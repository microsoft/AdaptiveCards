#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "ActionSet.h"

namespace AdaptiveCards
{
    namespace Rendering
    {
        namespace Uwp
        {
            class AdaptiveActionSetRenderer
                : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                                      ABI::AdaptiveNamespace::IAdaptiveElementRenderer,
                                                      ABI::AdaptiveNamespace::IAdaptiveElementParser>
            {
                InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveActionSetRenderer, BaseTrust)

                    public : HRESULT RuntimeClassInitialize() noexcept;

                IFACEMETHODIMP Render(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* cardElement,
                                      _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                      _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                      _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept;

                IFACEMETHODIMP FromJson(ABI::Windows::Data::Json::IJsonObject*,
                                        ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParsers,
                                        ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParsers,
                                        ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
                                        ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept;
            };

            ActivatableClass(AdaptiveActionSetRenderer);
        }
    }
}
