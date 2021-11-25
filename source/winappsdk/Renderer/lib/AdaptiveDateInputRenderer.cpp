// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveDateInputRenderer.h"
#include "AdaptiveDateInputRenderer.g.cpp"
#include "XamlHelpers.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    rtxaml::UIElement AdaptiveDateInputRenderer::Render(rtom::IAdaptiveCardElement const& adaptiveCardElement,
                                                        rtrender::AdaptiveRenderContext const& renderContext,
                                                        rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            if (!::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                         L"Date input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            auto adaptiveDateInput = adaptiveCardElement.as<rtom::AdaptiveDateInput>();

            rtxaml::Controls::CalendarDatePicker datePicker{};
            datePicker.PlaceholderText(adaptiveDateInput.Placeholder());

            // Make the picker stretch full width
            datePicker.HorizontalAlignment(rtxaml::HorizontalAlignment::Stretch);
            datePicker.VerticalAlignment(rtxaml::VerticalAlignment::Top);

            // Value
            std::string value = HStringToUTF8(adaptiveDateInput.Value());
            unsigned int year, month, day;
            if (::AdaptiveCards::DateTimePreparser::TryParseSimpleDate(value, year, month, day))
            {
                auto dateTimeReference = GetDateTimeReference(year, month, day);
                datePicker.Date(dateTimeReference);
            }

            // Min date
            std::string min = HStringToUTF8(adaptiveDateInput.Min());
            winrt::Windows::Foundation::DateTime minDate{};
            boolean isMinValid = ::AdaptiveCards::DateTimePreparser::TryParseSimpleDate(min, year, month, day);
            if (isMinValid)
            {
                minDate = GetDateTime(year, month, day);
                datePicker.MinDate(minDate);
            }

            // Max date
            std::string max = HStringToUTF8(adaptiveDateInput.Max());
            if (::AdaptiveCards::DateTimePreparser::TryParseSimpleDate(max, year, month, day))
            {
                auto maxDate = GetDateTime(year, month, day);
                if (isMinValid)
                {
                    if (maxDate.time_since_epoch().count() > minDate.time_since_epoch().count())
                    {
                        datePicker.MaxDate(maxDate);
                    }
                    else
                    {
                        renderContext.AddWarning(rtom::WarningStatusCode::InvalidValue, L"Min value must be less than max in Input.Date");
                    }
                }
                else
                {
                    datePicker.MaxDate(maxDate);
                }
            }

            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Date", datePicker);

            rtxaml::UIElement inputLayout{nullptr};
            rtxaml::Controls::Border validationBorder{nullptr};

            std::tie(inputLayout, validationBorder) =
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(adaptiveDateInput, datePicker, false, renderContext);

            // TODO: come back to inputs here.
            auto input = winrt::make_self<rtrender::DateInputValue>(adaptiveDateInput, datePicker, validationBorder);
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
