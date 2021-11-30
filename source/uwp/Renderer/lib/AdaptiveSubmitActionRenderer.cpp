// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveSubmitActionRenderer.h"
#include "AdaptiveSubmitActionRenderer.g.cpp"
#include "ActionHelpers.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    rtxaml::UIElement AdaptiveSubmitActionRenderer::Render(rtom::IAdaptiveActionElement const& action,
                                                           rtrender::AdaptiveRenderContext const& renderContext,
                                                           rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            renderContext.LinkSubmitActionToCard(action, renderArgs);
            return ::AdaptiveCards::Rendering::Uwp::ActionHelpers::BuildAction(action, renderContext, renderArgs, false);
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
