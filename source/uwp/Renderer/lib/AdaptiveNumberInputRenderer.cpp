// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveNumberInputRenderer.h"
#include "AdaptiveNumberInputRenderer.g.cpp"
#include <limits>

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    rtxaml::UIElement AdaptiveNumberInputRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                          rtrender::AdaptiveRenderContext const& renderContext,
                                                          rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            if (!::AdaptiveCards::Rendering::Uwp::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                         L"Number input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            auto adaptiveNumberInput = cardElement.as<rtom::AdaptiveNumberInput>();

            rtxaml::Controls::TextBox textBox{};
            rtxaml::Input::InputScopeName inputScopeName{rtxaml::Input::InputScopeNameValue::Number};

            rtxaml::Input::InputScope inputScope{};
            // TODO: we can do this, right?
            inputScope.Names().Append(rtxaml::Input::InputScopeName{rtxaml::Input::InputScopeNameValue::Number});

            textBox.InputScope(inputScope);

            auto value = adaptiveNumberInput.Value();

            if (value != nullptr)
            {
                // TODO: why do we need to check if retrieval of value was successful? ref is not nullptr
                // TODO: what if it's 0? then if (const auto boxValue = value.Value()) won't work
                // if (SUCCEEDED(value->get_Value(&boxValue)))
                double boxValue = value.Value();
                std::wstringstream ss;
                // TODO: why not just use std::to_string(boxValue)? so we can specify precision correctly?
                ss.precision(std::numeric_limits<double>::digits10);
                ss << boxValue;
                std::wstring stringValue = ss.str();

                // TODO: hstring constructor from wstring will be invoked.
                // TODO: {} is not neccessary, right?
                textBox.Text(stringValue);
            }

            textBox.PlaceholderText(adaptiveNumberInput.Placeholder());
            textBox.VerticalAlignment(rtxaml::VerticalAlignment::Top);

            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Number", textBox);

            // If there's any validation on this input, put the input inside a border
            auto max = adaptiveNumberInput.Max();
            auto min = adaptiveNumberInput.Min();

            rtxaml::UIElement inputLayout{nullptr};
            rtxaml::Controls::Border validationBorder{nullptr};
            std::tie(inputLayout, validationBorder) =
                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleInputLayoutAndValidation(adaptiveNumberInput, // TODO: no need to cast here either, right?
                                                                                                textBox,
                                                                                                (max || min), // TODO: no need to compare with nullptr, right?
                                                                                                renderContext);
            // Create the InputValue and add it to the context
            // TODO: is this the right way to do it?
            // TODO: do we need private IDL for these scenarios?
            auto input = winrt::make_self<rtrender::NumberInputValue>(adaptiveNumberInput, textBox, validationBorder);

            renderContext.AddInputValue(*input, renderArgs);

            return inputLayout;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
