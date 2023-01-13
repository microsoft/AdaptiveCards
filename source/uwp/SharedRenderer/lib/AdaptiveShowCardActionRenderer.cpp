// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveShowCardActionRenderer.h"
#include "AdaptiveShowCardActionRenderer.g.cpp"
#include "ActionHelpers.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::UIElement AdaptiveShowCardActionRenderer::Render(winrt::IAdaptiveActionElement const& action,
                                                            winrt::AdaptiveRenderContext const& renderContext,
                                                            winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            return ::AdaptiveCards::Rendering::Xaml_Rendering::ActionHelpers::BuildAction(action, renderContext, renderArgs, false);
        }
        catch (winrt::hresult_error const& ex)
        {
            XamlHelpers::ErrForRenderFailedForElement(renderContext, action.ActionTypeString(), ex.message());
            return nullptr;
        }
    }
    winrt::UIElement AdaptiveShowCardActionRenderer::BuildShowCard(winrt::AdaptiveCard const& showCard,
                                                                   winrt::AdaptiveRenderContext const& renderContext,
                                                                   winrt::AdaptiveRenderArgs const& renderArgs,
                                                                   bool isBottomActionBar)
    {
        try
        {
            auto hostConfig = renderContext.HostConfig();
            auto actionsConfig = hostConfig.Actions();
            auto showCardActionConfig = actionsConfig.ShowCard();
            auto showCardConfigStyle = showCardActionConfig.Style();

            bool wasInShowCard = renderArgs.IsInShowCard();
            renderArgs.IsInShowCard(true);
            renderContext.LinkCardToParent(showCard, renderArgs);

            auto localUiShowCard =
                ::AdaptiveCards::Rendering::Xaml_Rendering::XamlBuilder::BuildXamlTreeFromAdaptiveCard(showCard, renderContext, nullptr, showCardConfigStyle);
            renderArgs.IsInShowCard(wasInShowCard);

            // Set the padding
            auto spacingConfig = hostConfig.Spacing();
            uint32_t padding = spacingConfig.Padding();

            // Set the top margin
            uint32_t inlineTopMargin = showCardActionConfig.InlineTopMargin();

            const double negativePadding = -(static_cast<double>(padding));
            const double sideMargin = negativePadding;
            const double topMargin = isBottomActionBar ? inlineTopMargin + padding : inlineTopMargin;
            const double bottomMargin = negativePadding;

            localUiShowCard.Margin({sideMargin, topMargin, sideMargin, bottomMargin});

            // Set the visibility as Collapsed until the action is triggered
            localUiShowCard.Visibility(winrt::Visibility::Collapsed);

            return localUiShowCard;
        }
        catch (winrt::hresult_error const& ex)
        {
            renderContext.AddError(winrt::ErrorStatusCode::CustomError,
                                   L"Show Card building failed with the following message:\n" + ex.message());
            return nullptr;
        }
    }
}
