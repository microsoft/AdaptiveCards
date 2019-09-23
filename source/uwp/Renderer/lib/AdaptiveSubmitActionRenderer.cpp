// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveSubmitAction.h"
#include "AdaptiveSubmitActionRenderer.h"
#include "AdaptiveElementParserRegistration.h"
#include "ActionHelpers.h"

using namespace ABI::AdaptiveNamespace;
using namespace Microsoft::WRL;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveSubmitActionRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveSubmitActionRenderer::Render(_In_ IAdaptiveActionElement* action,
                                                 _In_ IAdaptiveRenderContext* renderContext,
                                                 _In_ IAdaptiveRenderArgs* renderArgs,
                                                 _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept
    try
    {
        return ActionHelpers::BuildAction(action, renderContext, renderArgs, result);
    }
    CATCH_RETURN;

    HRESULT AdaptiveSubmitActionRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** element) noexcept
    try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveSubmitAction, AdaptiveSharedNamespace::SubmitAction, AdaptiveSharedNamespace::SubmitActionParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
