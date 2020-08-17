// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TextInput.h"

namespace AdaptiveNamespace
{
    class AdaptiveTextInputRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveElementRenderer,
                                              ABI::AdaptiveNamespace::IAdaptiveElementParser>
    {
        AdaptiveRuntime(AdaptiveTextInputRenderer);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* cardElement,
                              _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept override;

        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject*,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParsers,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParsers,
                                _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
                                _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept override;

    private:
        HRESULT HandleLayoutAndValidation(ABI::AdaptiveNamespace::IAdaptiveTextInput* adaptiveTextInput,
                                          ABI::Windows::UI::Xaml::Controls::ITextBox* textBox,
                                          ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                          ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                          ABI::Windows::UI::Xaml::IUIElement** inputLayout);
    };

    ActivatableClass(AdaptiveTextInputRenderer);
}
