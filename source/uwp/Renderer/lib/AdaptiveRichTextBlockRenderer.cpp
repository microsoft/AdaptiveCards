// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRichTextBlock.h"
#include "AdaptiveRichTextBlockRenderer.h"
#include "AdaptiveRenderContext.h"
#include "Util.h"
#include "XamlBuilder.h"
#include "AdaptiveElementParserRegistration.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveRichTextBlockRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveRichTextBlockRenderer::Render(_In_ IAdaptiveCardElement* cardElement,
                                                  _In_ IAdaptiveRenderContext* renderContext,
                                                  _In_ IAdaptiveRenderArgs* renderArgs,
                                                  _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept try
    {
        XamlBuilder::BuildRichTextBlock(cardElement, renderContext, renderArgs, result);
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveRichTextBlockRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveRichTextBlock, AdaptiveSharedNamespace::RichTextBlock, AdaptiveSharedNamespace::RichTextBlockParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
