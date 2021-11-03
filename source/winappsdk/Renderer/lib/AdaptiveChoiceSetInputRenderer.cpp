// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveChoiceSetInputRenderer.h"
#include "ParseUtil.h"

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
    /*HRESULT AdaptiveChoiceSetInputRenderer::RuntimeClassInitialize() noexcept { return S_OK; }*/

    winrt::Windows::UI::Xaml::UIElement AdaptiveChoiceSetInputRenderer::Render(
        winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        auto hostConfig = renderContext.HostConfig();
        if (!::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SupportsInteractivity(hostConfig))
        {
            renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                     L"ChoiceSet was stripped from card because interactivity is not supported");
        }

        rtom::ChoiceSetStyle choiceSetStyle;

        bool isMultiSelect;

        if (const auto adaptiveChoiceSetInput = cardElement.try_as<rtom::AdaptiveChoiceSetInput>())
        {
            choiceSetStyle = adaptiveChoiceSetInput.ChoiceSetStyle();
            isMultiSelect = adaptiveChoiceSetInput.IsMultiSelect();

            if (choiceSetStyle == rtom::ChoiceSetStyle::Compact && !isMultiSelect)
            {
                return BuildCompactChoiceSetInput(renderContext, renderArgs, adaptiveChoiceSetInput);
            }
            else if (choiceSetStyle == rtom::ChoiceSetStyle::Filtered)
            {
                return BuildFilteredChoiceSetInput(renderContext, renderArgs, adaptiveChoiceSetInput);
            }
            else
            {
                return BuildExpandedChoiceSetInput(renderContext, renderArgs, adaptiveChoiceSetInput, isMultiSelect);
            }
        }
        return nullptr;
    }

    std::vector<std::string> AdaptiveChoiceSetInputRenderer::GetChoiceSetValueVector(rtom::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput)
    {
        auto value = adaptiveChoiceSetInput.Value();

        std::vector<std::string> values;
        std::string stdValue = HStringToUTF8(value);
        std::stringstream streamValue(stdValue);

        while (streamValue.good())
        {
            std::string subString;
            std::getline(streamValue, subString, ',');
            values.push_back(std::move(subString));
        }

        return values;
    }

    bool AdaptiveChoiceSetInputRenderer::IsChoiceSelected(std::vector<std::string> selectedValues,
                                                          rtom::AdaptiveChoiceInput const& choice)
    {
        auto value = choice.Value();
        std::string stdValue = HStringToUTF8(value);
        return std::find(selectedValues.begin(), selectedValues.end(), stdValue) != selectedValues.end();
    }

    winrt::Windows::UI::Xaml::UIElement AdaptiveChoiceSetInputRenderer::BuildCompactChoiceSetInput(
        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs,
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput)
    {
        /*ComPtr<IComboBox> comboBox =
            XamlHelpers::CreateABIClass<IComboBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ComboBox));*/
        rtxaml::Controls::ComboBox comboBox{};

        comboBox.PlaceholderText(adaptiveChoiceSetInput.Placeholder());
        // Set HorizontalAlignment to Stretch (defaults to Left for combo boxes)
        comboBox.HorizontalAlignment(rtxaml::HorizontalAlignment::Stretch);

        auto items = comboBox.Items();

        // ComPtr<IVector<IInspectable*>> itemsVector;
        // RETURN_IF_FAILED(items.As(&itemsVector));
        auto choices = adaptiveChoiceSetInput.Choices();

        /*   ComPtr<IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveChoiceInput*>> choices;
           RETURN_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));*/
        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);
        // boolean wrap;
        // adaptiveChoiceSetInput->get_Wrap(&wrap);
        auto wrap = adaptiveChoiceSetInput.Wrap();

        int currentIndex = 0;
        int selectedIndex = -1;

        for (auto adaptiveChoiceInput : choices)
        {
            auto title = adaptiveChoiceInput.Title();

            rtxaml::Controls::ComboBoxItem comboBoxItem{};

            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetContent(comboBoxItem, title, wrap);

            if (values.size() == 1 && IsChoiceSelected(values, adaptiveChoiceInput))
            {
                // If multiple values are specified, no option is selected
                selectedIndex = currentIndex;
            }
            items.Append(comboBoxItem);
            currentIndex++;
        }

        comboBox.SelectedIndex(selectedIndex);

        /*ComPtr<IUIElement> comboBoxAsUIElement;
        RETURN_IF_FAILED(comboBox.As(&comboBoxAsUIElement));
        RETURN_IF_FAILED(::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AddHandledTappedEvent(comboBoxAsUIElement.Get()));*/
        ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AddHandledTappedEvent(comboBox);

        ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                        L"Adaptive.Input.ChoiceSet.Compact",
                                                                                        comboBox);

        /* ComPtr<IAdaptiveChoiceSetInput> localAdaptiveChoiceSetInput(adaptiveChoiceSetInput);
         ComPtr<IAdaptiveInputElement> adaptiveChoiceSetInputAsAdaptiveInput;
         RETURN_IF_FAILED(localAdaptiveChoiceSetInput.As(&adaptiveChoiceSetInputAsAdaptiveInput));*/

        /*ComPtr<IUIElement> inputLayout;
        ComPtr<IBorder> validationBorder;*/
        rtxaml::UIElement inputLayout{nullptr};
        rtxaml::Controls::Border validationBorder{};

        /*::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(
            adaptiveChoiceSetInput, comboBox, false, renderContext, inputLayout, validationBorder);*/

        // TODO: revisit this
        std::tie(inputLayout, validationBorder) =
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(adaptiveChoiceSetInput, comboBox, false, renderContext);

        /* RETURN_IF_FAILED(::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(
             adaptiveChoiceSetInputAsAdaptiveInput.Get(), comboBoxAsUIElement.Get(), false, renderContext, &inputLayout, &validationBorder));*/
        /* ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(
             adaptiveChoiceSetInput, comboBox, false, renderContext, inputLayout, validationBorder);*/

        /* ComPtr<ISelector> comboBoxAsSelector;
         RETURN_IF_FAILED(comboBox.As(&comboBoxAsSelector));*/
        if (const auto comboBoxAsSelector = comboBox.try_as<rtxaml::Controls::Primitives::Selector>())
        {
            rtrender::CompactChoiceSetInputValue input{adaptiveChoiceSetInput, comboBoxAsSelector, validationBorder};
            renderContext.AddInputValue(input, renderArgs);
        }

        // Create the InputValue and add it to the context
        /*ComPtr<CompactChoiceSetInputValue> input;
        RETURN_IF_FAILED(MakeAndInitialize<CompactChoiceSetInputValue>(
            &input, adaptiveChoiceSetInput, comboBoxAsSelector.Get(), validationBorder.Get()));
        RETURN_IF_FAILED(renderContext->AddInputValue(input.Get(), renderArgs));*/

        return inputLayout;
    }

    rtxaml::UIElement AdaptiveChoiceSetInputRenderer::BuildExpandedChoiceSetInput(rtrender::AdaptiveRenderContext const& renderContext,
                                                                                  rtrender::AdaptiveRenderArgs const& renderArgs,
                                                                                  rtom::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput,
                                                                                  bool isMultiSelect)
    {
        /* ComPtr<IVector<AdaptiveChoiceInput*>> choices;
         RETURN_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));*/
        auto choices = adaptiveChoiceSetInput.Choices();

        /*ComPtr<IStackPanel> stackPanel = ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::CreateABIClass<IStackPanel>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        stackPanel->put_Orientation(Orientation::Orientation_Vertical);*/
        rtxaml::Controls::StackPanel stackPanel{};
        // No need to set vertical orientation, that's default
        /* stackPanel.Orientation(rtxaml::Controls::Orientation::Vertical);*/

        /*ComPtr<IPanel> panel;
        RETURN_IF_FAILED(stackPanel.As(&panel));*/

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        /* boolean wrap;
         adaptiveChoiceSetInput->get_Wrap(&wrap);*/
        auto wrap = adaptiveChoiceSetInput.Wrap();

        for (auto input : choices)
        {
            rtxaml::UIElement choiceItem{nullptr};
            if (isMultiSelect)
            {
                rtxaml::Controls::CheckBox checkBox{};
                // TODO: no need to cast, right?
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                                L"Adaptive.Input.Choice.Multiselect",
                                                                                                checkBox);

                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetToggleValue(checkBox, IsChoiceSelected(values, input));
                // TODO: is this correct way?
                choiceItem = checkBox;
            }
            else
            {
                rtxaml::Controls::RadioButton radioButton{};

                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                                L"Adaptive.Input.Choice.SingleSelect",
                                                                                                radioButton);
                if (values.size() == 1)
                {
                    // When isMultiSelect is false, only 1 specified value is accepted.
                    // Otherwise, leave all options unset
                    ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetToggleValue(radioButton, IsChoiceSelected(values, input));
                }
                choiceItem = radioButton;
            }
            winrt::hstring title = input.Title();
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetContent(choiceItem, title, wrap);
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AddHandledTappedEvent(choiceItem);
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AppendXamlElementToPanel(choiceItem, stackPanel);
        }

        /* ComPtr<IFrameworkElement> choiceSetAsFrameworkElement;
         RETURN_IF_FAILED(stackPanel.As(&choiceSetAsFrameworkElement));
         RETURN_IF_FAILED(::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(
             renderContext, L"Adaptive.Input.ChoiceSet.Expanded", choiceSetAsFrameworkElement.Get()));*/
        ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                        L"Adaptive.Input.ChoiceSet.Expanded",
                                                                                        stackPanel);

        /*  ComPtr<IAdaptiveChoiceSetInput> localAdaptiveChoiceSetInput(adaptiveChoiceSetInput);
          ComPtr<IAdaptiveInputElement> adaptiveChoiceSetInputAsAdaptiveInput;
          RETURN_IF_FAILED(localAdaptiveChoiceSetInput.As(&adaptiveChoiceSetInputAsAdaptiveInput));*/

        /* ComPtr<IUIElement> choiceSetAsUIElement;
         RETURN_IF_FAILED(stackPanel.As(&choiceSetAsUIElement));*/

        /*ComPtr<IUIElement> inputLayout;
        RETURN_IF_FAILED(::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(
            adaptiveChoiceSetInputAsAdaptiveInput.Get(), choiceSetAsUIElement.Get(), false, renderContext, &inputLayout, nullptr));*/
        rtxaml::UIElement inputLayout{nullptr};

        // TODO: is this correct way?
        std::tie(inputLayout, std::ignore) =
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(adaptiveChoiceSetInput, stackPanel, false, renderContext);

        // Create the InputValue and add it to the context
        /* ComPtr<ExpandedChoiceSetInputValue> input;
         RETURN_IF_FAILED(MakeAndInitialize<ExpandedChoiceSetInputValue>(&input, adaptiveChoiceSetInput, panel.Get(),
         nullptr)); RETURN_IF_FAILED(renderContext->AddInputValue(input.Get(), renderArgs));*/

        // return inputLayout.CopyTo(choiceInputSet);
        return inputLayout;
    }

    rtxaml::UIElement AdaptiveChoiceSetInputRenderer::BuildFilteredChoiceSetInput(rtrender::AdaptiveRenderContext const& renderContext,
                                                                                  rtrender::AdaptiveRenderArgs const& renderArgs,
                                                                                  rtom::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput)
    {
        /*ComPtr<IAutoSuggestBox> autoSuggestBox = ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::CreateABIClass<IAutoSuggestBox>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_AutoSuggestBox));

        ComPtr<IItemsControl> autoSuggestBoxAsItemsControl;
        RETURN_IF_FAILED(autoSuggestBox.As(&autoSuggestBoxAsItemsControl));*/

        rtxaml::Controls::AutoSuggestBox autoSuggestBox{};

        /*ComPtr<IVector<AdaptiveChoiceInput*>> choices;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));*/

        auto choices = adaptiveChoiceSetInput.Choices();

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        // Set up the initial choice list, and set the value if present
        // ComPtr<IVector<HSTRING>> choiceList = Microsoft::WRL::Make<Vector<HSTRING>>();
        // IterateOverVector<AdaptiveChoiceInput, IAdaptiveChoiceInput>(
        //    choices.Get(),
        //    [choiceList, values, autoSuggestBox](IAdaptiveChoiceInput* adaptiveChoiceInput)
        //    {
        //        HString title;
        //        RETURN_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));
        //        RETURN_IF_FAILED(choiceList->Append(title.Get()));

        //        // If multiple values are specified, no option is selected
        //        if (values.size() == 1 && IsChoiceSelected(values, adaptiveChoiceInput))
        //        {
        //            RETURN_IF_FAILED(autoSuggestBox->put_Text(title.Get()));
        //        }

        //        return S_OK;
        //    });
        // TODO: is this a correct way to initialize a vector?
        winrt::Windows::Foundation::Collections::IVector<winrt::hstring> choiceList{};
        for (auto input : choices)
        {
            auto title = input.Title();
            choiceList.Append(title);

            if (values.size() == 1 && IsChoiceSelected(values, input))
            {
                autoSuggestBox.Text(title);
            }
        }

        /*ComPtr<IInspectable> choiceListAsInspectable;
        RETURN_IF_FAILED(choiceList.As(&choiceListAsInspectable));
        RETURN_IF_FAILED(autoSuggestBoxAsItemsControl->put_ItemsSource(choiceListAsInspectable.Get()));*/
        autoSuggestBox.ItemsSource(choiceList);

        // When we get focus open the suggestion list. This ensures the choices are shown on first focus.
        // ComPtr<IUIElement5> autoSuggestBoxAsUIElement5;
        // RETURN_IF_FAILED(autoSuggestBox.As(&autoSuggestBoxAsUIElement5));
        // EventRegistrationToken gotFocusToken;
        // RETURN_IF_FAILED(autoSuggestBoxAsUIElement5->add_GettingFocus(
        //    Callback<ABI::Windows::Foundation::ITypedEventHandler<UIElement*, ABI::Windows::UI::Xaml::Input::GettingFocusEventArgs*>>(
        //        [autoSuggestBox](IInspectable* /*sender*/, ABI::Windows::UI::Xaml::Input::IGettingFocusEventArgs*
        //                         /*args*/) -> HRESULT
        //        {
        //            autoSuggestBox->put_IsSuggestionListOpen(true);
        //            return S_OK;
        //        })
        //        .Get(),
        //    &gotFocusToken));
        autoSuggestBox.GettingFocus([autoSuggestBox](IInspectable const&, rtxaml::Input::GettingFocusEventArgs const& args)
                                    { autoSuggestBox.IsSuggestionListOpen(true); });

        autoSuggestBox.TextChanged(
            [choices](IInspectable const& sender, rtxaml::Controls::AutoSuggestBoxTextChangedEventArgs const&)
            {
                // TODO: is this correct way to do it?
                if (const auto autoSuggestBox = sender.try_as<rtxaml::Controls::AutoSuggestBox>())
                {
                    auto currentTextHstring = autoSuggestBox.Text();
                    std::string currentText = HStringToUTF8(currentTextHstring);

                    winrt::Windows::Foundation::Collections::IVector<winrt::hstring> currentResults{};

                    for (auto input : choices)
                    {
                        auto titleHString = input.Title();
                        std::string title = HStringToUTF8(titleHString);

                        if (::AdaptiveCards::ParseUtil::ToLowercase(title).find(
                                ::AdaptiveCards::ParseUtil::ToLowercase(currentText)) != std::string::npos)
                        {
                            currentResults.Append(titleHString);
                        }
                    }
                    autoSuggestBox.ItemsSource(currentResults);
                }
            });

        // When the text changes, update the ItemSource with matching items
        /* EventRegistrationToken textChangedToken;
         RETURN_IF_FAILED(autoSuggestBox->add_TextChanged(
             Callback<ABI::Windows::Foundation::ITypedEventHandler<AutoSuggestBox*, AutoSuggestBoxTextChangedEventArgs*>>(
                 [choices, autoSuggestBoxAsItemsControl](IInspectable* sender, IAutoSuggestBoxTextChangedEventArgs*) -> HRESULT
                 {
                     ComPtr<IInspectable> localSender = sender;

                     ComPtr<IAutoSuggestBox> autoSuggestBox;
                     RETURN_IF_FAILED(localSender.As(&autoSuggestBox));

                     HString currentTextHstring;
                     RETURN_IF_FAILED(autoSuggestBox->get_Text(currentTextHstring.GetAddressOf()));
                     std::string currentText = HStringToUTF8(currentTextHstring.Get());

                     ComPtr<IVector<HSTRING>> currentResults = Microsoft::WRL::Make<Vector<HSTRING>>();

                     IterateOverVector<AdaptiveChoiceInput, IAdaptiveChoiceInput>(
                         choices.Get(),
                         [currentText, currentResults](IAdaptiveChoiceInput* adaptiveChoiceInput)
                         {
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
             &textChangedToken));*/

        /* ComPtr<IUIElement> autoSuggestBoxAsUIElement;
         RETURN_IF_FAILED(autoSuggestBox.As(&autoSuggestBoxAsUIElement));

         ComPtr<IAdaptiveChoiceSetInput> localChoiceSetInput(adaptiveChoiceSetInput);
         ComPtr<IAdaptiveInputElement> choiceSetInputAsAdaptiveInput;
         RETURN_IF_FAILED(localChoiceSetInput.As(&choiceSetInputAsAdaptiveInput));*/

        // Handle input validation
       /* ComPtr<IUIElement> inputLayout;
        ComPtr<IBorder> validationBorder;
        RETURN_IF_FAILED(::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(
            choiceSetInputAsAdaptiveInput.Get(), autoSuggestBoxAsUIElement.Get(), true, renderContext, &inputLayout, &validationBorder));*/
        rtxaml::UIElement inputLayout{nullptr};
        rtxaml::Controls::Border validationBorder;

        std::tie(inputLayout, validationBorder) = ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(
            adaptiveChoiceSetInput, autoSuggestBox, true, renderContext);

        // Create the InputValue and add it to the context
       /* ComPtr<FilteredChoiceSetInputValue> input;
        RETURN_IF_FAILED(MakeAndInitialize<FilteredChoiceSetInputValue>(
            &input, adaptiveChoiceSetInput, autoSuggestBox.Get(), validationBorder.Get()));
        RETURN_IF_FAILED(renderContext->AddInputValue(input.Get(), renderArgs));*/
        rtrender::FilteredChoiceSetInputValue input{adaptiveChoiceSetInput, autoSuggestBox, validationBorder};
        renderContext.AddInputValue(input, renderArgs);

        //RETURN_IF_FAILED(inputLayout.CopyTo(choiceInputSet));
        return inputLayout;
    }
}
