// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveTimeInput.h"
#include "AdaptiveTimeInputRenderer.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveTimeInputRenderer::RuntimeClassInitialize() noexcept { return S_OK; }

    HRESULT AdaptiveTimeInputRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                              _In_ IAdaptiveRenderContext* renderContext,
                                              _In_ IAdaptiveRenderArgs* renderArgs,
                                              _COM_Outptr_ IUIElement** timeInputControl) noexcept
    try
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!XamlHelpers::SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Time Input was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<ITimePicker> timePicker =
            XamlHelpers::CreateXamlClass<ITimePicker>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TimePicker));

        // Make the picker stretch full width
        ComPtr<IFrameworkElement> timePickerAsFrameworkElement;
        RETURN_IF_FAILED(timePicker.As(&timePickerAsFrameworkElement));
        RETURN_IF_FAILED(timePickerAsFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Stretch));
        RETURN_IF_FAILED(timePickerAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));

        RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                     L"Adaptive.Input.Time",
                                                                     timePickerAsFrameworkElement.Get()));

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTimeInput> adaptiveTimeInput;
        RETURN_IF_FAILED(cardElement.As(&adaptiveTimeInput));

        // Set initial value
        HString hstringValue;
        RETURN_IF_FAILED(adaptiveTimeInput->get_Value(hstringValue.GetAddressOf()));
        std::string value = HStringToUTF8(hstringValue.Get());
        unsigned int hours, minutes;
        if (DateTimePreparser::TryParseSimpleTime(value, hours, minutes))
        {
            TimeSpan initialTime{(INT64)(hours * 60 + minutes) * 10000000 * 60};
            RETURN_IF_FAILED(timePicker->put_Time(initialTime));
        }

        // Note: Placeholder is not supported by ITimePicker

        ComPtr<IAdaptiveInputElement> adaptiveTimeInputAsAdaptiveInput;
        RETURN_IF_FAILED(adaptiveTimeInput.As(&adaptiveTimeInputAsAdaptiveInput));

        // If there's any validation on this input, put the input inside a border
        HString max, min;
        RETURN_IF_FAILED(adaptiveTimeInput->get_Max(max.GetAddressOf()));
        RETURN_IF_FAILED(adaptiveTimeInput->get_Min(min.GetAddressOf()));

        ComPtr<IUIElement> timePickerAsUIElement;
        RETURN_IF_FAILED(timePicker.As(&timePickerAsUIElement));

        ComPtr<IUIElement> inputLayout;
        ComPtr<IBorder> validationBorder;
        RETURN_IF_FAILED(XamlHelpers::HandleInputLayoutAndValidation(adaptiveTimeInputAsAdaptiveInput.Get(),
                                                                     timePickerAsUIElement.Get(),
                                                                     max.IsValid() || min.IsValid(),
                                                                     renderContext,
                                                                     &inputLayout,
                                                                     &validationBorder));

        // Create the InputValue and add it to the context
        ComPtr<TimeInputValue> input;
        RETURN_IF_FAILED(
            MakeAndInitialize<TimeInputValue>(&input, adaptiveTimeInput.Get(), timePicker.Get(), validationBorder.Get());
            RETURN_IF_FAILED(renderContext->AddInputValue(input.Get(), renderArgs)));

        RETURN_IF_FAILED(inputLayout.CopyTo(timeInputControl));

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTimeInputRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept
    try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveTimeInput, AdaptiveSharedNamespace::TimeInput, AdaptiveSharedNamespace::TimeInputParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
