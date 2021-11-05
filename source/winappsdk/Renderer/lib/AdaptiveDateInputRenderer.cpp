// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveDateInputRenderer.h"
#include "XamlHelpers.h"

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
    rtxaml::UIElement AdaptiveDateInputRenderer::Render(rtom::IAdaptiveCardElement const& adaptiveCardElement,
                                                        rtrender::AdaptiveRenderContext const& renderContext,
                                                        rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
           /* ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));*/

            auto hostConfig = renderContext.HostConfig();
            if (!::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                /*renderContext->AddWarning(
                    ABI::AdaptiveCards::ObjectModel::WinUI3::WarningStatusCode::InteractivityNotSupported,
                    HStringReference(L"Date input was stripped from card because interactivity is not supported").Get());*/
                renderContext.AddWarning(
                    rtom::WarningStatusCode::InteractivityNotSupported,
                    L"Date input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            /*ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
            ComPtr<IAdaptiveDateInput> adaptiveDateInput;
            RETURN_IF_FAILED(cardElement.As(&adaptiveDateInput));*/
            // TODO: is it better to wrap this cast in if (const auto ..) ..?
            auto adaptiveDateInput = adaptiveCardElement.as<rtom::AdaptiveDateInput>();


            /*ComPtr<ICalendarDatePicker> datePicker = XamlHelpers::CreateABIClass<ICalendarDatePicker>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CalendarDatePicker));*/

            /*HString placeHolderText;
            RETURN_IF_FAILED(adaptiveDateInput->get_Placeholder(placeHolderText.GetAddressOf()));
            RETURN_IF_FAILED(datePicker->put_PlaceholderText(placeHolderText.Get()));*/

            rtxaml::Controls::CalendarDatePicker datePicker{};
            datePicker.PlaceholderText(adaptiveDateInput.Placeholder());

            // Make the picker stretch full width
           /* ComPtr<IFrameworkElement> datePickerAsFrameworkElement;
            RETURN_IF_FAILED(datePicker.As(&datePickerAsFrameworkElement));
            RETURN_IF_FAILED(datePickerAsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));
            RETURN_IF_FAILED(datePickerAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));*/
            datePicker.HorizontalAlignment(rtxaml::HorizontalAlignment::Stretch);
            datePicker.VerticalAlignment(rtxaml::VerticalAlignment::Top);

            /*RETURN_IF_FAILED(datePicker.CopyTo(dateInputControl));*/

            // Value
          /*  HString hstringValue;
            RETURN_IF_FAILED(adaptiveDateInput->get_Value(hstringValue.GetAddressOf()));*/
            std::string value = HStringToUTF8(adaptiveDateInput.Value());
            unsigned int year, month, day;
            if (::AdaptiveCards::DateTimePreparser::TryParseSimpleDate(value, year, month, day))
            {
                auto dateTimeReference = GetDateTimeReference(year, month, day);
                datePicker.Date(dateTimeReference);
                /*ComPtr<IReference<DateTime>> initialDateTimeReference;
                RETURN_IF_FAILED(GetDateTimeReference(year, month, day, &initialDateTimeReference));
                RETURN_IF_FAILED(datePicker->put_Date(initialDateTimeReference.Get()));*/
              /*  auto initialDateTimeReference = GetDateTimeReference(year, month, day);
                datePicker.ti*/
                //datePicker.Date(initialDateTimeReference);
            }

            // Min date
            HString hstringMin;
            RETURN_IF_FAILED(adaptiveDateInput->get_Min(hstringMin.GetAddressOf()));
            std::string min = HStringToUTF8(hstringMin.Get());
            DateTime minDate{};
            boolean isMinValid{DateTimePreparser::TryParseSimpleDate(min, year, month, day)};
            if (isMinValid)
            {
                minDate = GetDateTime(year, month, day);
                RETURN_IF_FAILED(datePicker->put_MinDate(minDate));
            }

            // Max date
            HString hstringMax;
            RETURN_IF_FAILED(adaptiveDateInput->get_Max(hstringMax.GetAddressOf()));
            std::string max = HStringToUTF8(hstringMax.Get());
            if (DateTimePreparser::TryParseSimpleDate(max, year, month, day))
            {
                DateTime maxDate = GetDateTime(year, month, day);
                if (isMinValid)
                {
                    if (maxDate.UniversalTime > minDate.UniversalTime)
                    {
                        RETURN_IF_FAILED(datePicker->put_MaxDate(maxDate));
                    }
                    else
                    {
                        renderContext->AddWarning(ABI::AdaptiveCards::ObjectModel::WinUI3::WarningStatusCode::InvalidValue,
                                                  HStringReference(L"Min value must be less than max in Input.Date").Get());
                    }
                }
                else
                {
                    RETURN_IF_FAILED(datePicker->put_MaxDate(maxDate));
                }
            }

            ComPtr<IAdaptiveInputElement> adapitveDateInputAsAdaptiveInput;
            RETURN_IF_FAILED(adaptiveDateInput.As(&adapitveDateInputAsAdaptiveInput));

            RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                         L"Adaptive.Input.Date",
                                                                         datePickerAsFrameworkElement.Get()));

            ComPtr<IUIElement> datePickerAsUIElement;
            RETURN_IF_FAILED(datePicker.As(&datePickerAsUIElement));

            ComPtr<IUIElement> inputLayout;
            ComPtr<IBorder> validationBorder;
            RETURN_IF_FAILED(XamlHelpers::HandleInputLayoutAndValidation(
                adapitveDateInputAsAdaptiveInput.Get(), datePickerAsUIElement.Get(), false, renderContext, &inputLayout, &validationBorder));

            // Create the InputValue and add it to the context
            ComPtr<DateInputValue> input;
            RETURN_IF_FAILED(
                MakeAndInitialize<DateInputValue>(&input, adaptiveDateInput.Get(), datePicker.Get(), validationBorder.Get()));
            RETURN_IF_FAILED(renderContext->AddInputValue(input.Get(), renderArgs));

            RETURN_IF_FAILED(inputLayout.CopyTo(dateInputControl));

            return nullptr;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
