// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Image.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveImageRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRenderer>
    {
        AdaptiveRuntime(AdaptiveImageRenderer);

    public:
        AdaptiveImageRenderer();
        AdaptiveImageRenderer(Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::Uwp::XamlBuilder> xamlBuilder);
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* cardElement,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept override;

    private:
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::Uwp::XamlBuilder> m_xamlBuilder;
    };

    ActivatableClass(AdaptiveImageRenderer);
}
