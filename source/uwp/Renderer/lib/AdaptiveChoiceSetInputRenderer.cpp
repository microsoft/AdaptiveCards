// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveChoiceSetInput.h"
#include "AdaptiveChoiceSetInputRenderer.h"
#include "AdaptiveElementParserRegistration.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveChoiceSetInputRenderer::RuntimeClassInitialize() noexcept { return S_OK; }

    HRESULT AdaptiveChoiceSetInputRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                                   _In_ IAdaptiveRenderContext* renderContext,
                                                   _In_ IAdaptiveRenderArgs* renderArgs,
                                                   _COM_Outptr_ IUIElement** choiceInputSet) noexcept
    try
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!XamlHelpers::SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"ChoiceSet was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveChoiceSetInput> adaptiveChoiceSetInput;
        RETURN_IF_FAILED(cardElement.As(&adaptiveChoiceSetInput));

        ABI::AdaptiveNamespace::ChoiceSetStyle choiceSetStyle;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_ChoiceSetStyle(&choiceSetStyle));

        boolean isMultiSelect;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_IsMultiSelect(&isMultiSelect));

        if (choiceSetStyle == ABI::AdaptiveNamespace::ChoiceSetStyle_Compact && !isMultiSelect)
        {
            RETURN_IF_FAILED(BuildCompactChoiceSetInput(renderContext, renderArgs, adaptiveChoiceSetInput.Get(), choiceInputSet));
        }
        else
        {
            RETURN_IF_FAILED(BuildExpandedChoiceSetInput(renderContext, renderArgs, adaptiveChoiceSetInput.Get(), isMultiSelect, choiceInputSet));
        }

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveChoiceSetInputRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept
    try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveChoiceSetInput, AdaptiveSharedNamespace::ChoiceSetInput, AdaptiveSharedNamespace::ChoiceSetInputParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;

    std::vector<std::string> AdaptiveChoiceSetInputRenderer::GetChoiceSetValueVector(_In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput)
    {
        HString value;
        THROW_IF_FAILED(adaptiveChoiceSetInput->get_Value(value.GetAddressOf()));

        std::vector<std::string> values;
        std::string stdValue = HStringToUTF8(value.Get());
        std::stringstream streamValue(stdValue);

        while (streamValue.good())
        {
            std::string subString;
            std::getline(streamValue, subString, ',');
            values.push_back(std::move(subString));
        }

        return values;
    }

    bool AdaptiveChoiceSetInputRenderer::IsChoiceSelected(std::vector<std::string> selectedValues, _In_ IAdaptiveChoiceInput* choice)
    {
        HString value;
        THROW_IF_FAILED(choice->get_Value(value.GetAddressOf()));
        std::string stdValue = HStringToUTF8(value.Get());
        return std::find(selectedValues.begin(), selectedValues.end(), stdValue) != selectedValues.end();
    }

    HRESULT AdaptiveChoiceSetInputRenderer::BuildCompactChoiceSetInput(_In_ IAdaptiveRenderContext* renderContext,
                                                                       _In_ IAdaptiveRenderArgs* renderArgs,
                                                                       _In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                                       _COM_Outptr_ IUIElement** choiceInputSet)
    {
        ComPtr<IComboBox> comboBox =
            XamlHelpers::CreateXamlClass<IComboBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ComboBox));

        
        // Set HorizontalAlignment to Stretch (defaults to Left for combo boxes)
        ComPtr<IFrameworkElement> comboBoxAsFrameworkElement;
        RETURN_IF_FAILED(comboBox.As(&comboBoxAsFrameworkElement));
        RETURN_IF_FAILED(comboBoxAsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));

        ComPtr<IItemsControl> itemsControl;
        RETURN_IF_FAILED(comboBox.As(&itemsControl));

        ComPtr<IObservableVector<IInspectable*>> items;
        RETURN_IF_FAILED(itemsControl->get_Items(items.GetAddressOf()));

        ComPtr<IVector<IInspectable*>> itemsVector;
        RETURN_IF_FAILED(items.As(&itemsVector));

        ComPtr<IVector<ABI::AdaptiveNamespace::AdaptiveChoiceInput*>> choices;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);
        boolean wrap;
        adaptiveChoiceSetInput->get_Wrap(&wrap);

        int currentIndex = 0;
        int selectedIndex = -1;
        XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::AdaptiveChoiceInput, IAdaptiveChoiceInput>(
            choices.Get(), [&currentIndex, &selectedIndex, itemsVector, values, wrap](IAdaptiveChoiceInput* adaptiveChoiceInput) {
                HString title;
                RETURN_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));

                ComPtr<IComboBoxItem> comboBoxItem = XamlHelpers::CreateXamlClass<IComboBoxItem>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ComboBoxItem));

                XamlHelpers::SetContent(comboBoxItem.Get(), title.Get(), wrap);

                // If multiple values are specified, no option is selected
                if (values.size() == 1 && IsChoiceSelected(values, adaptiveChoiceInput))
                {
                    selectedIndex = currentIndex;
                }

                ComPtr<IInspectable> inspectable;
                RETURN_IF_FAILED(comboBoxItem.As(&inspectable));

                RETURN_IF_FAILED(itemsVector->Append(inspectable.Get()));
                currentIndex++;
                return S_OK;
            });

        ComPtr<ISelector> selector;
        RETURN_IF_FAILED(comboBox.As(&selector));
        RETURN_IF_FAILED(selector->put_SelectedIndex(selectedIndex));

        ComPtr<IUIElement> comboBoxAsUIElement;
        RETURN_IF_FAILED(comboBox.As(&comboBoxAsUIElement));
        RETURN_IF_FAILED(XamlHelpers::AddHandledTappedEvent(comboBoxAsUIElement.Get()));

        XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                    L"Adaptive.Input.ChoiceSet.Compact",
                                                    comboBoxAsFrameworkElement.Get());

        ComPtr<IAdaptiveChoiceSetInput> localAdaptiveChoiceSetInput(adaptiveChoiceSetInput);
        ComPtr<IAdaptiveInputElement> adaptiveChoiceSetInputAsAdaptiveInput;
        RETURN_IF_FAILED(localAdaptiveChoiceSetInput.As(&adaptiveChoiceSetInputAsAdaptiveInput));

        ComPtr<IUIElement> inputLayout;
        ComPtr<IBorder> validationBorder;
        RETURN_IF_FAILED(XamlHelpers::HandleInputLayoutAndValidation(adaptiveChoiceSetInputAsAdaptiveInput.Get(),
                                                    comboBoxAsUIElement.Get(),
                                                    false,
                                                    renderContext,
                                                    &inputLayout,
                                                    &validationBorder));

        // Create the InputValue and add it to the context
        ComPtr<ChoiceSetInputValue> input;
        RETURN_IF_FAILED(MakeAndInitialize<ChoiceSetInputValue>(
            &input, renderContext, adaptiveChoiceSetInput, comboBoxAsUIElement.Get(), validationBorder.Get()));
        RETURN_IF_FAILED(renderContext->AddInputValue(input.Get(), renderArgs));

        return inputLayout.CopyTo(choiceInputSet);
    }

    HRESULT AdaptiveChoiceSetInputRenderer::BuildExpandedChoiceSetInput(_In_ IAdaptiveRenderContext* renderContext,
                                                                        _In_ IAdaptiveRenderArgs* renderArgs,
                                                                        _In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                                        boolean isMultiSelect,
                                                                        _COM_Outptr_ IUIElement** choiceInputSet)
    {
        ComPtr<IVector<AdaptiveChoiceInput*>> choices;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));

        ComPtr<IStackPanel> stackPanel =
            XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        stackPanel->put_Orientation(Orientation::Orientation_Vertical);

        ComPtr<IPanel> panel;
        RETURN_IF_FAILED(stackPanel.As(&panel));

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        boolean wrap;
        adaptiveChoiceSetInput->get_Wrap(&wrap);

        XamlHelpers::IterateOverVector<AdaptiveChoiceInput, IAdaptiveChoiceInput>(
            choices.Get(), [panel, isMultiSelect, renderContext, values, wrap](IAdaptiveChoiceInput* adaptiveChoiceInput) {
                ComPtr<IUIElement> choiceItem;
                if (isMultiSelect)
                {
                    ComPtr<ICheckBox> checkBox =
                        XamlHelpers::CreateXamlClass<ICheckBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CheckBox));
                    RETURN_IF_FAILED(checkBox.As(&choiceItem));

                    ComPtr<IFrameworkElement> frameworkElement;
                    RETURN_IF_FAILED(checkBox.As(&frameworkElement));
                    XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                L"Adaptive.Input.Choice.Multiselect",
                                                                frameworkElement.Get());

                    XamlHelpers::SetToggleValue(choiceItem.Get(), IsChoiceSelected(values, adaptiveChoiceInput));
                }
                else
                {
                    ComPtr<IRadioButton> radioButton = XamlHelpers::CreateXamlClass<IRadioButton>(
                        HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RadioButton));
                    RETURN_IF_FAILED(radioButton.As(&choiceItem));

                    ComPtr<IFrameworkElement> frameworkElement;
                    RETURN_IF_FAILED(radioButton.As(&frameworkElement));
                    XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                L"Adaptive.Input.Choice.SingleSelect",
                                                                frameworkElement.Get());

                    if (values.size() == 1)
                    {
                        // When isMultiSelect is false, only 1 specified value is accepted.
                        // Otherwise, leave all options unset
                        XamlHelpers::SetToggleValue(choiceItem.Get(), IsChoiceSelected(values, adaptiveChoiceInput));
                    }
                }

                HString title;
                RETURN_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));
                XamlHelpers::SetContent(choiceItem.Get(), title.Get(), wrap);

                RETURN_IF_FAILED(XamlHelpers::AddHandledTappedEvent(choiceItem.Get()));

                XamlHelpers::AppendXamlElementToPanel(choiceItem.Get(), panel.Get());
                return S_OK;
            });

        ComPtr<IFrameworkElement> choiceSetAsFrameworkElement;
        RETURN_IF_FAILED(stackPanel.As(&choiceSetAsFrameworkElement));
        RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                     L"Adaptive.Input.ChoiceSet.Expanded",
                                                                     choiceSetAsFrameworkElement.Get()));

        ComPtr<IAdaptiveChoiceSetInput> localAdaptiveChoiceSetInput(adaptiveChoiceSetInput);
        ComPtr<IAdaptiveInputElement> adaptiveChoiceSetInputAsAdaptiveInput;
        RETURN_IF_FAILED(localAdaptiveChoiceSetInput.As(&adaptiveChoiceSetInputAsAdaptiveInput));

        ComPtr<IUIElement> choiceSetAsUIElement;
        RETURN_IF_FAILED(stackPanel.As(&choiceSetAsUIElement));

        ComPtr<IUIElement> inputLayout;
        RETURN_IF_FAILED(XamlHelpers::HandleInputLayoutAndValidation(adaptiveChoiceSetInputAsAdaptiveInput.Get(),
                                                    choiceSetAsUIElement.Get(),
                                                    false,
                                                    renderContext,
                                                    &inputLayout,
                                                    nullptr));

        // Create the InputValue and add it to the context
        ComPtr<ChoiceSetInputValue> input;
        RETURN_IF_FAILED(MakeAndInitialize<ChoiceSetInputValue>(
            &input, renderContext, adaptiveChoiceSetInput, choiceSetAsUIElement.Get(), nullptr);
        RETURN_IF_FAILED(renderContext->AddInputValue(input.Get(), renderArgs)));

        return inputLayout.CopyTo(choiceInputSet);
    }
}
