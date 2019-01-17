#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Column.h"
#include "XamlBuilder.h"

namespace AdaptiveNamespace
{
    class AdaptiveColumnRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveElementRenderer>
    {
        AdaptiveRuntime(AdaptiveColumnRenderer);

    public:
        AdaptiveColumnRenderer();
        AdaptiveColumnRenderer(std::shared_ptr<AdaptiveNamespace::XamlBuilder> xamlBuilder);
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* cardElement,
                              _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result);

    private:
        std::shared_ptr<AdaptiveNamespace::XamlBuilder> m_xamlBuilder;
    };

    ActivatableClass(AdaptiveColumnRenderer);
}
