#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "ColumnSet.h"
#include "XamlBuilder.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveColumnSetRenderer :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Uwp::IAdaptiveElementRenderer>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveColumnSetRenderer, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        AdaptiveColumnSetRenderer();
        AdaptiveColumnSetRenderer(const std::shared_ptr<AdaptiveCards::Uwp::XamlBuilder> xamlBuilder);

        IFACEMETHODIMP Render(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* cardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result);
    private:
        std::shared_ptr<AdaptiveCards::Uwp::XamlBuilder> m_xamlBuilder;
    };

    ActivatableClass(AdaptiveColumnSetRenderer);
}}
