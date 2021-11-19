// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveNumberInputRenderer.h"
#include "AdaptiveNumberInputRenderer.g.cpp"
#include <limits>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Input;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    rtxaml::UIElement AdaptiveNumberInputRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
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
                                         L"Number input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            /*ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
            ComPtr<IAdaptiveNumberInput> adaptiveNumberInput;
            RETURN_IF_FAILED(cardElement.As(&adaptiveNumberInput));*/

            auto adaptiveNumberInput = cardElement.as<rtom::AdaptiveNumberInput>();

            /*  ComPtr<ITextBox> textBox =
                  XamlHelpers::CreateABIClass<ITextBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBox));

              ComPtr<IInputScopeName> inputScopeName =
                  XamlHelpers::CreateABIClass<IInputScopeName>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScopeName));
              RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_Number));*/

            rtxaml::Controls::TextBox textBox{};

            rtxaml::Input::InputScopeName inputScopeName{rtxaml::Input::InputScopeNameValue::Number};

            /*ComPtr<IInputScope> inputScope =
                XamlHelpers::CreateABIClass<IInputScope>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScope));
            ComPtr<IVector<InputScopeName*>> names;
            RETURN_IF_FAILED(inputScope->get_Names(names.GetAddressOf()));
            RETURN_IF_FAILED(names->Append(inputScopeName.Get()));

            RETURN_IF_FAILED(textBox->put_InputScope(inputScope.Get()));

            ComPtr<ABI::Windows::Foundation::IReference<double>> value;
            RETURN_IF_FAILED(adaptiveNumberInput->get_Value(&value));*/

            rtxaml::Input::InputScope inputScope{};

            auto names = inputScope.Names();
            names.Append(inputScopeName);
            textBox.InputScope(inputScope);

            auto value = adaptiveNumberInput.Value();

            if (value != nullptr)
            {
                // TODO: why do we need to check if retrieval of value was successful? ref is not nullptr
                // TODO: what if it's 0? then if (const auto boxValue = value.Value()) won't work
                /*if (const auto boxValue = value.Value())
                {*/
                double boxValue = value.Value();
                std::wstringstream ss;
                ss.precision(std::numeric_limits<double>::digits10);
                ss << boxValue;
                std::wstring stringValue = ss.str();

                // TODO: hstring constructor from wstring will be invoked.
                // TODO: {} is not neccessary, right?
                textBox.Text({stringValue});
                //}
            }

            /* ComPtr<ITextBox2> textBox2;
             RETURN_IF_FAILED(textBox.As(&textBox2));

             HString placeHolderText;
             RETURN_IF_FAILED(adaptiveNumberInput->get_Placeholder(placeHolderText.GetAddressOf()));
             RETURN_IF_FAILED(textBox2->put_PlaceholderText(placeHolderText.Get()));*/
            auto placeHolderText = adaptiveNumberInput.Placeholder();
            textBox.PlaceholderText(placeHolderText);

            /* ComPtr<IFrameworkElement> frameworkElement;
             RETURN_IF_FAILED(textBox.As(&frameworkElement));
             RETURN_IF_FAILED(frameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
             RETURN_IF_FAILED(
                 XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Number", frameworkElement.Get()));*/
            textBox.VerticalAlignment(rtxaml::VerticalAlignment::Top);
            // TODO: no need to convert textBox to frameworkElement here, right?
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Number", textBox);

            /*ComPtr<IAdaptiveInputElement> numberInputAsAdaptiveInput;
            RETURN_IF_FAILED(adaptiveNumberInput.As(&numberInputAsAdaptiveInput));

            ComPtr<IUIElement> textBoxAsUIElement;
            RETURN_IF_FAILED(textBox.As(&textBoxAsUIElement));*/

            // If there's any validation on this input, put the input inside a border
            /*   ComPtr<ABI::Windows::Foundation::IReference<double>> max;
               RETURN_IF_FAILED(adaptiveNumberInput->get_Max(&max));

               ComPtr<ABI::Windows::Foundation::IReference<double>> min;
               RETURN_IF_FAILED(adaptiveNumberInput->get_Min(&min));*/
            auto max = adaptiveNumberInput.Max();
            auto min = adaptiveNumberInput.Min();

            rtxaml::UIElement inputLayout{nullptr};
            rtxaml::Controls::Border validationBorder{nullptr};
            std::tie(inputLayout, validationBorder) =
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(adaptiveNumberInput, // TODO: no need to cast here either, right?
                                                                                                textBox,
                                                                                                (max || min), // TODO: no need to compare with nullptr, right?
                                                                                                renderContext);
            //// Create the InputValue and add it to the context
            // ComPtr<NumberInputValue> input;
            // RETURN_IF_FAILED(
            //    MakeAndInitialize<NumberInputValue>(&input, adaptiveNumberInput.Get(), textBox.Get(), validationBorder.Get()));
            // RETURN_IF_FAILED(renderContext->AddInputValue(input.Get(), renderArgs));

            // RETURN_IF_FAILED(inputLayout.CopyTo(numberInputControl));
            // return S_OK;

            // TODO: is this the right way to do it?
            // TODO: we can't use make self here, because we define NumberInputValue in idl, however it inherits from interface defined in idl I assume?
            // TODO: do we need private IDL for these scenarios?
            // auto input = winrt::make_self<rtrender::NumberInputValue>(adaptiveNumberInput, textBox, validationBorder);

            rtrender::NumberInputValue input{adaptiveNumberInput, textBox, validationBorder};

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
