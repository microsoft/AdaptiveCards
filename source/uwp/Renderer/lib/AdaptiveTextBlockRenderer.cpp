// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextBlock.h"
#include "AdaptiveTextBlockRenderer.h"
#include "AdaptiveRenderContext.h"
#include "AdaptiveElementParserRegistration.h"
#include "TextHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveTextBlockRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextBlockRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                              _In_ IAdaptiveRenderContext* renderContext,
                                              _In_ IAdaptiveRenderArgs* renderArgs,
                                              _COM_Outptr_ IUIElement** textBlockControl) noexcept
    try
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTextBlock> adaptiveTextBlock;
        RETURN_IF_FAILED(cardElement.As(&adaptiveTextBlock));

        ComPtr<IAdaptiveTextElement> textBlockAsTextElement;
        RETURN_IF_FAILED(adaptiveTextBlock.As(&textBlockAsTextElement));
        HString text;
        RETURN_IF_FAILED(textBlockAsTextElement->get_Text(text.ReleaseAndGetAddressOf()));

        // If the text is null, return immediately without constructing a text block
        if (text.Get() == nullptr)
        {
            *textBlockControl = nullptr;
            renderContext->AddError(ABI::AdaptiveNamespace::ErrorStatusCode::RequiredPropertyMissing,
                                      HStringReference(L"Required property, \"text\", is missing from TextBlock").Get());
            return S_OK;
        }

        ComPtr<ITextBlock> xamlTextBlock =
            XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));

        ComPtr<IAdaptiveTextElement> adaptiveTextElement;
        RETURN_IF_FAILED(adaptiveTextBlock.As(&adaptiveTextElement));

        RETURN_IF_FAILED(StyleXamlTextBlockProperties(adaptiveTextBlock.Get(), renderContext, renderArgs, xamlTextBlock.Get()));

        ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> inlines;
        RETURN_IF_FAILED(xamlTextBlock->get_Inlines(&inlines));

        RETURN_IF_FAILED(SetXamlInlines(adaptiveTextElement.Get(), renderContext, renderArgs, false, inlines.Get()));

        // Ensure left edge of text is consistent regardless of font size, so both small and large fonts
        // are flush on the left edge of the card by enabling TrimSideBearings
        ComPtr<ITextBlock2> xamlTextBlock2;
        RETURN_IF_FAILED(xamlTextBlock.As(&xamlTextBlock2));
        RETURN_IF_FAILED(xamlTextBlock2->put_OpticalMarginAlignment(OpticalMarginAlignment_TrimSideBearings));

        ComPtr<IFrameworkElement> frameworkElement;
        RETURN_IF_FAILED(xamlTextBlock.As(&frameworkElement));
        RETURN_IF_FAILED(
            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.TextBlock", frameworkElement.Get()));

        return xamlTextBlock.CopyTo(textBlockControl);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextBlockRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept
    try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveTextBlock, AdaptiveSharedNamespace::TextBlock, AdaptiveSharedNamespace::TextBlockParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
