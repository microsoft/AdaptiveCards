#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveImageSizeOptions :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSizeOptions>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveImageSizeOptions, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ImageSizeOptions imageSizeOptions) noexcept;

        IFACEMETHODIMP get_Small(_Out_ INT32 *value);
        IFACEMETHODIMP put_Small(_In_ INT32 value);

        IFACEMETHODIMP get_Medium(_Out_ INT32 *value);
        IFACEMETHODIMP put_Medium(_In_ INT32 value);

        IFACEMETHODIMP get_Large(_Out_ INT32 *value);
        IFACEMETHODIMP put_Large(_In_ INT32 value);

    private:
        ImageSizeOptions m_sharedImageSizeOptions;
    };

    ActivatableClass(AdaptiveImageSizeOptions);
}}