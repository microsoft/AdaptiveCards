#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveHostOptions :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostOptions>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveHostOptions, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        // IAdaptiveHostOptions
        IFACEMETHODIMP get_FontFamily(_Out_ HSTRING *text);
        IFACEMETHODIMP put_FontFamily(_In_ HSTRING text);

        IFACEMETHODIMP get_FontSizes(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFontSizeOptions** fontSize);
        IFACEMETHODIMP put_FontSizes(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFontSizeOptions* fontSize);

        IFACEMETHODIMP get_SupportsInteractivity(_Out_ boolean* supportsInteractivity);
        IFACEMETHODIMP put_SupportsInteractivity(_In_ boolean supportsInteractivity);

        IFACEMETHODIMP get_Colors(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOptions **colorOptions);
        IFACEMETHODIMP put_Colors(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOptions *colorOptions);

        IFACEMETHODIMP get_ImageSizes(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSizeOptions** imageOptions);
        IFACEMETHODIMP put_ImageSizes(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSizeOptions* imageOptions);

        IFACEMETHODIMP get_MaxActions(_Out_ INT32 *maxActions);
        IFACEMETHODIMP put_MaxActions(_In_ INT32 maxActions);

        IFACEMETHODIMP get_StrongSeparation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions** strongSeparationOptions);
        IFACEMETHODIMP put_StrongSeparation(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions* strongSeparationOptions);

        IFACEMETHODIMP get_AdaptiveCard(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardOptions** adaptiveCardOptionsOptions);
        IFACEMETHODIMP put_AdaptiveCard(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardOptions* adaptiveCardOptionsOptions);

        IFACEMETHODIMP get_ImageSet(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSetOptions** imageSetOptionsOptions);
        IFACEMETHODIMP put_ImageSet(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSetOptions* imageSetOptionsOptions);

        IFACEMETHODIMP get_Image(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageOptions** imageOptionsOptions);
        IFACEMETHODIMP put_Image(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageOptions* imageOptionsOptions);

        IFACEMETHODIMP get_FactSet(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFactSetOptions** factSetOptionsOptions);
        IFACEMETHODIMP put_FactSet(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFactSetOptions* factSetOptionsOptions);

        IFACEMETHODIMP get_Column(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumnOptions** columnOptionsOptions);
        IFACEMETHODIMP put_Column(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumnOptions* columnOptionsOptions);

        IFACEMETHODIMP get_Container(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerOptions** containerOptionsOptions);
        IFACEMETHODIMP put_Container(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerOptions* containerOptionsOptions);

        IFACEMETHODIMP get_ColumnSet(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumnSetOptions** columnSetOptionsOptions);
        IFACEMETHODIMP put_ColumnSet(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumnSetOptions* columnSetOptionsOptions);

        IFACEMETHODIMP get_TextBlock(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextBlockOptions** textBlockOptionsOptions);
        IFACEMETHODIMP put_TextBlock(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextBlockOptions* textBlockOptionsOptions);

        IFACEMETHODIMP get_DateInput(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveDateInputOptions** dateInputOptionsOptions);
        IFACEMETHODIMP put_DateInput(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveDateInputOptions* dateInputOptionsOptions);

        IFACEMETHODIMP get_TimeInput(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTimeInputOptions** timeInputOptionsOptions);
        IFACEMETHODIMP put_TimeInput(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTimeInputOptions* timeInputOptionsOptions);

        IFACEMETHODIMP get_NumberInput(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveNumberInputOptions** numberInputOptionsOptions);
        IFACEMETHODIMP put_NumberInput(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveNumberInputOptions* numberInputOptionsOptions);

        IFACEMETHODIMP get_ToggleInput(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveToggleInputOptions** toggleInputOptionsOptions);
        IFACEMETHODIMP put_ToggleInput(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveToggleInputOptions* toggleInputOptionsOptions);

        IFACEMETHODIMP get_TextInput(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextInputOptions** textInputOptionsOptions);
        IFACEMETHODIMP put_TextInput(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextInputOptions* textInputOptionsOptions);

        IFACEMETHODIMP get_ChoiceSetInput(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceSetInputOptions** choiceSetInputOptionsOptions);
        IFACEMETHODIMP put_ChoiceSetInput(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceSetInputOptions* choiceSetInputOptionsOptions);

        IFACEMETHODIMP get_Actions(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionOptions** actionsOptionOptions);
        IFACEMETHODIMP put_Actions(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionOptions* actionsOptionOptions);

    private:
        HostOptions m_sharedHostOptions;
    };

    ActivatableClass(AdaptiveHostOptions);
}}