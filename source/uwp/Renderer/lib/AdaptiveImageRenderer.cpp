// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveImage.h"
#include "AdaptiveImageRenderer.h"
#include "enums.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;

namespace AdaptiveNamespace
{
    AdaptiveImageRenderer::AdaptiveImageRenderer() {}

    AdaptiveImageRenderer::AdaptiveImageRenderer(ComPtr<XamlBuilder> xamlBuilder) : m_xamlBuilder(xamlBuilder)
    {
    }

    HRESULT AdaptiveImageRenderer::RuntimeClassInitialize() noexcept try
    {
        RETURN_IF_FAILED(MakeAndInitialize<XamlBuilder>(&m_xamlBuilder));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveImageRenderer::Render(_In_ IAdaptiveCardElement* cardElement,
                                          _In_ IAdaptiveRenderContext* renderContext,
                                          _In_ IAdaptiveRenderArgs* renderArgs,
                                          _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept try
    {
        return m_xamlBuilder->BuildImage(cardElement, renderContext, renderArgs, result);
    }
    CATCH_RETURN;

    HRESULT AdaptiveImageRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveImage, AdaptiveSharedNamespace::Image, AdaptiveSharedNamespace::ImageParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
