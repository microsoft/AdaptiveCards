// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextInputRenderer.h"
#include "ActionHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Input;

namespace AdaptiveCards::Rendering::Uwp
{
HRESULT AdaptiveTextInputRenderer::RuntimeClassInitialize() noexcept
try
{
    return S_OK;
}
CATCH_RETURN;

HRESULT AdaptiveTextInputRenderer::HandleLayoutAndValidation(
    IAdaptiveTextInput* adaptiveTextInput,
    IUIElement* inputUIElement,
    _In_ IAdaptiveRenderContext* renderContext,
    _In_ IAdaptiveRenderArgs* renderArgs,
    IUIElement** textInputLayout,
    IBorder** validationBorderOut)
{
    // The text box may need to go into a number of parent containers to handle validation and inline actions.
    // textBoxParentContainer represents the current parent container.
    ComPtr<IUIElement> textBoxParentContainer = inputUIElement;

    // If there's any validation on this input, put the input inside a border. We don't use
    // XamlHelpers::HandleInputLayoutAndValidation validation border because that would wrap any inline action as
    // well as the text input, which is not the desired behavior.
    ComPtr<IAdaptiveTextInput> localTextInput(adaptiveTextInput);
    ComPtr<IAdaptiveInputElement> textInputAsAdaptiveInput;
    RETURN_IF_FAILED(localTextInput.As(&textInputAsAdaptiveInput));

    HString regex;
    RETURN_IF_FAILED(adaptiveTextInput->get_Regex(regex.GetAddressOf()));
    boolean isRequired;
    RETURN_IF_FAILED(textInputAsAdaptiveInput->get_IsRequired(&isRequired));

    ComPtr<IBorder> validationBorder;
    if (regex.IsValid() || isRequired)
    {
        RETURN_IF_FAILED(XamlHelpers::CreateValidationBorder(inputUIElement, renderContext, &validationBorder));
        RETURN_IF_FAILED(validationBorder.As(&textBoxParentContainer));
    }

    // If this input has an inline action, render it next to the input
    ComPtr<IAdaptiveActionElement> inlineAction;
    RETURN_IF_FAILED(adaptiveTextInput->get_InlineAction(&inlineAction));

    if (inlineAction != nullptr)
    {
        boolean isMultiline;
        RETURN_IF_FAILED(adaptiveTextInput->get_IsMultiline(&isMultiline));

        ABI::AdaptiveCards::ObjectModel::Uwp::TextInputStyle style;
        RETURN_IF_FAILED(adaptiveTextInput->get_TextInputStyle(&style));

        isMultiline &= style != (ABI::AdaptiveCards::ObjectModel::Uwp::TextInputStyle::Password);

        ComPtr<IUIElement> textBoxWithInlineAction;
        ActionHelpers::HandleInlineAction(
            renderContext, renderArgs, inputUIElement, textBoxParentContainer.Get(), isMultiline, inlineAction.Get(), &textBoxWithInlineAction);
        textBoxParentContainer = textBoxWithInlineAction;
    }

    boolean isMultiline;
    RETURN_IF_FAILED(adaptiveTextInput->get_IsMultiline(&isMultiline));

    if (!isMultiline)
    {
        ComPtr<IFrameworkElement> textBoxFrameworkElement;
        RETURN_IF_FAILED(textBoxParentContainer.As(&textBoxFrameworkElement));
        RETURN_IF_FAILED(textBoxFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
    }

    // Call XamlHelpers::HandleInputLayoutAndValidation to handle accessibility properties. Pass nullptr for
    // validationBorder as we've already handled that above.
    ComPtr<IUIElement> inputLayout;
    ComPtr<IUIElement> validationError;
    RETURN_IF_FAILED(XamlHelpers::HandleInputLayoutAndValidation(
        textInputAsAdaptiveInput.Get(), textBoxParentContainer.Get(), regex.IsValid(), renderContext, &inputLayout, nullptr));

    RETURN_IF_FAILED(inputLayout.CopyTo(textInputLayout));
    RETURN_IF_FAILED(validationBorder.CopyTo(validationBorderOut));
    return S_OK;
}

HRESULT AdaptiveTextInputRenderer::RenderTextBox(
    _In_ IAdaptiveTextInput* adaptiveTextInput,
    _In_ IAdaptiveRenderContext* renderContext,
    _In_ IAdaptiveRenderArgs* renderArgs,
    _COM_Outptr_ IUIElement** textInputControl)
{
    ComPtr<ITextBox> textBox =
        XamlHelpers::CreateABIClass<ITextBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBox));

    boolean isMultiLine;
    RETURN_IF_FAILED(adaptiveTextInput->get_IsMultiline(&isMultiLine));
    if (isMultiLine)
    {
        RETURN_IF_FAILED(textBox->put_AcceptsReturn(true));
        RETURN_IF_FAILED(textBox->put_TextWrapping(TextWrapping_Wrap));
    }

    HString textValue;
    RETURN_IF_FAILED(adaptiveTextInput->get_Value(textValue.GetAddressOf()));
    RETURN_IF_FAILED(textBox->put_Text(textValue.Get()));

    UINT32 maxLength;
    RETURN_IF_FAILED(adaptiveTextInput->get_MaxLength(&maxLength));
    RETURN_IF_FAILED(textBox->put_MaxLength(maxLength));

    ComPtr<ITextBox2> textBox2;
    RETURN_IF_FAILED(textBox.As(&textBox2));

    HString placeHolderText;
    RETURN_IF_FAILED(adaptiveTextInput->get_Placeholder(placeHolderText.GetAddressOf()));
    RETURN_IF_FAILED(textBox2->put_PlaceholderText(placeHolderText.Get()));

    ABI::AdaptiveCards::ObjectModel::Uwp::TextInputStyle textInputStyle;
    RETURN_IF_FAILED(adaptiveTextInput->get_TextInputStyle(&textInputStyle));

    ComPtr<IInputScopeName> inputScopeName =
        XamlHelpers::CreateABIClass<IInputScopeName>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScopeName));
    switch (textInputStyle)
    {
    case ABI::AdaptiveCards::ObjectModel::Uwp::TextInputStyle::Email:
        RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_EmailSmtpAddress));
        break;

    case ABI::AdaptiveCards::ObjectModel::Uwp::TextInputStyle::Tel:
        RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_TelephoneNumber));
        break;

    case ABI::AdaptiveCards::ObjectModel::Uwp::TextInputStyle::Url:
        RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_Url));
        break;
    }

    ComPtr<IInputScope> inputScope =
        XamlHelpers::CreateABIClass<IInputScope>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScope));
    ComPtr<IVector<InputScopeName*>> names;
    RETURN_IF_FAILED(inputScope->get_Names(names.GetAddressOf()));
    RETURN_IF_FAILED(names->Append(inputScopeName.Get()));

    RETURN_IF_FAILED(textBox->put_InputScope(inputScope.Get()));

    ComPtr<IUIElement> textBoxAsUIElement;
    RETURN_IF_FAILED(textBox.As(&textBoxAsUIElement));

    ComPtr<IBorder> validationBorder;
    RETURN_IF_FAILED(HandleLayoutAndValidation(
        adaptiveTextInput, textBoxAsUIElement.Get(), renderContext, renderArgs, textInputControl, &validationBorder));

    ComPtr<TextInputValue> inputValue;
    RETURN_IF_FAILED(MakeAndInitialize<TextInputValue>(&inputValue, adaptiveTextInput, textBox.Get(), validationBorder.Get()));
    RETURN_IF_FAILED(renderContext->AddInputValue(inputValue.Get(), renderArgs));

    ComPtr<IFrameworkElement> textBoxAsFrameworkElement;
    RETURN_IF_FAILED(textBox.As(&textBoxAsFrameworkElement));
    RETURN_IF_FAILED(
        XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Text", textBoxAsFrameworkElement.Get()));

    return S_OK;
}

HRESULT AdaptiveTextInputRenderer::RenderPasswordBox(
    _In_ IAdaptiveTextInput* adaptiveTextInput,
    _In_ IAdaptiveRenderContext* renderContext,
    _In_ IAdaptiveRenderArgs* renderArgs,
    _COM_Outptr_ IUIElement** textInputControl)
{
    ComPtr<IPasswordBox> passwordBox =
        XamlHelpers::CreateABIClass<IPasswordBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_PasswordBox));

    HString textValue;
    RETURN_IF_FAILED(adaptiveTextInput->get_Value(textValue.GetAddressOf()));
    RETURN_IF_FAILED(passwordBox->put_Password(textValue.Get()));

    UINT32 maxLength;
    RETURN_IF_FAILED(adaptiveTextInput->get_MaxLength(&maxLength));
    RETURN_IF_FAILED(passwordBox->put_MaxLength(maxLength));

    ComPtr<IPasswordBox2> passwordBox2;
    RETURN_IF_FAILED(passwordBox.As(&passwordBox2));

    HString placeHolderText;
    RETURN_IF_FAILED(adaptiveTextInput->get_Placeholder(placeHolderText.GetAddressOf()));
    RETURN_IF_FAILED(passwordBox2->put_PlaceholderText(placeHolderText.Get()));

    ComPtr<IUIElement> textBoxAsUIElement;
    RETURN_IF_FAILED(passwordBox.As(&textBoxAsUIElement));

    ComPtr<IBorder> validationBorder;
    RETURN_IF_FAILED(HandleLayoutAndValidation(
        adaptiveTextInput, textBoxAsUIElement.Get(), renderContext, renderArgs, textInputControl, &validationBorder));

    ComPtr<PasswordInputValue> inputValue;
    RETURN_IF_FAILED(
        MakeAndInitialize<PasswordInputValue>(&inputValue, adaptiveTextInput, passwordBox.Get(), validationBorder.Get()));
    RETURN_IF_FAILED(renderContext->AddInputValue(inputValue.Get(), renderArgs));

    return S_OK;
}

HRESULT AdaptiveTextInputRenderer::Render(
    _In_ IAdaptiveCardElement* adaptiveCardElement,
    _In_ IAdaptiveRenderContext* renderContext,
    _In_ IAdaptiveRenderArgs* renderArgs,
    _COM_Outptr_ IUIElement** textInputControl) noexcept
try
{
    ComPtr<IAdaptiveHostConfig> hostConfig;
    RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
    if (!XamlHelpers::SupportsInteractivity(hostConfig.Get()))
    {
        renderContext->AddWarning(
            ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::InteractivityNotSupported,
            HStringReference(L"Text Input was stripped from card because interactivity is not supported").Get());
        return S_OK;
    }

    ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
    ComPtr<IAdaptiveTextInput> adaptiveTextInput;
    RETURN_IF_FAILED(cardElement.As(&adaptiveTextInput));

    ABI::AdaptiveCards::ObjectModel::Uwp::TextInputStyle textInputStyle;
    RETURN_IF_FAILED(adaptiveTextInput->get_TextInputStyle(&textInputStyle));

    ComPtr<IUIElement> renderedTextInputControl;
    if (textInputStyle == ABI::AdaptiveCards::ObjectModel::Uwp::TextInputStyle::Password)
    {
        RenderPasswordBox(adaptiveTextInput.Get(), renderContext, renderArgs, &renderedTextInputControl);
    }
    else
    {
        RenderTextBox(adaptiveTextInput.Get(), renderContext, renderArgs, &renderedTextInputControl);
    }

    RETURN_IF_FAILED(renderedTextInputControl.CopyTo(textInputControl));

    return S_OK;
}
CATCH_RETURN;
} // namespace AdaptiveCards::Rendering::Uwp
