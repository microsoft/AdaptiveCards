#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveCardConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespace::IAdaptiveCardConfig>
    {
        AdaptiveRuntime(AdaptiveCardConfig)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveSharedNamespace::AdaptiveCardConfig adaptiveCardConfig) noexcept;

        IFACEMETHODIMP get_AllowCustomStyle(_Out_ boolean* allowCustomStyle);
        IFACEMETHODIMP put_AllowCustomStyle(_In_ boolean allowCustomStyle);

    private:
        boolean m_allowCustomStyle;
    };

    ActivatableClass(AdaptiveCardConfig);
AdaptiveNamespaceEnd