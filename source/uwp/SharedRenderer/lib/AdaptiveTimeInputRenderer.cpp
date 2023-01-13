// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTimeInputRenderer.h"
#include "AdaptiveTimeInputRenderer.g.cpp"
#include "InputValue.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::UIElement AdaptiveTimeInputRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                       winrt::AdaptiveRenderContext const& renderContext,
                                                       winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            if (!XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(winrt::WarningStatusCode::InteractivityNotSupported,
                                         L"Time Input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            winrt::TimePicker timePicker{};

            // Make the picker stretch full width
            timePicker.HorizontalAlignment(winrt::HorizontalAlignment::Stretch);
            timePicker.VerticalAlignment(winrt::VerticalAlignment::Top);

            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Time", timePicker);

            auto adaptiveTimeInput = cardElement.as<winrt::AdaptiveTimeInput>();

            // Set initial value
            std::string value = HStringToUTF8(adaptiveTimeInput.Value());
            unsigned int hours, minutes;
            if (::AdaptiveCards::DateTimePreparser::TryParseSimpleTime(value, hours, minutes))
            {
                winrt::TimeSpan initialTime{(int64_t)(hours * 60 + minutes) * 10000000 * 60};
                timePicker.Time(initialTime);
            }
            // Note: Placeholder is not supported by ITimePicker

            // If there's any validation on this input, put the input inside a border
            winrt::hstring min = adaptiveTimeInput.Min();
            winrt::hstring max = adaptiveTimeInput.Max();

            auto [inputLayout, validationBorder] =
                XamlHelpers::HandleInputLayoutAndValidation(adaptiveTimeInput, timePicker, !max.empty() || !min.empty(), renderContext);

            auto input = winrt::make_self<winrt::TimeInputValue>(adaptiveTimeInput, timePicker, validationBorder);
            renderContext.AddInputValue(*input, renderArgs);

            return inputLayout;
        }
        catch (winrt::hresult_error const& ex)
        {
            XamlHelpers::ErrForRenderFailedForElement(renderContext, cardElement.ElementTypeString(), ex.message());
            return nullptr;
        }
    }
}
