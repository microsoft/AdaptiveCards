// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveSubmitActionRenderer.h"
#include "ActionHelpers.h"

using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace Microsoft::WRL;

namespace AdaptiveCards::Rendering::WinUI3
{
    HRESULT AdaptiveSubmitActionRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN();

    HRESULT AdaptiveSubmitActionRenderer::Render(_In_ IAdaptiveActionElement* action,
                                                 _In_ IAdaptiveRenderContext* renderContext,
                                                 _In_ IAdaptiveRenderArgs* renderArgs,
                                                 _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept
    try
    {
        RETURN_IF_FAILED(renderContext->LinkSubmitActionToCard(action, renderArgs));
        return ActionHelpers::BuildAction(action, renderContext, renderArgs, false, result);
    }
    CATCH_RETURN();
}
