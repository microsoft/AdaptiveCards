// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextInputRenderer.h"
#include "AdaptiveTextInputRenderer.g.cpp"
#include "ActionHelpers.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    std::tuple<rtxaml::UIElement, rtxaml::Controls::Border> AdaptiveTextInputRenderer::HandleLayoutAndValidation(
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveTextInput const& adaptiveTextInput,
        winrt::Windows::UI::Xaml::UIElement const& inputUIElement,
        winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
        winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        // The text box may need to go into a number of parent containers to handle validation and inline actions.
        // textBoxParentContainer represents the current parent container.
        auto textBoxParentContainer = inputUIElement;

        // If there's any validation on this input, put the input inside a border. We don't use
        // XamlHelpers::HandleInputLayoutAndValidation validation border because that would wrap any inline action as
        // well as the text input, which is not the desired behavior.
        winrt::hstring regex = adaptiveTextInput.Regex();
        bool isRequired = adaptiveTextInput.IsRequired();

        rtxaml::Controls::Border validationBorder{nullptr};

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
            rtom::TextInputStyle style = adaptiveTextInput.TextInputStyle();
            isMultiline &= style != rtom::TextInputStyle::Password;
            // TODO: not sure why inputUIElement is passed twice here.. (as textBoxParentContainer)
            textBoxParentContainer = ::AdaptiveCards::Rendering::Uwp::ActionHelpers::HandleInlineAction(
                renderContext, renderArgs, inputUIElement, textBoxParentContainer, isMultiline, inlineAction);
        }

        if (!adaptiveTextInput.IsMultiline())
        {
            auto textBoxFrameworkElement = textBoxParentContainer.as<rtxaml::FrameworkElement>();
            textBoxFrameworkElement.VerticalAlignment(rtxaml::VerticalAlignment::Top);
        }

        // Call XamlHelpers::HandleInputLayoutAndValidation to handle accessibility properties. Pass nullptr for
        // validationBorder as we've already handled that above.
        rtxaml::UIElement inputLayout{nullptr};

        std::tie(inputLayout, std::ignore) = ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleInputLayoutAndValidation(
            adaptiveTextInput, textBoxParentContainer, !regex.empty(), renderContext, false);

        return {inputLayout, validationBorder};
    }

    // TODO: should it be rtom::IAdaptiveTextInput for first arg?
    rtxaml::UIElement AdaptiveTextInputRenderer::RenderTextBox(rtom::AdaptiveTextInput const& adaptiveTextInput,
                                                               rtrender::AdaptiveRenderContext const& renderContext,
                                                               rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        rtxaml::Controls::TextBox textBox{};

        if (adaptiveTextInput.IsMultiline())
        {
            textBox.AcceptsReturn(true);
            textBox.TextWrapping(rtxaml::TextWrapping::Wrap);
        }

        textBox.Text(adaptiveTextInput.Value());
        textBox.MaxLength(adaptiveTextInput.MaxLength());
        textBox.PlaceholderText(adaptiveTextInput.Placeholder());

        rtom::TextInputStyle textInputStyle = adaptiveTextInput.TextInputStyle();

        rtxaml::Input::InputScopeName inputScopeName{};

        switch (textInputStyle)
        {
        case rtom::TextInputStyle::Email:
            // TODO: why smtp instead of name/email?
            inputScopeName.NameValue(rtxaml::Input::InputScopeNameValue::EmailSmtpAddress);
            break;

        case rtom::TextInputStyle::Tel:
            inputScopeName.NameValue(rtxaml::Input::InputScopeNameValue::TelephoneNumber);
            break;

        case rtom::TextInputStyle::Url:
            inputScopeName.NameValue(rtxaml::Input::InputScopeNameValue::Url);
            break;
        }

        rtxaml::Input::InputScope inputScope{};
        inputScope.Names().Append(inputScopeName);

        textBox.InputScope(inputScope);

        auto& [textInputControl, validationBorder] =
            HandleLayoutAndValidation(adaptiveTextInput, textBox, renderContext, renderArgs);

        // TODO: come back here, not sure if this is correct?
        auto inputValue = winrt::make_self<rtrender::TextInputValue>(adaptiveTextInput, textBox, validationBorder);
        renderContext.AddInputValue(*inputValue, renderArgs);

        ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Text", textBox);
        return textInputControl;
    }

    rtxaml::UIElement AdaptiveTextInputRenderer::RenderPasswordBox(rtom::AdaptiveTextInput const& adaptiveTextInput,
                                                                   rtrender::AdaptiveRenderContext const& renderContext,
                                                                   rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        rtxaml::Controls::PasswordBox passwordBox{};

        passwordBox.Password(adaptiveTextInput.Value());
        passwordBox.MaxLength(adaptiveTextInput.MaxLength());
        passwordBox.PlaceholderText(adaptiveTextInput.Placeholder());

        auto& [textInputControl, validationBorder] =
            HandleLayoutAndValidation(adaptiveTextInput, passwordBox, renderContext, renderArgs);

        // TODO: come back to inputs, not sure if it's correct
        auto inputValue = winrt::make_self<rtrender::PasswordInputValue>(adaptiveTextInput, passwordBox, validationBorder);
        renderContext.AddInputValue(*inputValue, renderArgs);
        // TODO: no custom style for passwordBox I guess?
        return textInputControl;
    }

    rtxaml::UIElement AdaptiveTextInputRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                        rtrender::AdaptiveRenderContext const& renderContext,
                                                        rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            if (!::AdaptiveCards::Rendering::Uwp::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                         L"Text Input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            auto adaptiveTextInput = cardElement.as<rtom::AdaptiveTextInput>();
            rtom::TextInputStyle textInputStyle = adaptiveTextInput.TextInputStyle();
            if (textInputStyle == rtom::TextInputStyle::Password)
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
