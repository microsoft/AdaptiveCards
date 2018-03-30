#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Column.h"

AdaptiveNamespaceStart
    class AdaptiveColumnRenderer :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespaceRef::IAdaptiveElementRenderer>
    {
        AdaptiveRuntime(AdaptiveColumnRenderer)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(
            _In_ ABI::AdaptiveNamespaceRef::IAdaptiveCardElement* cardElement,
            _In_ ABI::AdaptiveNamespaceRef::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespaceRef::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result);
    };

    ActivatableClass(AdaptiveColumnRenderer);
AdaptiveNamespaceEnd
