// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextInputRenderer.h"
#include "ActionHelpers.h"

namespace Xaml
{
    using namespace winrt::Windows::UI::Xaml;
}

namespace XamlHelpers
{
    using namespace AdaptiveCards::Rendering::Uwp::XamlHelpers;
}

namespace ActionHelpers
{
    using namespace AdaptiveCards::Rendering::Uwp::ActionHelpers;
}

using namespace winrt::AdaptiveCards::ObjectModel::Uwp;
using namespace winrt::AdaptiveCards::Rendering::Uwp;

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    Xaml::UIElement AdaptiveTextInputRenderer::HandleLayoutAndValidation(AdaptiveTextInput adaptiveTextInput,
                                                                         Xaml::Controls::TextBox textBox,
                                                                         AdaptiveRenderContext renderContext,
                                                                         AdaptiveRenderArgs renderArgs)
    {
        // The text box may need to go into a number of parent containers to handle validation and inline actions.
        // textBoxParentContainer represents the current parent container.
        Xaml::UIElement textBoxParentContainer = textBox;

        // If there's any validation on this input, put the input inside a border. We don't use
        // XamlHelpers::HandleInputLayoutAndValidation validation border because that would wrap any inline action as
        // well as the text input, which is not the desired behavior.
        if (!adaptiveTextInput.Regex().empty() || adaptiveTextInput.IsRequired())
        {
            textBoxParentContainer = XamlHelpers::CreateValidationBorder(textBox, renderContext);
        }

        // If this input has an inline action, render it next to the input
        if (adaptiveTextInput.InlineAction() != nullptr)
        {
            textBoxParentContainer = ActionHelpers::HandleInlineAction(
                renderContext, renderArgs, textBox, textBoxParentContainer, adaptiveTextInput.InlineAction());
        }

        if (!adaptiveTextInput.IsMultiline())
        {
            textBoxParentContainer.as<Xaml::FrameworkElement>().VerticalAlignment(Xaml::VerticalAlignment::Top);
        }

        // Call XamlHelpers::HandleInputLayoutAndValidation to handle accessibility properties.
        Xaml::UIElement inputLayout =
            XamlHelpers::HandleInputLayoutAndValidation(adaptiveTextInput, textBox, !adaptiveTextInput.Regex().empty(), renderContext);

        // Create the InputValue and add it to the context
        winrt::com_ptr<::AdaptiveCards::Rendering::Uwp::TextInputValue> inputValue;
        THROW_IF_FAILED(Microsoft::WRL::MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::TextInputValue>(
            inputValue.put(),
            adaptiveTextInput.as<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTextInput>().get(),
            textBox.as<ABI::Windows::UI::Xaml::Controls::ITextBox>().get(),
            nullptr));

        renderContext.AddInputValue(inputValue.as<IAdaptiveInputValue>(), renderArgs);

        return inputLayout;
    }

    Xaml::UIElement AdaptiveTextInputRenderer::Render(IAdaptiveCardElement element, AdaptiveRenderContext renderContext, AdaptiveRenderArgs renderArgs)
    {
        if (!renderContext.HostConfig().SupportsInteractivity())
        {
            renderContext.AddWarning(winrt::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::InteractivityNotSupported,
                                     L"Text Input was stripped from card because interactivity is not supported");
            return nullptr;
        }

        AdaptiveTextInput adaptiveTextInput = element.as<AdaptiveTextInput>();
        Xaml::Controls::TextBox textBox{};

        if (adaptiveTextInput.IsMultiline())
        {
            textBox.AcceptsReturn(true);
            textBox.TextWrapping(Xaml::TextWrapping::Wrap);
        }

        textBox.Text(adaptiveTextInput.Value());
        textBox.MaxLength(adaptiveTextInput.MaxLength());
        textBox.PlaceholderText(adaptiveTextInput.Placeholder());

        Xaml::Input::InputScopeName inputScopeName{};
        switch (adaptiveTextInput.TextInputStyle())
        {
        case TextInputStyle::Email:
            inputScopeName.NameValue(Xaml::Input::InputScopeNameValue::EmailSmtpAddress);
            break;

        case TextInputStyle::Tel:
            inputScopeName.NameValue(Xaml::Input::InputScopeNameValue::TelephoneNumber);
            break;

        case TextInputStyle::Url:
            inputScopeName.NameValue(Xaml::Input::InputScopeNameValue::Url);
            break;
        }

        Xaml::Input::InputScope inputScope{};
        inputScope.Names().Append(inputScopeName);
        textBox.InputScope(inputScope);

        XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Text", textBox);

        return HandleLayoutAndValidation(adaptiveTextInput, textBox, renderContext, renderArgs);
    }
}
