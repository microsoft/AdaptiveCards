#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "Height.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveHeight :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHeight>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveHeight, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(Height height) noexcept;

        IFACEMETHODIMP get_HeightType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::HeightType* heightType);
        IFACEMETHODIMP put_HeightType(_In_ ABI::AdaptiveCards::XamlCardRenderer::HeightType heightType);

    private:
        Height m_sharedHeight;
    };

    ActivatableClass(AdaptiveHeight);
}}