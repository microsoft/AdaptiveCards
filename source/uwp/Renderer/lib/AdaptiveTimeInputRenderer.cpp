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
    HRESULT AdaptiveTimeInputRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTimeInputRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                              _In_ IAdaptiveRenderContext* renderContext,
                                              _In_ IAdaptiveRenderArgs* /*renderArgs*/,
                                              _COM_Outptr_ IUIElement** timeInputControl) noexcept try
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
        THROW_IF_FAILED(cardElement.As(&adaptiveTimeInput));

        // Set initial value
        HString hstringValue;
        THROW_IF_FAILED(adaptiveTimeInput->get_Value(hstringValue.GetAddressOf()));
        std::string value = HStringToUTF8(hstringValue.Get());
        unsigned int hours, minutes;
        if (DateTimePreparser::TryParseSimpleTime(value, hours, minutes))
        {
            TimeSpan initialTime{(INT64)(hours * 60 + minutes) * 10000000 * 60};
            THROW_IF_FAILED(timePicker->put_Time(initialTime));
        }

        // Note: Placeholder text and min/max are not supported by ITimePicker

        RETURN_IF_FAILED(timePicker.CopyTo(timeInputControl));
        XamlHelpers::AddInputValueToContext(renderContext, adaptiveCardElement, *timeInputControl);
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTimeInputRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveTimeInput, AdaptiveSharedNamespace::TimeInput, AdaptiveSharedNamespace::TimeInputParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
