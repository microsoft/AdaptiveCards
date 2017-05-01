#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveFontSizeOptions :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFontSizeOptions>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveFontSizeOptions, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(FontSizeOptions fontSizeOptions) noexcept;

        IFACEMETHODIMP get_Small(_Out_ INT32 *value);
        IFACEMETHODIMP put_Small(_In_ INT32 value);

        IFACEMETHODIMP get_Normal(_Out_ INT32 *value);
        IFACEMETHODIMP put_Normal(_In_ INT32 value);

        IFACEMETHODIMP get_Medium(_Out_ INT32 *value);
        IFACEMETHODIMP put_Medium(_In_ INT32 value);

        IFACEMETHODIMP get_Large(_Out_ INT32 *value);
        IFACEMETHODIMP put_Large(_In_ INT32 value);

        IFACEMETHODIMP get_ExtraLarge(_Out_ INT32 *value);
        IFACEMETHODIMP put_ExtraLarge(_In_ INT32 value);

    private:
        FontSizeOptions m_sharedFontSizeOptions;
    };

    ActivatableClass(AdaptiveFontSizeOptions);
}}