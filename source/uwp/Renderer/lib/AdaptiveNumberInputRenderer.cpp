// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveNumberInputRenderer.h"
#include "AdaptiveNumberInputRenderer.g.cpp"
#include <limits>

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    winrt::UIElement AdaptiveNumberInputRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                         winrt::AdaptiveRenderContext const& renderContext,
                                                         winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            if (!::AdaptiveCards::Rendering::Uwp::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(winrt::WarningStatusCode::InteractivityNotSupported,
                                         L"Number input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            auto adaptiveNumberInput = cardElement.as<winrt::AdaptiveNumberInput>();

            winrt::TextBox textBox{};
            winrt::InputScopeName inputScopeName{winrt::InputScopeNameValue::Number};

            winrt::InputScope inputScope{};
            inputScope.Names().Append(winrt::InputScopeName{winrt::InputScopeNameValue::Number});

            textBox.InputScope(inputScope);

            auto value = adaptiveNumberInput.Value();

            if (value)
            {
                double boxValue = value.Value();
                std::wstringstream ss;
                ss.precision(std::numeric_limits<double>::digits10);
                ss << boxValue;
                std::wstring stringValue = ss.str();
                textBox.Text(stringValue);
            }

            textBox.PlaceholderText(adaptiveNumberInput.Placeholder());
            textBox.VerticalAlignment(winrt::VerticalAlignment::Top);

            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Number", textBox);

            // If there's any validation on this input, put the input inside a border
            auto max = adaptiveNumberInput.Max();
            auto min = adaptiveNumberInput.Min();

            auto [inputLayout, validationBorder] =
                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleInputLayoutAndValidation(adaptiveNumberInput,
                                                                                             textBox,
                                                                                             (max || min),
                                                                                             renderContext);

            // Create the InputValue and add it to the context?
            auto input = winrt::make_self<winrt::NumberInputValue>(adaptiveNumberInput, textBox, validationBorder);

            renderContext.AddInputValue(*input, renderArgs);

            return inputLayout;
        }
        catch (winrt::hresult_error const& ex)
        {
            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::ErrForRenderFailedForElement(renderContext,
                                                                             cardElement.ElementTypeString(),
                                                                             ex.message());
            return nullptr;
        }
    }
}
