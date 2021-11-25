// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextInputRenderer.h"
#include "AdaptiveTextInputRenderer.g.cpp"
#include "ActionHelpers.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    std::tuple<rtxaml::UIElement, rtxaml::Controls::Border> AdaptiveTextInputRenderer::HandleLayoutAndValidation(
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextInput const& adaptiveTextInput,
        winrt::Windows::UI::Xaml::UIElement const& inputUIElement,
        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        // If there's any validation on this input, put the input inside a border. We don't use
        // XamlHelpers::HandleInputLayoutAndValidation validation border because that would wrap any inline action as
        // well as the text input, which is not the desired behavior.
        /* ComPtr<IAdaptiveTextInput> localTextInput(adaptiveTextInput);
         ComPtr<IAdaptiveInputElement> textInputAsAdaptiveInput;
         RETURN_IF_FAILED(localTextInput.As(&textInputAsAdaptiveInput));*/

        // The text box may need to go into a number of parent containers to handle validation and inline actions.
        // textBoxParentContainer represents the current parent container.
        auto textBoxParentContainer = inputUIElement;

        winrt::hstring regex = adaptiveTextInput.Regex();
        bool isRequired = adaptiveTextInput.IsRequired();

        rtxaml::Controls::Border validationBorder{nullptr};

        if (!regex.empty() || isRequired)
        {
            validationBorder =
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::CreateValidationBorder(inputUIElement, renderContext);
        }

        // If this input has an inline action, render it next to the input
        auto inlineAction = adaptiveTextInput.InlineAction();

        if (inlineAction != nullptr)
        {
            bool isMultiline = adaptiveTextInput.IsMultiline();
            rtom::TextInputStyle style = adaptiveTextInput.TextInputStyle();
            isMultiline &= style != rtom::TextInputStyle::Password;
            // TODO: not sure why inputUIElement is passed twice here.. (as textBoxParentContainer)
            textBoxParentContainer = ::AdaptiveCards::Rendering::WinUI3::ActionHelpers::HandleInlineAction(
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
        std::tie(inputLayout, std::ignore) =
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleInputLayoutAndValidation(adaptiveTextInput,
                                                                                            inputUIElement,
                                                                                            !regex.empty(), // TODO: not sure
                                                                                                            // if it's correct way here with regex hstring
                                                                                            renderContext);

        // TODO: we can't just return xamlHelpres function cal as we need to return nullptr for validationBorder, correct?
        return {inputLayout, nullptr};
    }

    // TODO: should it be rtom::IAdaptiveTextInput for first arg?
    rtxaml::UIElement AdaptiveTextInputRenderer::RenderTextBox(rtom::AdaptiveTextInput const& adaptiveTextInput,
                                                               rtrender::AdaptiveRenderContext const& renderContext,
                                                               rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        rtxaml::Controls::TextBox textBox{};

        // boolean isMultiLine;
        // RETURN_IF_FAILED(adaptiveTextInput->get_IsMultiline(&isMultiLine));
        if (adaptiveTextInput.IsMultiline())
        {
            // RETURN_IF_FAILED(textBox->put_AcceptsReturn(true));
            // RETURN_IF_FAILED(textBox->put_TextWrapping(TextWrapping_Wrap));
            textBox.AcceptsReturn(true);
            textBox.TextWrapping(rtxaml::TextWrapping::Wrap);
        }

        /*HString textValue;
        RETURN_IF_FAILED(adaptiveTextInput->get_Value(textValue.GetAddressOf()));
        RETURN_IF_FAILED(textBox->put_Text(textValue.Get()));*/
        /* winrt::hstring textValue = adaptiveTextInput.Value();*/
        textBox.Text(adaptiveTextInput.Value());

        /*UINT32 maxLength;
        RETURN_IF_FAILED(adaptiveTextInput->get_MaxLength(&maxLength));
        RETURN_IF_FAILED(textBox->put_MaxLength(maxLength));*/
        textBox.MaxLength(adaptiveTextInput.MaxLength());

        /*ComPtr<ITextBox2> textBox2;
        RETURN_IF_FAILED(textBox.As(&textBox2));

        HString placeHolderText;
        RETURN_IF_FAILED(adaptiveTextInput->get_Placeholder(placeHolderText.GetAddressOf()));
        RETURN_IF_FAILED(textBox2->put_PlaceholderText(placeHolderText.Get()));*/
        textBox.PlaceholderText(adaptiveTextInput.Placeholder());

        /* ABI::AdaptiveCards::ObjectModel::WinUI3::TextInputStyle textInputStyle;
         RETURN_IF_FAILED(adaptiveTextInput->get_TextInputStyle(&textInputStyle));*/
        rtom::TextInputStyle textInputStyle = adaptiveTextInput.TextInputStyle();

        /*ComPtr<IInputScopeName> inputScopeName =
            XamlHelpers::CreateABIClass<IInputScopeName>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScopeName));*/
        rtxaml::Input::InputScopeName inputScopeName{};

        switch (textInputStyle)
        {
        case rtom::TextInputStyle::Email:
            /* RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_EmailSmtpAddress));*/
            // TODO: why smtp instead of name/email?
            inputScopeName.NameValue(rtxaml::Input::InputScopeNameValue::EmailSmtpAddress);
            break;

        case rtom::TextInputStyle::Tel:
            /* RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_TelephoneNumber));*/
            inputScopeName.NameValue(rtxaml::Input::InputScopeNameValue::TelephoneNumber);
            break;

        case rtom::TextInputStyle::Url:
            /* RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_Url));*/
            inputScopeName.NameValue(rtxaml::Input::InputScopeNameValue::Url);
            break;
        }

        /*  ComPtr<IInputScope> inputScope =
              XamlHelpers::CreateABIClass<IInputScope>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScope));
          ComPtr<IVector<InputScopeName*>> names;
          RETURN_IF_FAILED(inputScope->get_Names(names.GetAddressOf()));
          RETURN_IF_FAILED(names->Append(inputScopeName.Get()));*/
        rtxaml::Input::InputScope inputScope{};
        auto names = inputScope.Names();
        names.Append(inputScopeName);

        /*RETURN_IF_FAILED(textBox->put_InputScope(inputScope.Get()));*/
        textBox.InputScope(inputScope);

        /*ComPtr<IUIElement> textBoxAsUIElement;
        RETURN_IF_FAILED(textBox.As(&textBoxAsUIElement));

        ComPtr<IBorder> validationBorder;
        RETURN_IF_FAILED(HandleLayoutAndValidation(
            adaptiveTextInput, textBoxAsUIElement.Get(), renderContext, renderArgs, textInputControl, &validationBorder));

        ComPtr<TextInputValue> inputValue;
        RETURN_IF_FAILED(
            MakeAndInitialize<TextInputValue>(&inputValue, adaptiveTextInput, textBox.Get(), validationBorder.Get()));
        RETURN_IF_FAILED(renderContext->AddInputValue(inputValue.Get(), renderArgs));

        ComPtr<IFrameworkElement> textBoxAsFrameworkElement;
        RETURN_IF_FAILED(textBox.As(&textBoxAsFrameworkElement));
        RETURN_IF_FAILED(
            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Text", textBoxAsFrameworkElement.Get()));*/
        rtxaml::Controls::Border validationBorder{nullptr};
        rtxaml::UIElement textInputControl{nullptr};

        std::tie(textInputControl, validationBorder) =
            HandleLayoutAndValidation(adaptiveTextInput, textBox, renderContext, renderArgs);

        // TODO: come back here, not sure if this is correct?
        auto inputValue = winrt::make_self<rtrender::TextInputValue>(adaptiveTextInput, textBox, validationBorder);
        renderContext.AddInputValue(*inputValue, renderArgs);

        ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Text", textBox);
        return textInputControl;
    }

    rtxaml::UIElement AdaptiveTextInputRenderer::RenderPasswordBox(rtom::AdaptiveTextInput const& adaptiveTextInput,
                                                                   rtrender::AdaptiveRenderContext const& renderContext,
                                                                   rtrender::AdaptiveRenderArgs const& renderArgs)
    { /*
         ComPtr<IPasswordBox> passwordBox =
             XamlHelpers::CreateABIClass<IPasswordBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_PasswordBox));*/
        rtxaml::Controls::PasswordBox passwordBox{};

        /*  HString textValue;
          RETURN_IF_FAILED(adaptiveTextInput->get_Value(textValue.GetAddressOf()));
          RETURN_IF_FAILED(passwordBox->put_Password(textValue.Get()));

          UINT32 maxLength;
          RETURN_IF_FAILED(adaptiveTextInput->get_MaxLength(&maxLength));
          RETURN_IF_FAILED(passwordBox->put_MaxLength(maxLength));*/
        passwordBox.Password(adaptiveTextInput.Value());
        passwordBox.MaxLength(adaptiveTextInput.MaxLength());

        /* ComPtr<IPasswordBox2> passwordBox2;
         RETURN_IF_FAILED(passwordBox.As(&passwordBox2));

         HString placeHolderText;
         RETURN_IF_FAILED(adaptiveTextInput->get_Placeholder(placeHolderText.GetAddressOf()));
         RETURN_IF_FAILED(passwordBox2->put_PlaceholderText(placeHolderText.Get()));*/
        passwordBox.PlaceholderText(adaptiveTextInput.Placeholder());

        /*ComPtr<IUIElement> textBoxAsUIElement;
        RETURN_IF_FAILED(passwordBox.As(&textBoxAsUIElement));

        ComPtr<IBorder> validationBorder;
        RETURN_IF_FAILED(HandleLayoutAndValidation(
            adaptiveTextInput, textBoxAsUIElement.Get(), renderContext, renderArgs, textInputControl, &validationBorder));*/

        rtxaml::Controls::Border validationBorder{nullptr};
        rtxaml::UIElement textInputControl{nullptr};

        std::tie(textInputControl, validationBorder) =
            HandleLayoutAndValidation(adaptiveTextInput, passwordBox, renderContext, renderArgs);

        /* ComPtr<PasswordInputValue> inputValue;
         RETURN_IF_FAILED(
             MakeAndInitialize<PasswordInputValue>(&inputValue, adaptiveTextInput, passwordBox.Get(),
         validationBorder.Get())); RETURN_IF_FAILED(renderContext->AddInputValue(inputValue.Get(), renderArgs));*/
        // TODO: come back to inputs, not sure if it's correct
        auto inputValue = winrt::make_self<rtrender::PasswordInputValue>(adaptiveTextInput, passwordBox, validationBorder);
        renderContext.AddInputValue(*inputValue, renderArgs);

        return textInputControl;
    }

    rtxaml::UIElement AdaptiveTextInputRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                        rtrender::AdaptiveRenderContext const& renderContext,
                                                        rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            /*ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));*/
            auto hostConfig = renderContext.HostConfig();
            if (!::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                         L"Text Input was stripped from card because interactivity is not supported");
                return nullptr;
            }

            /*  ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
              ComPtr<IAdaptiveTextInput> adaptiveTextInput;
              RETURN_IF_FAILED(cardElement.As(&adaptiveTextInput));

              ABI::AdaptiveCards::ObjectModel::WinUI3::TextInputStyle textInputStyle;
              RETURN_IF_FAILED(adaptiveTextInput->get_TextInputStyle(&textInputStyle));

              ComPtr<IUIElement> renderedTextInputControl;*/
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

            /*RETURN_IF_FAILED(renderedTextInputControl.CopyTo(textInputControl));

            return S_OK;*/
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
