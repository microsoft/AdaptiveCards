// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveToggleInput.h"
#include "AdaptiveToggleInputRenderer.h"
#include "enums.h"
#include "Util.h"
#include "XamlBuilder.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveToggleInputRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveToggleInputRenderer::Render(_In_ IAdaptiveCardElement* cardElement,
                                                _In_ IAdaptiveRenderContext* renderContext,
                                                _In_ IAdaptiveRenderArgs* renderArgs,
                                                _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept try
    {
        return XamlBuilder::BuildToggleInput(cardElement, renderContext, renderArgs, result);
    }
    CATCH_RETURN;

    HRESULT AdaptiveToggleInputRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveToggleInput, AdaptiveSharedNamespace::ToggleInput, AdaptiveSharedNamespace::ToggleInputParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
