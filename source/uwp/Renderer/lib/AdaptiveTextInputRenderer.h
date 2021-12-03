// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TextInput.h"

namespace AdaptiveCards::Rendering::Uwp
{
class AdaptiveTextInputRenderer
    : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRenderer>
{
    AdaptiveRuntime(AdaptiveTextInputRenderer);

public:
    HRESULT RuntimeClassInitialize() noexcept;

    IFACEMETHODIMP Render(
        _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* cardElement,
        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
        _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept override;

private:
    HRESULT AdaptiveTextInputRenderer::RenderTextBox(
        _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTextInput* adaptiveTextInput,
        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
        _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** textInputControl);

    HRESULT AdaptiveTextInputRenderer::RenderPasswordBox(
        _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTextInput* adaptiveTextInput,
        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
        _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** textInputControl);

    HRESULT HandleLayoutAndValidation(
        ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTextInput* adaptiveTextInput,
        ABI::Windows::UI::Xaml::IUIElement* textBox,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
        ABI::Windows::UI::Xaml::IUIElement** inputLayout,
        ABI::Windows::UI::Xaml::Controls::IBorder** validationBorderOut);
};

ActivatableClass(AdaptiveTextInputRenderer);
} // namespace AdaptiveCards::Rendering::Uwp
