// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTimeInputRenderer.h"
#include "AdaptiveTimeInputRenderer.g.cpp"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    rtxaml::UIElement AdaptiveTimeInputRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                        rtrender::AdaptiveRenderContext const& renderContext,
                                                        rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            /*  ComPtr<IAdaptiveHostConfig> hostConfig;
              RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));*/
            auto hostConfig = renderContext.HostConfig();
            if (!::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                         L"Time Input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            /*ComPtr<ITimePicker> timePicker =
                XamlHelpers::CreateABIClass<ITimePicker>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TimePicker));*/
            rtxaml::Controls::TimePicker timePicker{};

            // Make the picker stretch full width
            /*  ComPtr<IFrameworkElement> timePickerAsFrameworkElement;
              RETURN_IF_FAILED(timePicker.As(&timePickerAsFrameworkElement));
              RETURN_IF_FAILED(timePickerAsFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Stretch));
              RETURN_IF_FAILED(timePickerAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));*/
            timePicker.HorizontalAlignment(rtxaml::HorizontalAlignment::Stretch);
            timePicker.VerticalAlignment(rtxaml::VerticalAlignment::Top);

            /*RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                         L"Adaptive.Input.Time",
                                                                         timePickerAsFrameworkElement.Get()));*/
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Time", timePicker);

            /* ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
             ComPtr<IAdaptiveTimeInput> adaptiveTimeInput;
             RETURN_IF_FAILED(cardElement.As(&adaptiveTimeInput));*/
            auto adaptiveTimeInput = cardElement.as<rtom::AdaptiveTimeInput>();

            // Set initial value
            /* HString hstringValue;
             RETURN_IF_FAILED(adaptiveTimeInput->get_Value(hstringValue.GetAddressOf()));*/
            winrt::hstring hstringValue = adaptiveTimeInput.Value();
            std::string value = HStringToUTF8(hstringValue);
            unsigned int hours, minutes;
            if (::AdaptiveCards::DateTimePreparser::TryParseSimpleTime(value, hours, minutes))
            {
                winrt::Windows::Foundation::TimeSpan initialTime{(int64_t)(hours * 60 + minutes) * 10000000 * 60};
                // RETURN_IF_FAILED(timePicker->put_Time(initialTime));
                timePicker.Time(initialTime);
            }

            // Note: Placeholder is not supported by ITimePicker

            /* ComPtr<IAdaptiveInputElement> adaptiveTimeInputAsAdaptiveInput;
             RETURN_IF_FAILED(adaptiveTimeInput.As(&adaptiveTimeInputAsAdaptiveInput));*/

            // If there's any validation on this input, put the input inside a border
            /*HString max, min;
            RETURN_IF_FAILED(adaptiveTimeInput->get_Max(max.GetAddressOf()));
            RETURN_IF_FAILED(adaptiveTimeInput->get_Min(min.GetAddressOf()));*/
            winrt::hstring min = adaptiveTimeInput.Min();
            winrt::hstring max = adaptiveTimeInput.Max();

            /*ComPtr<IUIElement> timePickerAsUIElement;
            RETURN_IF_FAILED(timePicker.As(&timePickerAsUIElement));*/

            /* ComPtr<IUIElement> inputLayout;
             ComPtr<IBorder> validationBorder;
             RETURN_IF_FAILED(XamlHelpers::HandleInputLayoutAndValidation(adaptiveTimeInputAsAdaptiveInput.Get(),
                                                                          timePickerAsUIElement.Get(),
                                                                          max.IsValid() || min.IsValid(),
                                                                          renderContext,
                                                                          &inputLayout,
                                                                          &validationBorder));*/

            rtxaml::UIElement inputLayout{nullptr};
            rtxaml::Controls::Border validationBorder{nullptr};
            std::tie(inputLayout, validationBorder) = ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(
                adaptiveTimeInput, timePicker, !max.empty() || !min.empty(), renderContext); // TODO: not sure about max/min(.)empty.
                                                                                             // How to properly mimick HString.IsValid() ?

            // Create the InputValue and add it to the context
            /* ComPtr<TimeInputValue> input;
             RETURN_IF_FAILED(
                 MakeAndInitialize<TimeInputValue>(&input, adaptiveTimeInput.Get(), timePicker.Get(),
             validationBorder.Get())); RETURN_IF_FAILED(renderContext->AddInputValue(input.Get(), renderArgs));

             RETURN_IF_FAILED(inputLayout.CopyTo(timeInputControl));*/
            rtrender::TimeInputValue input{adaptiveTimeInput, timePicker, validationBorder};
            renderContext.AddInputValue(input, renderArgs);

            return inputLayout;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
