// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveOpenUrlAction.h"
#include "AdaptiveOpenUrlActionRenderer.h"
#include "Util.h"
#include "AdaptiveElementParserRegistration.h"
#include "ActionHelpers.h"

using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace Microsoft::WRL;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveOpenUrlActionRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveOpenUrlActionRenderer::Render(_In_ IAdaptiveActionElement* action,
                                                  _In_ IAdaptiveRenderContext* renderContext,
                                                  _In_ IAdaptiveRenderArgs* renderArgs,
                                                  _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept
    try
    {
        return ActionHelpers::BuildAction(action, renderContext, renderArgs, result);
    }
    CATCH_RETURN;

    HRESULT AdaptiveOpenUrlActionRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement** element) noexcept
    try
    {
        return AdaptiveCards::Rendering::Uwp::FromJson<AdaptiveCards::Rendering::Uwp::AdaptiveOpenUrlAction, AdaptiveCards::OpenUrlAction, AdaptiveCards::OpenUrlActionParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
