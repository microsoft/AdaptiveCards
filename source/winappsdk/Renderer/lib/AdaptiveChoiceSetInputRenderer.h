// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ChoiceSetInput.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveChoiceSetInputRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveElementRenderer>
    {
        AdaptiveRuntime(AdaptiveChoiceSetInputRenderer);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveCardElement* cardElement,
                              _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept override;

    private:
        static std::vector<std::string> GetChoiceSetValueVector(_In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput);
        static bool IsChoiceSelected(std::vector<std::string> selectedValues,
                                     _In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveChoiceInput* choice);

        HRESULT BuildExpandedChoiceSetInput(_In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderContext* renderContext,
                                            _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderArgs* renderArgs,
                                            _In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                            boolean isMultiSelect,
                                            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceInputSet);

        HRESULT BuildCompactChoiceSetInput(_In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderContext* renderContext,
                                           _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderArgs* renderArgs,
                                           _In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                           _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceInputSet);

        HRESULT BuildFilteredChoiceSetInput(_In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderContext* renderContext,
                                            _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveRenderArgs* renderArgs,
                                            _In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceInputSet);
    };

    ActivatableClass(AdaptiveChoiceSetInputRenderer);
}
