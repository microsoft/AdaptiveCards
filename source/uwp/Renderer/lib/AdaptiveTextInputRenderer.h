// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TextInput.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveTextInputRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRenderer>
    {
        AdaptiveRuntime(AdaptiveTextInputRenderer);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* cardElement,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept override;

    private:
        HRESULT HandleLayoutAndValidation(ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTextInput* adaptiveTextInput,
                                          ABI::Windows::UI::Xaml::Controls::ITextBox* textBox,
                                          ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                          ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                                          ABI::Windows::UI::Xaml::IUIElement** inputLayout);
    };

    ActivatableClass(AdaptiveTextInputRenderer);
}
