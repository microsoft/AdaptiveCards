// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveChoiceSetInputRenderer.h"
#include "AdaptiveChoiceSetInputRenderer.g.cpp"
#include "InputValue.h"
#include "ParseUtil.h"
#include "WholeItemsPanel.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::UIElement AdaptiveChoiceSetInputRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                            winrt::AdaptiveRenderContext const& renderContext,
                                                            winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            if (!XamlHelpers::SupportsInteractivity(hostConfig))
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
            XamlHelpers::ErrForRenderFailedForElement(renderContext, cardElement.ElementTypeString(), ex.message());
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

    winrt::UIElement AdaptiveChoiceSetInputRenderer::BuildCompactChoiceSetInput(winrt::AdaptiveRenderContext const& renderContext,
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

            if (values.size() == 1 && IsChoiceSelected(values, adaptiveChoiceInput))
            {
                // If multiple values are specified, no option is selected
                selectedIndex = currentIndex;
            }
            items.Append(XamlHelpers::CreateTextBlockWithContent(title, wrap));
            currentIndex++;
        }

        comboBox.SelectedIndex(selectedIndex);

        comboBox.Tapped([](winrt::IInspectable const&, winrt::TappedRoutedEventArgs const& args) { args.Handled(true); });

        XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.ChoiceSet.Compact", comboBox);

        auto [inputLayout, validationBorder] =
            XamlHelpers::HandleInputLayoutAndValidation(adaptiveChoiceSetInput, comboBox, false, renderContext);

        // Create the InputValue and add it to the context
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
        stackPanel.Orientation(winrt::Orientation::Vertical);

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        bool wrap = adaptiveChoiceSetInput.Wrap();

        for (auto input : choices)
        {
            winrt::UIElement choiceItem{nullptr};
            if (isMultiSelect)
            {
                winrt::CheckBox checkBox{};
                XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Choice.Multiselect", checkBox);
                checkBox.IsChecked(IsChoiceSelected(values, input));
                choiceItem = checkBox;
            }
            else
            {
                winrt::RadioButton radioButton{};

                XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Choice.SingleSelect", radioButton);
                if (values.size() == 1)
                {
                    // When isMultiSelect is false, only 1 specified value is accepted.
                    // Otherwise, leave all options unset
                    radioButton.IsChecked(IsChoiceSelected(values, input));
                }

                radioButton.PreviewKeyDown(
                    [stackPanel, radioButton](winrt::IInspectable const& /*sender*/, winrt::KeyRoutedEventArgs const& args) -> void
                    {
                        std::uint32_t currentButtonIndex;
                        auto children = stackPanel.Children();
                        auto size = children.Size();
                        if (const auto isButtonFound = children.IndexOf(radioButton, currentButtonIndex))
                        {
                            if (args.Key() == winrt::VirtualKey::Down)
                            {
                                auto newButtonIndex = (currentButtonIndex + 1) % size;
                                children.GetAt(newButtonIndex).as<winrt::RadioButton>().IsChecked(true);
                            }
                            else if (args.Key() == winrt::VirtualKey::Up)
                            {
                                auto newButtonIndex = (currentButtonIndex + size - 1) % size;
                                children.GetAt(newButtonIndex).as<winrt::RadioButton>().IsChecked(true);
                            }
                        }
                    });

                choiceItem = radioButton;
            }
            winrt::hstring title = input.Title();
            XamlHelpers::SetContent(choiceItem, title, wrap);
            XamlHelpers::AddHandledTappedEvent(choiceItem);
            XamlHelpers::AppendXamlElementToPanel(choiceItem, stackPanel);
        }

        XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.ChoiceSet.Expanded", stackPanel);

        winrt::UIElement inputLayout{nullptr};

        std::tie(inputLayout, std::ignore) =
            XamlHelpers::HandleInputLayoutAndValidation(adaptiveChoiceSetInput, stackPanel, false, renderContext, false);

        // Create the InputValue and add it to the context
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
        winrt::IVector<winrt::hstring> choiceList{winrt::single_threaded_vector<winrt::hstring>()};
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
        autoSuggestBox.GotFocus(
            [](IInspectable const& sender, winrt::RoutedEventArgs const& /* args */) -> void
            {
                if (const auto autoSuggestBox = sender.try_as<winrt::AutoSuggestBox>())
                {
                    autoSuggestBox.IsSuggestionListOpen(true);
                }
            });

        // When the text changes, update the ItemSource with matching items
        autoSuggestBox.TextChanged(
            [choices](IInspectable const& sender, winrt::AutoSuggestBoxTextChangedEventArgs const&) -> void
            {
                if (const auto autoSuggestBox = sender.try_as<winrt::AutoSuggestBox>())
                {
                    auto currentTextHstring = autoSuggestBox.Text();
                    std::string currentText = HStringToUTF8(currentTextHstring);

                    winrt::IVector<winrt::hstring> currentResults{winrt::single_threaded_vector<winrt::hstring>()};

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
        auto [inputLayout, validationBorder] =
            XamlHelpers::HandleInputLayoutAndValidation(adaptiveChoiceSetInput, autoSuggestBox, true, renderContext);

        auto input = winrt::make_self<winrt::FilteredChoiceSetInputValue>(adaptiveChoiceSetInput, autoSuggestBox, validationBorder);
        renderContext.AddInputValue(*input, renderArgs);

        return inputLayout;
    }
}
