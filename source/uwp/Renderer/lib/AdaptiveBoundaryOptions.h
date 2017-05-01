#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveBoundaryOptions :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveBoundaryOptions>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveBoundaryOptions, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(BoundaryOptions boundaryOptions) noexcept;

        IFACEMETHODIMP get_Left(_Out_ INT32 *value);
        IFACEMETHODIMP put_Left(_In_ INT32 value);

        IFACEMETHODIMP get_Right(_Out_ INT32 *value);
        IFACEMETHODIMP put_Right(_In_ INT32 value);

        IFACEMETHODIMP get_Bottom(_Out_ INT32 *value);
        IFACEMETHODIMP put_Bottom(_In_ INT32 value);

        IFACEMETHODIMP get_Top(_Out_ INT32 *value);
        IFACEMETHODIMP put_Top(_In_ INT32 value);

    private:
        BoundaryOptions m_sharedBoundaryOptions;
    };

    ActivatableClass(AdaptiveBoundaryOptions);
}}