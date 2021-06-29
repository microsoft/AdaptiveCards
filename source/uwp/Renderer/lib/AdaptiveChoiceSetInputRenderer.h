// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ChoiceSetInput.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveChoiceSetInputRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRenderer,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParser>
    {
        AdaptiveRuntime(AdaptiveChoiceSetInputRenderer);

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
        static std::vector<std::string> GetChoiceSetValueVector(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput);
        static bool IsChoiceSelected(std::vector<std::string> selectedValues,
                                     _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveChoiceInput* choice);

        HRESULT BuildExpandedChoiceSetInput(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                            _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                                            _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                            boolean isMultiSelect,
                                            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceInputSet);

        HRESULT BuildCompactChoiceSetInput(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                           _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                                           _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                           _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceInputSet);

        HRESULT BuildFilteredChoiceSetInput(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                            _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                                            _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceInputSet);
    };

    ActivatableClass(AdaptiveChoiceSetInputRenderer);
}
