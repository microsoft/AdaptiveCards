// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveChoiceSetInputRenderer.h"
#include "AdaptiveChoiceSetInputRenderer.g.cpp"
#include "ParseUtil.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    winrt::Windows::UI::Xaml::UIElement AdaptiveChoiceSetInputRenderer::Render(
        winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        try
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
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
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
        rtxaml::Controls::ComboBox comboBox{};

        comboBox.PlaceholderText(adaptiveChoiceSetInput.Placeholder());
        // Set HorizontalAlignment to Stretch (defaults to Left for combo boxes)
        comboBox.HorizontalAlignment(rtxaml::HorizontalAlignment::Stretch);

        auto items = comboBox.Items();
        auto choices = adaptiveChoiceSetInput.Choices();

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        bool wrap = adaptiveChoiceSetInput.Wrap();

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

        comboBox.Tapped([](winrt::Windows::Foundation::IInspectable const&, rtxaml::Input::TappedRoutedEventArgs const& args)
                        { args.Handled(true); });

        ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                        L"Adaptive.Input.ChoiceSet.Compact",
                                                                                        comboBox);

        rtxaml::UIElement inputLayout{nullptr};
        rtxaml::Controls::Border validationBorder{nullptr};

        // TODO: revisit this
        std::tie(inputLayout, validationBorder) =
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(adaptiveChoiceSetInput, comboBox, false, renderContext);

        // Create the InputValue and add it to the context
        // TODO: come back here. AddInputValue probably needs to be modified to take in appropriate parameter
        auto input = winrt::make_self<rtrender::CompactChoiceSetInputValue>(adaptiveChoiceSetInput, comboBox, validationBorder);
        renderContext.AddInputValue(*input, renderArgs);

        return inputLayout;
    }

    rtxaml::UIElement AdaptiveChoiceSetInputRenderer::BuildExpandedChoiceSetInput(rtrender::AdaptiveRenderContext const& renderContext,
                                                                                  rtrender::AdaptiveRenderArgs const& renderArgs,
                                                                                  rtom::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput,
                                                                                  bool isMultiSelect)
    {
        auto choices = adaptiveChoiceSetInput.Choices();

        rtxaml::Controls::StackPanel stackPanel{};
        // TODO: No need to set vertical orientation, that's default, right?
        /* stackPanel.Orientation(rtxaml::Controls::Orientation::Vertical);*/

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        bool wrap = adaptiveChoiceSetInput.Wrap();

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

        ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                        L"Adaptive.Input.ChoiceSet.Expanded",
                                                                                        stackPanel);

        rtxaml::UIElement inputLayout{nullptr};

        // TODO: is this correct way?
        std::tie(inputLayout, std::ignore) =
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(adaptiveChoiceSetInput, stackPanel, false, renderContext, false);

        // Create the InputValue and add it to the context
        // TODO: revisit this. AddInputValue args need to be modified to accept proper inputValue
        auto input = winrt::make_self<rtrender::ExpandedChoiceSetInputValue>(adaptiveChoiceSetInput, stackPanel, nullptr);
        renderContext.AddInputValue(*input, renderArgs);
        return inputLayout;
    }

    rtxaml::UIElement AdaptiveChoiceSetInputRenderer::BuildFilteredChoiceSetInput(rtrender::AdaptiveRenderContext const& renderContext,
                                                                                  rtrender::AdaptiveRenderArgs const& renderArgs,
                                                                                  rtom::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput)
    {
        rtxaml::Controls::AutoSuggestBox autoSuggestBox{};

        auto choices = adaptiveChoiceSetInput.Choices();

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        // Set up the initial choice list, and set the value if present
        // TODO: is this a correct way to initialize a vector?
        winrt::Windows::Foundation::Collections::IVector<winrt::hstring> choiceList{};
        for (auto input : choices)
        {
            auto title = input.Title();
            choiceList.Append(title);

            // If multiple values are specified, no option is selected
            if (values.size() == 1 && IsChoiceSelected(values, input))
            {
                autoSuggestBox.Text(title);
            }
        }

        autoSuggestBox.ItemsSource(choiceList);

        // When we get focus open the suggestion list. This ensures the choices are shown on first focus.
        // TODO: no need for token, right? is this event going to clear itself? or we need a revoker?
        autoSuggestBox.GettingFocus([autoSuggestBox](IInspectable const&, rtxaml::Input::GettingFocusEventArgs const& args) -> void
                                    { autoSuggestBox.IsSuggestionListOpen(true); });

        // TODO: no need for token, right?
        // When the text changes, update the ItemSource with matching items
        autoSuggestBox.TextChanged(
            [choices](IInspectable const& sender, rtxaml::Controls::AutoSuggestBoxTextChangedEventArgs const&) -> void
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

        // Handle input validation
        rtxaml::UIElement inputLayout{nullptr};
        rtxaml::Controls::Border validationBorder{nullptr};

        std::tie(inputLayout, validationBorder) = ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(
            adaptiveChoiceSetInput, autoSuggestBox, true, renderContext);

        // Create the InputValue and add it to the context
        auto input = winrt::make_self<rtrender::FilteredChoiceSetInputValue>(adaptiveChoiceSetInput, autoSuggestBox, validationBorder);
        renderContext.AddInputValue(*input, renderArgs);

        return inputLayout;
    }
}
