// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TextInput.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveTextInputRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRenderer,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParser>
    {
        AdaptiveRuntime(AdaptiveTextInputRenderer);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement* cardElement,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept override;

        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject*,
                                _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration* elementParsers,
                                _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration* actionParsers,
                                _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>* adaptiveWarnings,
                                _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** element) noexcept override;

    private:
        HRESULT HandleLayoutAndValidation(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextInput* adaptiveTextInput,
                                          ABI::Windows::UI::Xaml::Controls::ITextBox* textBox,
                                          ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                          ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                                          ABI::Windows::UI::Xaml::IUIElement** inputLayout);
    };

    ActivatableClass(AdaptiveTextInputRenderer);
}
