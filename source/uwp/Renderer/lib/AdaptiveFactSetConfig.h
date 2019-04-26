// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveNamespace
{
    class AdaptiveFactSetConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveFactSetConfig>
    {
        AdaptiveRuntime(AdaptiveFactSetConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(FactSetConfig factSetConfig) noexcept;

        IFACEMETHODIMP get_Title(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveTextConfig** titleTextConfig);
        IFACEMETHODIMP put_Title(_In_ ABI::AdaptiveNamespace::IAdaptiveTextConfig* titleTextConfig);

        IFACEMETHODIMP get_Value(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveTextConfig** valueTextConfig);
        IFACEMETHODIMP put_Value(_In_ ABI::AdaptiveNamespace::IAdaptiveTextConfig* valueTextConfig);

        IFACEMETHODIMP get_Spacing(_Out_ UINT32* value);
        IFACEMETHODIMP put_Spacing(UINT32 value);

    private:
        UINT m_spacing;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveTextConfig> m_title;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveTextConfig> m_value;
    };

    ActivatableClass(AdaptiveFactSetConfig);
}
