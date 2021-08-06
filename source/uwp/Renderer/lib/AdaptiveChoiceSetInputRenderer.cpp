// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveChoiceSetInputRenderer.h"
#include "ParseUtil.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;

namespace AdaptiveCards::Rendering::Uwp
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
                ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"ChoiceSet was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveChoiceSetInput> adaptiveChoiceSetInput;
        RETURN_IF_FAILED(cardElement.As(&adaptiveChoiceSetInput));

        ABI::AdaptiveCards::ObjectModel::Uwp::ChoiceSetStyle choiceSetStyle;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_ChoiceSetStyle(&choiceSetStyle));

        boolean isMultiSelect;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_IsMultiSelect(&isMultiSelect));

        if (choiceSetStyle == ABI::AdaptiveCards::ObjectModel::Uwp::ChoiceSetStyle_Compact && !isMultiSelect)
        {
            RETURN_IF_FAILED(BuildCompactChoiceSetInput(renderContext, renderArgs, adaptiveChoiceSetInput.Get(), choiceInputSet));
        }
        else if (choiceSetStyle == ABI::AdaptiveCards::ObjectModel::Uwp::ChoiceSetStyle_Filtered)
        {
            RETURN_IF_FAILED(BuildFilteredChoiceSetInput(renderContext, renderArgs, adaptiveChoiceSetInput.Get(), choiceInputSet));
        }
        else
        {
            RETURN_IF_FAILED(BuildExpandedChoiceSetInput(renderContext, renderArgs, adaptiveChoiceSetInput.Get(), isMultiSelect, choiceInputSet));
        }

        return S_OK;
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
            XamlHelpers::CreateABIClass<IComboBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ComboBox));

        HString placeHolderText;
        ComPtr<IComboBox2> comboBox2;
        RETURN_IF_FAILED(comboBox.As(&comboBox2));
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_Placeholder(placeHolderText.GetAddressOf()));
        RETURN_IF_FAILED(comboBox2->put_PlaceholderText(placeHolderText.Get()));

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

        ComPtr<IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveChoiceInput*>> choices;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);
        boolean wrap;
        adaptiveChoiceSetInput->get_Wrap(&wrap);

        int currentIndex = 0;
        int selectedIndex = -1;
        IterateOverVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveChoiceInput, IAdaptiveChoiceInput>(
            choices.Get(), [&currentIndex, &selectedIndex, itemsVector, values, wrap](IAdaptiveChoiceInput* adaptiveChoiceInput) {
                HString title;
                RETURN_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));

                ComPtr<IComboBoxItem> comboBoxItem = XamlHelpers::CreateABIClass<IComboBoxItem>(
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
        RETURN_IF_FAILED(XamlHelpers::HandleInputLayoutAndValidation(
            adaptiveChoiceSetInputAsAdaptiveInput.Get(), comboBoxAsUIElement.Get(), false, renderContext, &inputLayout, &validationBorder));

        ComPtr<ISelector> comboBoxAsSelector;
        RETURN_IF_FAILED(comboBox.As(&comboBoxAsSelector));

        // Create the InputValue and add it to the context
        ComPtr<CompactChoiceSetInputValue> input;
        RETURN_IF_FAILED(MakeAndInitialize<CompactChoiceSetInputValue>(
            &input, adaptiveChoiceSetInput, comboBoxAsSelector.Get(), validationBorder.Get()));
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
            XamlHelpers::CreateABIClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        stackPanel->put_Orientation(Orientation::Orientation_Vertical);

        ComPtr<IPanel> panel;
        RETURN_IF_FAILED(stackPanel.As(&panel));

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        boolean wrap;
        adaptiveChoiceSetInput->get_Wrap(&wrap);

        IterateOverVector<AdaptiveChoiceInput, IAdaptiveChoiceInput>(
            choices.Get(), [panel, isMultiSelect, renderContext, values, wrap](IAdaptiveChoiceInput* adaptiveChoiceInput) {
                ComPtr<IUIElement> choiceItem;
                if (isMultiSelect)
                {
                    ComPtr<ICheckBox> checkBox =
                        XamlHelpers::CreateABIClass<ICheckBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CheckBox));
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
                    ComPtr<IRadioButton> radioButton = XamlHelpers::CreateABIClass<IRadioButton>(
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
        RETURN_IF_FAILED(XamlHelpers::HandleInputLayoutAndValidation(
            adaptiveChoiceSetInputAsAdaptiveInput.Get(), choiceSetAsUIElement.Get(), false, renderContext, &inputLayout, nullptr));

        // Create the InputValue and add it to the context
        ComPtr<ExpandedChoiceSetInputValue> input;
        RETURN_IF_FAILED(MakeAndInitialize<ExpandedChoiceSetInputValue>(&input, adaptiveChoiceSetInput, panel.Get(), nullptr);
                         RETURN_IF_FAILED(renderContext->AddInputValue(input.Get(), renderArgs)));

        return inputLayout.CopyTo(choiceInputSet);
    }

    HRESULT AdaptiveChoiceSetInputRenderer::BuildFilteredChoiceSetInput(_In_ IAdaptiveRenderContext* renderContext,
                                                                        _In_ IAdaptiveRenderArgs* renderArgs,
                                                                        _In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                                        _COM_Outptr_ IUIElement** choiceInputSet)
    {
        ComPtr<IAutoSuggestBox> autoSuggestBox =
            XamlHelpers::CreateABIClass<IAutoSuggestBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_AutoSuggestBox));

        ComPtr<IItemsControl> autoSuggestBoxAsItemsControl;
        RETURN_IF_FAILED(autoSuggestBox.As(&autoSuggestBoxAsItemsControl));

        ComPtr<IVector<AdaptiveChoiceInput*>> choices;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        // Set up the initial choice list, and set the value if present
        ComPtr<IVector<HSTRING>> choiceList = Microsoft::WRL::Make<Vector<HSTRING>>();
        IterateOverVector<AdaptiveChoiceInput, IAdaptiveChoiceInput>(
            choices.Get(), [choiceList, values, autoSuggestBox](IAdaptiveChoiceInput* adaptiveChoiceInput) {
                HString title;
                RETURN_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));
                RETURN_IF_FAILED(choiceList->Append(title.Get()));

                // If multiple values are specified, no option is selected
                if (values.size() == 1 && IsChoiceSelected(values, adaptiveChoiceInput))
                {
                    RETURN_IF_FAILED(autoSuggestBox->put_Text(title.Get()));
                }

                return S_OK;
            });

        ComPtr<IInspectable> choiceListAsInspectable;
        RETURN_IF_FAILED(choiceList.As(&choiceListAsInspectable));
        RETURN_IF_FAILED(autoSuggestBoxAsItemsControl->put_ItemsSource(choiceListAsInspectable.Get()));

        // When we get focus open the suggestion list. This ensures the choices are shown on first focus.
        ComPtr<IUIElement5> autoSuggestBoxAsUIElement5;
        RETURN_IF_FAILED(autoSuggestBox.As(&autoSuggestBoxAsUIElement5));
        EventRegistrationToken gotFocusToken;
        RETURN_IF_FAILED(autoSuggestBoxAsUIElement5->add_GettingFocus(
            Callback<ABI::Windows::Foundation::ITypedEventHandler<UIElement*, ABI::Windows::UI::Xaml::Input::GettingFocusEventArgs*>>(
                [autoSuggestBox](IInspectable* /*sender*/, ABI::Windows::UI::Xaml::Input::IGettingFocusEventArgs*
                                 /*args*/) -> HRESULT {
                    autoSuggestBox->put_IsSuggestionListOpen(true);
                    return S_OK;
                })
                .Get(),
            &gotFocusToken));

        // When the text changes, update the ItemSource with matching items
        EventRegistrationToken textChangedToken;
        RETURN_IF_FAILED(autoSuggestBox->add_TextChanged(
            Callback<ABI::Windows::Foundation::ITypedEventHandler<AutoSuggestBox*, AutoSuggestBoxTextChangedEventArgs*>>(
                [choices, autoSuggestBoxAsItemsControl](IInspectable* sender, IAutoSuggestBoxTextChangedEventArgs*) -> HRESULT {
                    ComPtr<IInspectable> localSender = sender;

                    ComPtr<IAutoSuggestBox> autoSuggestBox;
                    RETURN_IF_FAILED(localSender.As(&autoSuggestBox));

                    HString currentTextHstring;
                    RETURN_IF_FAILED(autoSuggestBox->get_Text(currentTextHstring.GetAddressOf()));
                    std::string currentText = HStringToUTF8(currentTextHstring.Get());

                    ComPtr<IVector<HSTRING>> currentResults = Microsoft::WRL::Make<Vector<HSTRING>>();

                    IterateOverVector<AdaptiveChoiceInput, IAdaptiveChoiceInput>(
                        choices.Get(), [currentText, currentResults](IAdaptiveChoiceInput* adaptiveChoiceInput) {
                            HString titleHString;
                            RETURN_IF_FAILED(adaptiveChoiceInput->get_Title(titleHString.GetAddressOf()));

                            std::string title = HStringToUTF8(titleHString.Get());

                            if (ParseUtil::ToLowercase(title).find(ParseUtil::ToLowercase(currentText)) != std::string::npos)
                            {
                                RETURN_IF_FAILED(currentResults->Append(titleHString.Get()));
                            }
                            return S_OK;
                        });

                    ComPtr<IInspectable> currentResultsAsInspectable;
                    RETURN_IF_FAILED(currentResults.As(&currentResultsAsInspectable));

                    RETURN_IF_FAILED(autoSuggestBoxAsItemsControl->put_ItemsSource(currentResultsAsInspectable.Get()));
                    return S_OK;
                })
                .Get(),
            &textChangedToken));

        ComPtr<IUIElement> autoSuggestBoxAsUIElement;
        RETURN_IF_FAILED(autoSuggestBox.As(&autoSuggestBoxAsUIElement));

        ComPtr<IAdaptiveChoiceSetInput> localChoiceSetInput(adaptiveChoiceSetInput);
        ComPtr<IAdaptiveInputElement> choiceSetInputAsAdaptiveInput;
        RETURN_IF_FAILED(localChoiceSetInput.As(&choiceSetInputAsAdaptiveInput));

        // Handle input validation
        ComPtr<IUIElement> inputLayout;
        ComPtr<IBorder> validationBorder;
        RETURN_IF_FAILED(XamlHelpers::HandleInputLayoutAndValidation(
            choiceSetInputAsAdaptiveInput.Get(), autoSuggestBoxAsUIElement.Get(), true, renderContext, &inputLayout, &validationBorder));

        // Create the InputValue and add it to the context
        ComPtr<FilteredChoiceSetInputValue> input;
        RETURN_IF_FAILED(MakeAndInitialize<FilteredChoiceSetInputValue>(
            &input, adaptiveChoiceSetInput, autoSuggestBox.Get(), validationBorder.Get()));
        RETURN_IF_FAILED(renderContext->AddInputValue(input.Get(), renderArgs));

        RETURN_IF_FAILED(inputLayout.CopyTo(choiceInputSet));
        return S_OK;
    }
}
