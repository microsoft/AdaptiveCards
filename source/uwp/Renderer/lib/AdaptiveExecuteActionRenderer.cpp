// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveExecuteActionRenderer.h"
#include "AdaptiveExecuteActionRenderer.g.cpp"
#include "ActionHelpers.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    rtxaml::UIElement AdaptiveExecuteActionRenderer::Render(winrt::IAdaptiveActionElement const& action,
                                                            winrt::AdaptiveRenderContext const& renderContext,
                                                            winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            // TODO: do we need to check for errors here? or catch -> nullptr should be enough
            renderContext.LinkSubmitActionToCard(action, renderArgs);
            return ::AdaptiveCards::Rendering::Uwp::ActionHelpers::BuildAction(action, renderContext, renderArgs, false);
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: restore treat warnings as errrors
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
