// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveToggleInputRenderer.h"
#include "AdaptiveToggleInputRenderer.g.cpp"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    rtxaml::UIElement AdaptiveToggleInputRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
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
                renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                         L"Toggle Input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            /* ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
             ComPtr<IAdaptiveToggleInput> adaptiveToggleInput;
             RETURN_IF_FAILED(cardElement.As(&adaptiveToggleInput));*/
            auto adaptiveToggleInput = cardElement.as<rtom::AdaptiveToggleInput>();

            /*  ComPtr<ICheckBox> checkBox =
                  XamlHelpers::CreateABIClass<ICheckBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CheckBox));*/
            rtxaml::Controls::CheckBox checkBox{};

            /*  HString title;
              RETURN_IF_FAILED(adaptiveToggleInput->get_Title(title.GetAddressOf()));

              boolean wrap;
              adaptiveToggleInput->get_Wrap(&wrap);*/

            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetContent(checkBox,
                                                                        adaptiveToggleInput.Title(),
                                                                        adaptiveToggleInput.Wrap());

            /*   HString value;
               RETURN_IF_FAILED(adaptiveToggleInput->get_Value(value.GetAddressOf()));

               HString valueOn;
               RETURN_IF_FAILED(adaptiveToggleInput->get_ValueOn(valueOn.GetAddressOf()));*/
            winrt::hstring value = adaptiveToggleInput.Value();
            winrt::hstring valueOn = adaptiveToggleInput.ValueOn();

            /*INT32 compareValueOn;
            RETURN_IF_FAILED(WindowsCompareStringOrdinal(value.Get(), valueOn.Get(), &compareValueOn));*/

            // TODO: why value is oh type hstring instead of bool? weird stuff here, honestly :D
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetToggleValue(checkBox, value == valueOn);

            /*ComPtr<IUIElement> checkboxAsUIElement;
            RETURN_IF_FAILED(checkBox.As(&checkboxAsUIElement));
            RETURN_IF_FAILED(XamlHelpers::AddHandledTappedEvent(checkboxAsUIElement.Get()));*/
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AddHandledTappedEvent(checkBox);

            /*ComPtr<IFrameworkElement> frameworkElement;
            RETURN_IF_FAILED(checkBox.As(&frameworkElement));
            RETURN_IF_FAILED(frameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
            RETURN_IF_FAILED(
                XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Toggle", frameworkElement.Get()));*/
            checkBox.VerticalAlignment(rtxaml::VerticalAlignment::Top);
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Toggle", checkBox);

            /*ComPtr<IAdaptiveInputElement> adapitveToggleInputAsAdaptiveInput;
            RETURN_IF_FAILED(adaptiveToggleInput.As(&adapitveToggleInputAsAdaptiveInput));*/

            /* ComPtr<IUIElement> inputLayout;
             ComPtr<IUIElement> validationError;
             RETURN_IF_FAILED(XamlHelpers::HandleInputLayoutAndValidation(
                 adapitveToggleInputAsAdaptiveInput.Get(), checkboxAsUIElement.Get(), false, renderContext, &inputLayout, nullptr));*/
            rtxaml::UIElement inputLayout{nullptr};
            std::tie(inputLayout, std::ignore) =
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(adaptiveToggleInput, checkBox, false, renderContext);

            /*ComPtr<ToggleInputValue> input;
            RETURN_IF_FAILED(MakeAndInitialize<ToggleInputValue>(&input, adaptiveToggleInput.Get(), checkBox.Get(),
            nullptr)); RETURN_IF_FAILED(renderContext->AddInputValue(input.Get(), renderArgs));

            RETURN_IF_FAILED(inputLayout.CopyTo(toggleInputControl));*/
            rtrender::ToggleInputValue input{adaptiveToggleInput, checkBox, nullptr};
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
