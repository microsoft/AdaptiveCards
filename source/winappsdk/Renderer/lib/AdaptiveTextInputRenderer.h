// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TextInput.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveTextInputRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveElementRenderer>
    {
        AdaptiveRuntime(AdaptiveTextInputRenderer);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveCardElement* cardElement,
                              _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept override;

    private:
        HRESULT HandleLayoutAndValidation(ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveTextInput* adaptiveTextInput,
                                          ABI::Windows::UI::Xaml::Controls::ITextBox* textBox,
                                          ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderContext* renderContext,
                                          ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderArgs* renderArgs,
                                          ABI::Windows::UI::Xaml::IUIElement** inputLayout);
    };

    ActivatableClass(AdaptiveTextInputRenderer);
}
