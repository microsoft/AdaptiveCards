// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveChoiceSetInputRenderer.h"
#include "AdaptiveChoiceSetInputRenderer.g.cpp"
#include "ParseUtil.h"

using namespace AdaptiveCards::Rendering::Uwp::XamlHelpers;
namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    winrt::UIElement AdaptiveChoiceSetInputRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                             winrt::AdaptiveRenderContext const& renderContext,
                                                             winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            if (!SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(winrt::WarningStatusCode::InteractivityNotSupported,
                                         L"ChoiceSet was stripped from card because interactivity is not supported");
            }

            winrt::ChoiceSetStyle choiceSetStyle;

            bool isMultiSelect;

            if (const auto adaptiveChoiceSetInput = cardElement.try_as<winrt::AdaptiveChoiceSetInput>())
            {
                choiceSetStyle = adaptiveChoiceSetInput.ChoiceSetStyle();
                isMultiSelect = adaptiveChoiceSetInput.IsMultiSelect();

                if (choiceSetStyle == winrt::ChoiceSetStyle::Compact && !isMultiSelect)
                {
                    return BuildCompactChoiceSetInput(renderContext, renderArgs, adaptiveChoiceSetInput);
                }
                else if (choiceSetStyle == winrt::ChoiceSetStyle::Filtered)
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

    std::vector<std::string> AdaptiveChoiceSetInputRenderer::GetChoiceSetValueVector(winrt::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput)
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
                                                          winrt::AdaptiveChoiceInput const& choice)
    {
        auto value = choice.Value();
        std::string stdValue = HStringToUTF8(value);
        return std::find(selectedValues.begin(), selectedValues.end(), stdValue) != selectedValues.end();
    }

    winrt::Windows::UI::Xaml::UIElement
    AdaptiveChoiceSetInputRenderer::BuildCompactChoiceSetInput(winrt::AdaptiveRenderContext const& renderContext,
                                                               winrt::AdaptiveRenderArgs const& renderArgs,
                                                               winrt::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput)
    {
        winrt::ComboBox comboBox{};

        comboBox.PlaceholderText(adaptiveChoiceSetInput.Placeholder());
        // Set HorizontalAlignment to Stretch (defaults to Left for combo boxes)
        comboBox.HorizontalAlignment(winrt::HorizontalAlignment::Stretch);

        auto items = comboBox.Items();
        auto choices = adaptiveChoiceSetInput.Choices();

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        bool wrap = adaptiveChoiceSetInput.Wrap();

        int currentIndex = 0;
        int selectedIndex = -1;

        for (auto adaptiveChoiceInput : choices)
        {
            auto title = adaptiveChoiceInput.Title();

            winrt::ComboBoxItem comboBoxItem{};

             SetContent(comboBoxItem, title, wrap);

            if (values.size() == 1 && IsChoiceSelected(values, adaptiveChoiceInput))
            {
                // If multiple values are specified, no option is selected
                selectedIndex = currentIndex;
            }
            items.Append(comboBoxItem);
            currentIndex++;
        }

        comboBox.SelectedIndex(selectedIndex);

        comboBox.Tapped([](winrt::IInspectable const&, winrt::TappedRoutedEventArgs const& args)
                        { args.Handled(true); });

         SetStyleFromResourceDictionary(renderContext,
                                                                                     L"Adaptive.Input.ChoiceSet.Compact",
                                                                                     comboBox);

        auto& [inputLayout, validationBorder] =
             HandleInputLayoutAndValidation(adaptiveChoiceSetInput, comboBox, false, renderContext);

        // Create the InputValue and add it to the context
        // TODO: come back here. AddInputValue probably needs to be modified to take in appropriate parameter
        auto input = winrt::make_self<winrt::CompactChoiceSetInputValue>(adaptiveChoiceSetInput, comboBox, validationBorder);
        renderContext.AddInputValue(*input, renderArgs);

        return inputLayout;
    }

    winrt::UIElement AdaptiveChoiceSetInputRenderer::BuildExpandedChoiceSetInput(winrt::AdaptiveRenderContext const& renderContext,
                                                                                  winrt::AdaptiveRenderArgs const& renderArgs,
                                                                                  winrt::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput,
                                                                                  bool isMultiSelect)
    {
        auto choices = adaptiveChoiceSetInput.Choices();

        winrt::StackPanel stackPanel{};
        // TODO: No need to set vertical orientation, that's default, right?
        /* stackPanel.Orientation(winrt::Orientation::Vertical);*/

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        bool wrap = adaptiveChoiceSetInput.Wrap();

        for (auto input : choices)
        {
            winrt::UIElement choiceItem{nullptr};
            if (isMultiSelect)
            {
                winrt::CheckBox checkBox{};
                // TODO: no need to cast, right?
                 SetStyleFromResourceDictionary(renderContext,
                                                                                             L"Adaptive.Input.Choice.Multiselect",
                                                                                             checkBox);

                 SetToggleValue(checkBox, IsChoiceSelected(values, input));
                // TODO: is this correct way?
                choiceItem = checkBox;
            }
            else
            {
                winrt::RadioButton radioButton{};

                 SetStyleFromResourceDictionary(renderContext,
                                                                                             L"Adaptive.Input.Choice.SingleSelect",
                                                                                             radioButton);
                if (values.size() == 1)
                {
                    // When isMultiSelect is false, only 1 specified value is accepted.
                    // Otherwise, leave all options unset
                     SetToggleValue(radioButton, IsChoiceSelected(values, input));
                }
                choiceItem = radioButton;
            }
            winrt::hstring title = input.Title();
             SetContent(choiceItem, title, wrap);
             AddHandledTappedEvent(choiceItem);
             AppendXamlElementToPanel(choiceItem, stackPanel);
        }

         SetStyleFromResourceDictionary(renderContext,
                                                                                     L"Adaptive.Input.ChoiceSet.Expanded",
                                                                                     stackPanel);

        winrt::UIElement inputLayout{nullptr};

        std::tie(inputLayout, std::ignore) =  HandleInputLayoutAndValidation(
            adaptiveChoiceSetInput, stackPanel, false, renderContext, false);

        // Create the InputValue and add it to the context
        // TODO: revisit this. AddInputValue args need to be modified to accept proper inputValue
        auto input = winrt::make_self<winrt::ExpandedChoiceSetInputValue>(adaptiveChoiceSetInput, stackPanel, nullptr);
        renderContext.AddInputValue(*input, renderArgs);
        return inputLayout;
    }

    winrt::UIElement AdaptiveChoiceSetInputRenderer::BuildFilteredChoiceSetInput(winrt::AdaptiveRenderContext const& renderContext,
                                                                                  winrt::AdaptiveRenderArgs const& renderArgs,
                                                                                  winrt::AdaptiveChoiceSetInput const& adaptiveChoiceSetInput)
    {
        winrt::AutoSuggestBox autoSuggestBox{};

        auto choices = adaptiveChoiceSetInput.Choices();

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        // Set up the initial choice list, and set the value if present
        // TODO: is this a correct way to initialize a vector?
        winrt::IVector<winrt::hstring> choiceList{};
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
        autoSuggestBox.GettingFocus([autoSuggestBox](IInspectable const&, winrt::GettingFocusEventArgs const& args) -> void
                                    { autoSuggestBox.IsSuggestionListOpen(true); });

        // TODO: no need for token, right?
        // When the text changes, update the ItemSource with matching items
        autoSuggestBox.TextChanged(
            [choices](IInspectable const& sender, winrt::AutoSuggestBoxTextChangedEventArgs const&) -> void
            {
                // TODO: is this correct way to do it?
                if (const auto autoSuggestBox = sender.try_as<winrt::AutoSuggestBox>())
                {
                    auto currentTextHstring = autoSuggestBox.Text();
                    std::string currentText = HStringToUTF8(currentTextHstring);

                    winrt::IVector<winrt::hstring> currentResults{};

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
        auto& [inputLayout, validationBorder] =
             HandleInputLayoutAndValidation(adaptiveChoiceSetInput, autoSuggestBox, true, renderContext);

        //TODO: come back here. Create the InputValue and add it to the context
        auto input = winrt::make_self<winrt::FilteredChoiceSetInputValue>(adaptiveChoiceSetInput, autoSuggestBox, validationBorder);
        renderContext.AddInputValue(*input, renderArgs);

        return inputLayout;
    }
}
