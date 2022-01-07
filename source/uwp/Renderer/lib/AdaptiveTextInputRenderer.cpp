// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextInputRenderer.h"
#include "AdaptiveTextInputRenderer.g.cpp"
#include "ActionHelpers.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    std::tuple<winrt::UIElement, winrt::Border> AdaptiveTextInputRenderer::HandleLayoutAndValidation(
        winrt::AdaptiveTextInput const& adaptiveTextInput,
        winrt::Windows::UI::Xaml::UIElement const& inputUIElement,
        winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
        winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        // The text box may need to go into a number of parent containers to handle validation and inline actions.
        // textBoxParentContainer represents the current parent container.
        auto textBoxParentContainer = inputUIElement;

        // If there's any validation on this input, put the input inside a border. We don't use
        //  ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleInputLayoutAndValidation validation border because that
        //  would wrap any inline action as
        // well as the text input, which is not the desired behavior.
        winrt::hstring regex = adaptiveTextInput.Regex();
        bool isRequired = adaptiveTextInput.IsRequired();

        winrt::Border validationBorder{nullptr};

        if (!regex.empty() || isRequired)
        {
            validationBorder = ::AdaptiveCards::Rendering::Uwp::XamlHelpers::CreateValidationBorder(inputUIElement, renderContext);
            textBoxParentContainer = validationBorder;
        }

        // If this input has an inline action, render it next to the input
        auto inlineAction = adaptiveTextInput.InlineAction();

        if (inlineAction)
        {
            bool isMultiline = adaptiveTextInput.IsMultiline();
            winrt::TextInputStyle style = adaptiveTextInput.TextInputStyle();
            isMultiline &= style != winrt::TextInputStyle::Password;
            // TODO: not sure why inputUIElement is passed twice here.. (as textBoxParentContainer)
            textBoxParentContainer = ::AdaptiveCards::Rendering::Uwp::ActionHelpers::HandleInlineAction(
                renderContext, renderArgs, inputUIElement, textBoxParentContainer, isMultiline, inlineAction);
        }

        if (!adaptiveTextInput.IsMultiline())
        {
            auto textBoxFrameworkElement = textBoxParentContainer.as<winrt::FrameworkElement>();
            textBoxFrameworkElement.VerticalAlignment(winrt::VerticalAlignment::Top);
        }

        // Call  ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleInputLayoutAndValidation to handle accessibility
        // properties. Pass nullptr for validationBorder as we've already handled that above.
        winrt::UIElement inputLayout{nullptr};

        std::tie(inputLayout, std::ignore) = ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleInputLayoutAndValidation(
            adaptiveTextInput, textBoxParentContainer, !regex.empty(), renderContext, false);

        return {inputLayout, validationBorder};
    }

    // TODO: should it be winrt::IAdaptiveTextInput for first arg?
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
            // TODO: why smtp instead of name/email?
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

        auto& [textInputControl, validationBorder] =
            HandleLayoutAndValidation(adaptiveTextInput, textBox, renderContext, renderArgs);

        // TODO: come back here, not sure if this is correct?
        auto inputValue = winrt::make_self<winrt::TextInputValue>(adaptiveTextInput, textBox, validationBorder);
        renderContext.AddInputValue(*inputValue, renderArgs);

        ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Text", textBox);
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

        auto& [textInputControl, validationBorder] =
            HandleLayoutAndValidation(adaptiveTextInput, passwordBox, renderContext, renderArgs);

        // TODO: come back to inputs, not sure if it's correct
        auto inputValue = winrt::make_self<winrt::PasswordInputValue>(adaptiveTextInput, passwordBox, validationBorder);
        renderContext.AddInputValue(*inputValue, renderArgs);
        // TODO: no custom style for passwordBox I guess?
        return textInputControl;
    }

    winrt::UIElement AdaptiveTextInputRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                       winrt::AdaptiveRenderContext const& renderContext,
                                                       winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            if (!::AdaptiveCards::Rendering::Uwp::XamlHelpers::SupportsInteractivity(hostConfig))
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
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
