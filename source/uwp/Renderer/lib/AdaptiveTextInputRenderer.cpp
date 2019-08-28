// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveTextInput.h"
#include "AdaptiveTextInputRenderer.h"
#include "ActionHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Input;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveTextInputRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextInputRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                              _In_ IAdaptiveRenderContext* renderContext,
                                              _In_ IAdaptiveRenderArgs* renderArgs,
                                              _COM_Outptr_ IUIElement** textInputControl) noexcept try
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!XamlHelpers::SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Text Input was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTextInput> adaptiveTextInput;
        RETURN_IF_FAILED(cardElement.As(&adaptiveTextInput));

        ComPtr<ITextBox> textBox =
            XamlHelpers::CreateXamlClass<ITextBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBox));

        boolean isMultiLine;
        RETURN_IF_FAILED(adaptiveTextInput->get_IsMultiline(&isMultiLine));
        RETURN_IF_FAILED(textBox->put_AcceptsReturn(isMultiLine));

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

        ABI::AdaptiveNamespace::TextInputStyle textInputStyle;
        RETURN_IF_FAILED(adaptiveTextInput->get_TextInputStyle(&textInputStyle));

        ComPtr<IInputScopeName> inputScopeName =
            XamlHelpers::CreateXamlClass<IInputScopeName>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScopeName));
        switch (textInputStyle)
        {
        case ABI::AdaptiveNamespace::TextInputStyle::Email:
            RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_EmailSmtpAddress));
            break;

        case ABI::AdaptiveNamespace::TextInputStyle::Tel:
            RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_TelephoneNumber));
            break;

        case ABI::AdaptiveNamespace::TextInputStyle::Url:
            RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_Url));
            break;
        }

        ComPtr<IInputScope> inputScope =
            XamlHelpers::CreateXamlClass<IInputScope>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScope));
        ComPtr<IVector<InputScopeName*>> names;
        RETURN_IF_FAILED(inputScope->get_Names(names.GetAddressOf()));
        RETURN_IF_FAILED(names->Append(inputScopeName.Get()));

        RETURN_IF_FAILED(textBox->put_InputScope(inputScope.Get()));

        ComPtr<IUIElement> textBoxAsUIElement;
        textBox.As(&textBoxAsUIElement);
        XamlHelpers::AddInputValueToContext(renderContext, adaptiveCardElement, textBoxAsUIElement.Get());

        ComPtr<IAdaptiveActionElement> inlineAction;
        RETURN_IF_FAILED(adaptiveTextInput->get_InlineAction(&inlineAction));

        ComPtr<IFrameworkElement> textBoxAsFrameworkElement;
        RETURN_IF_FAILED(textBox.As(&textBoxAsFrameworkElement));
        RETURN_IF_FAILED(
            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Text", textBoxAsFrameworkElement.Get()));

        if (inlineAction != nullptr)
        {
            ComPtr<IUIElement> textBoxWithInlineAction;
            ActionHelpers::HandleInlineAction(renderContext, renderArgs, textBox.Get(), inlineAction.Get(), &textBoxWithInlineAction);
            if (!isMultiLine)
            {
                RETURN_IF_FAILED(textBoxWithInlineAction.As(&textBoxAsFrameworkElement));
                RETURN_IF_FAILED(textBoxAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
            }

            RETURN_IF_FAILED(textBoxWithInlineAction.CopyTo(textInputControl));
        }
        else
        {
            if (!isMultiLine)
            {
                RETURN_IF_FAILED(textBoxAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
            }

            RETURN_IF_FAILED(textBox.CopyTo(textInputControl));
        }
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextInputRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveTextInput, AdaptiveSharedNamespace::TextInput, AdaptiveSharedNamespace::TextInputParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
