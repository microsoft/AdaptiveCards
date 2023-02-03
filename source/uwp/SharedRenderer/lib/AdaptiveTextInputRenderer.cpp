// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextInputRenderer.h"
#include "AdaptiveTextInputRenderer.g.cpp"
#include "ActionHelpers.h"
#include "InputValue.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    std::tuple<winrt::UIElement, winrt::Border>
    AdaptiveTextInputRenderer::HandleLayoutAndValidation(winrt::AdaptiveTextInput const& adaptiveTextInput,
                                                         winrt::UIElement const& inputUIElement,
                                                         winrt::AdaptiveRenderContext const& renderContext,
                                                         winrt::AdaptiveRenderArgs const& renderArgs)
    {
        // The text box may need to go into a number of parent containers to handle validation and inline actions.
        // textBoxParentContainer represents the current parent container.
        auto textBoxParentContainer = inputUIElement;

        // If there's any validation on this input, put the input inside a border. We don't use
        // XamlHelpers::HandleInputLayoutAndValidation validation border because that
        // would wrap any inline action as well as the text input, which is not the desired behavior.
        winrt::hstring regex = adaptiveTextInput.Regex();
        bool isRequired = adaptiveTextInput.IsRequired();

        winrt::Border validationBorder{nullptr};

        if (!regex.empty() || isRequired)
        {
            validationBorder = XamlHelpers::CreateValidationBorder(inputUIElement, renderContext);
            textBoxParentContainer = validationBorder;
        }

        // If this input has an inline action, render it next to the input
        auto inlineAction = adaptiveTextInput.InlineAction();

        if (inlineAction)
        {
            bool isMultiline = adaptiveTextInput.IsMultiline();
            winrt::TextInputStyle style = adaptiveTextInput.TextInputStyle();
            isMultiline &= style != winrt::TextInputStyle::Password;
            textBoxParentContainer = ::AdaptiveCards::Rendering::Xaml_Rendering::ActionHelpers::HandleInlineAction(
                renderContext, renderArgs, inputUIElement, textBoxParentContainer, isMultiline, inlineAction);
        }

        if (!adaptiveTextInput.IsMultiline())
        {
            if (const auto textBoxFrameworkElement = textBoxParentContainer.as<winrt::FrameworkElement>())
            {
                textBoxFrameworkElement.VerticalAlignment(winrt::VerticalAlignment::Top);
            }
        }

        // Call XamlHelpers::HandleInputLayoutAndValidation to handle accessibility
        // properties. Pass nullptr for validationBorder as we've already handled that above.
        winrt::UIElement inputLayout{nullptr};

        std::tie(inputLayout, std::ignore) =
            XamlHelpers::HandleInputLayoutAndValidation(adaptiveTextInput, textBoxParentContainer, !regex.empty(), renderContext, false);

        return {inputLayout, validationBorder};
    }

    winrt::UIElement AdaptiveTextInputRenderer::RenderTextBox(winrt::AdaptiveTextInput const& adaptiveTextInput,
                                                              winrt::AdaptiveRenderContext const& renderContext,
                                                              winrt::AdaptiveRenderArgs const& renderArgs)
    {
        winrt::TextBox textBox{};

        if (adaptiveTextInput.IsMultiline())
        {
            textBox.AcceptsReturn(true);
            textBox.TextWrapping(winrt::TextWrapping::Wrap);
        }

        textBox.Text(adaptiveTextInput.Value());
        textBox.MaxLength(adaptiveTextInput.MaxLength());
        textBox.PlaceholderText(adaptiveTextInput.Placeholder());

        winrt::TextInputStyle textInputStyle = adaptiveTextInput.TextInputStyle();

        winrt::InputScopeName inputScopeName{};

        switch (textInputStyle)
        {
        case winrt::TextInputStyle::Email:
            inputScopeName.NameValue(winrt::InputScopeNameValue::EmailSmtpAddress);
            break;

        case winrt::TextInputStyle::Tel:
            inputScopeName.NameValue(winrt::InputScopeNameValue::TelephoneNumber);
            break;

        case winrt::TextInputStyle::Url:
            inputScopeName.NameValue(winrt::InputScopeNameValue::Url);
            break;
        }

        winrt::InputScope inputScope{};
        inputScope.Names().Append(inputScopeName);

        textBox.InputScope(inputScope);

        auto [textInputControl, validationBorder] = HandleLayoutAndValidation(adaptiveTextInput, textBox, renderContext, renderArgs);

        auto inputValue = winrt::make_self<winrt::TextInputValue>(adaptiveTextInput, textBox, validationBorder);
        renderContext.AddInputValue(*inputValue, renderArgs);

        XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Text", textBox);
        return textInputControl;
    }

    winrt::UIElement AdaptiveTextInputRenderer::RenderPasswordBox(winrt::AdaptiveTextInput const& adaptiveTextInput,
                                                                  winrt::AdaptiveRenderContext const& renderContext,
                                                                  winrt::AdaptiveRenderArgs const& renderArgs)
    {
        winrt::PasswordBox passwordBox{};

        passwordBox.Password(adaptiveTextInput.Value());
        passwordBox.MaxLength(adaptiveTextInput.MaxLength());
        passwordBox.PlaceholderText(adaptiveTextInput.Placeholder());

        auto [textInputControl, validationBorder] =
            HandleLayoutAndValidation(adaptiveTextInput, passwordBox, renderContext, renderArgs);

        auto inputValue = winrt::make_self<winrt::PasswordInputValue>(adaptiveTextInput, passwordBox, validationBorder);
        renderContext.AddInputValue(*inputValue, renderArgs);
        return textInputControl;
    }

    winrt::UIElement AdaptiveTextInputRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                       winrt::AdaptiveRenderContext const& renderContext,
                                                       winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            if (!XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(winrt::WarningStatusCode::InteractivityNotSupported,
                                         L"Text Input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            auto adaptiveTextInput = cardElement.as<winrt::AdaptiveTextInput>();
            winrt::TextInputStyle textInputStyle = adaptiveTextInput.TextInputStyle();
            if (textInputStyle == winrt::TextInputStyle::Password)
            {
                return RenderPasswordBox(adaptiveTextInput, renderContext, renderArgs);
            }
            else
            {
                return RenderTextBox(adaptiveTextInput, renderContext, renderArgs);
            }
        }
        catch (winrt::hresult_error const& ex)
        {
            XamlHelpers::ErrForRenderFailedForElement(renderContext, cardElement.ElementTypeString(), ex.message());
            return nullptr;
        }
    }
}
