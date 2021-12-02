// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTimeInputRenderer.h"
#include "AdaptiveTimeInputRenderer.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    rtxaml::UIElement AdaptiveTimeInputRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                        rtrender::AdaptiveRenderContext const& renderContext,
                                                        rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            if (!::AdaptiveCards::Rendering::Uwp::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                         L"Time Input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            rtxaml::Controls::TimePicker timePicker{};

            // Make the picker stretch full width
            timePicker.HorizontalAlignment(rtxaml::HorizontalAlignment::Stretch);
            timePicker.VerticalAlignment(rtxaml::VerticalAlignment::Top);

            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Time", timePicker);

            auto adaptiveTimeInput = cardElement.as<rtom::AdaptiveTimeInput>();

            // Set initial value
            std::string value = HStringToUTF8(adaptiveTimeInput.Value());
            unsigned int hours, minutes;
            if (::AdaptiveCards::DateTimePreparser::TryParseSimpleTime(value, hours, minutes))
            {
                winrt::Windows::Foundation::TimeSpan initialTime{(int64_t)(hours * 60 + minutes) * 10000000 * 60};
                timePicker.Time(initialTime);
            }
            // Note: Placeholder is not supported by ITimePicker

            // If there's any validation on this input, put the input inside a border
            winrt::hstring min = adaptiveTimeInput.Min();
            winrt::hstring max = adaptiveTimeInput.Max();

            auto& [inputLayout, validationBorder] = ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleInputLayoutAndValidation(
                adaptiveTimeInput, timePicker, !max.empty() || !min.empty(), renderContext);

            // TODO: come back to all the inputs, not sure if this is right
            auto input = winrt::make_self<rtrender::TimeInputValue>(adaptiveTimeInput, timePicker, validationBorder);
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
