// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveActionSetRenderer.h"
#include "AdaptiveActionSetRenderer.g.cpp"

#include "ActionHelpers.h"
#include "AdaptiveRenderArgs.h"

using namespace winrt;
using namespace winrt::AdaptiveCards::Rendering::Uwp;
using namespace winrt::AdaptiveCards::ObjectModel::Uwp;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Controls::Primitives;

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    winrt::Windows::UI::Xaml::UIElement AdaptiveActionSetRenderer::Render(ObjectModel::Uwp::IAdaptiveCardElement const& cardElement,
                                                                          Uwp::AdaptiveRenderContext const& renderContext,
                                                                          Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();

            if (!::AdaptiveCards::Rendering::Uwp::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(ObjectModel::Uwp::WarningStatusCode::InteractivityNotSupported,
                                         L"ActionSet was stripped from card because interactivity is not supported");

                return nullptr;
            }
            else
            {
                auto adaptiveActionSet = cardElement.as<ObjectModel::Uwp::AdaptiveActionSet>();
                auto actions = adaptiveActionSet.Actions();

                return ::AdaptiveCards::Rendering::Uwp::ActionHelpers::BuildActionSetHelper(
                    nullptr, adaptiveActionSet, actions, renderContext, renderArgs);
            }
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
