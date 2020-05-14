// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveDateInput.h"
#include "AdaptiveDateInputRenderer.h"
#include "AdaptiveElementParserRegistration.h"
#include "XamlHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveDateInputRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveDateInputRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                              _In_ IAdaptiveRenderContext* renderContext,
                                              _In_ IAdaptiveRenderArgs* renderArgs,
                                              _COM_Outptr_ IUIElement** dateInputControl) noexcept
    try
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!XamlHelpers::SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Date input was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveDateInput> adaptiveDateInput;
        RETURN_IF_FAILED(cardElement.As(&adaptiveDateInput));

        ComPtr<ICalendarDatePicker> datePicker = XamlHelpers::CreateXamlClass<ICalendarDatePicker>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CalendarDatePicker));

        HString placeHolderText;
        RETURN_IF_FAILED(adaptiveDateInput->get_Placeholder(placeHolderText.GetAddressOf()));
        RETURN_IF_FAILED(datePicker->put_PlaceholderText(placeHolderText.Get()));

        // Make the picker stretch full width
        ComPtr<IFrameworkElement> datePickerAsFrameworkElement;
        RETURN_IF_FAILED(datePicker.As(&datePickerAsFrameworkElement));
        RETURN_IF_FAILED(datePickerAsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));
        RETURN_IF_FAILED(datePickerAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));

        RETURN_IF_FAILED(datePicker.CopyTo(dateInputControl));

        // Value
        HString hstringValue;
        RETURN_IF_FAILED(adaptiveDateInput->get_Value(hstringValue.GetAddressOf()));
        std::string value = HStringToUTF8(hstringValue.Get());
        unsigned int year, month, day;
        if (DateTimePreparser::TryParseSimpleDate(value, year, month, day))
        {
            ComPtr<IReference<DateTime>> initialDateTimeReference;
            RETURN_IF_FAILED(GetDateTimeReference(year, month, day, &initialDateTimeReference));
            RETURN_IF_FAILED(datePicker->put_Date(initialDateTimeReference.Get()));
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
        boolean isMaxValid{DateTimePreparser::TryParseSimpleDate(max, year, month, day)};
        if (isMaxValid)
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
                    renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::InvalidValue,
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
        datePicker.As(&datePickerAsUIElement);

        ComPtr<IUIElement> inputLayout;
        ComPtr<IBorder> validationBorder;
        ComPtr<IUIElement> validationError;
        XamlHelpers::HandleInputLayoutAndValidation(adapitveDateInputAsAdaptiveInput.Get(),
                                                    datePickerAsUIElement.Get(),
                                                    isMinValid || isMaxValid , // due to min, max values
                                                    renderContext,
                                                    renderArgs,
                                                    &inputLayout,
                                                    &validationBorder,
                                                    &validationError);

        // Create the InputValue and add it to the context
        ComPtr<DateInputValue> input;
        MakeAndInitialize<DateInputValue>(
            &input, renderContext, adaptiveDateInput.Get(), datePicker.Get(), validationBorder.Get(), validationError.Get());
        renderContext->AddInputValue(input.Get());

        inputLayout.CopyTo(dateInputControl);

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveDateInputRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept
    try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveDateInput, AdaptiveSharedNamespace::DateInput, AdaptiveSharedNamespace::DateInputParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
