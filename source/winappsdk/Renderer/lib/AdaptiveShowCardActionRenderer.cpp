// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveShowCardActionRenderer.h"
#include "ActionHelpers.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    rtxaml::UIElement AdaptiveShowCardActionRenderer::Render(rtom::IAdaptiveActionElement const& action,
                             rtrender::AdaptiveRenderContext const& renderContext,
                             rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            return ::AdaptiveCards::Rendering::WinUI3::ActionHelpers::BuildAction(action, renderContext, renderArgs, false);
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }

    static winrt::Windows::UI::Xaml::UIElement BuildShowCard(rtom::AdaptiveCard const& showCard,
                                                             rtrender::AdaptiveRenderContext const& renderContext,
                                                             rtrender::AdaptiveRenderArgs const& renderArgs,
                                                             bool isBottomActionBar)
    {
        try
        {
            /*ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

            ComPtr<IAdaptiveActionsConfig> actionsConfig;
            RETURN_IF_FAILED(hostConfig->get_Actions(&actionsConfig));

            ComPtr<IAdaptiveShowCardActionConfig> showCardActionConfig;
            RETURN_IF_FAILED(actionsConfig->get_ShowCard(&showCardActionConfig));

            ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle showCardConfigStyle;
            RETURN_IF_FAILED(showCardActionConfig->get_Style(&showCardConfigStyle));*/
            auto hostConfig = renderContext.HostConfig();
            auto actionsConfig = hostConfig.Actions();
            auto showCardActionConfig = actionsConfig.ShowCard();
            auto showCardConfigStyle = showCardActionConfig.Style();

         /*   boolean wasInShowCard;
            RETURN_IF_FAILED(renderArgs->get_IsInShowCard(&wasInShowCard));
            RETURN_IF_FAILED(renderArgs->put_IsInShowCard(true));

            RETURN_IF_FAILED(renderContext->LinkCardToParent(showCard, renderArgs));*/

            bool wasInShowCard = renderArgs.IsInShowCard();
            renderArgs.IsInShowCard(true);
            renderContext.LinkCardToParent(showCard, renderArgs);

            /*ComPtr<IFrameworkElement> localUiShowCard;
            RETURN_IF_FAILED(XamlBuilder::BuildXamlTreeFromAdaptiveCard(
                showCard, localUiShowCard.GetAddressOf(), renderContext, nullptr, showCardConfigStyle));

            RETURN_IF_FAILED(renderArgs->put_IsInShowCard(wasInShowCard));

            ComPtr<IGrid2> showCardGrid;
            RETURN_IF_FAILED(localUiShowCard.As(&showCardGrid));*/

            // TODO: implement BuildXamlTreeFromAdaptiveCard
            auto localUiShowCard = ::AdaptiveCards::Rendering::WinUI3::XamlBuilder::BuildXamlTreeFromAdaptiveCard(showCard, renderContext, nullptr, showCardConfigStyle);
            renderArgs.IsInShowCard(wasInShowCard);

            // Set the padding
            /*ComPtr<IAdaptiveSpacingConfig> spacingConfig;
            RETURN_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

            UINT32 padding;
            RETURN_IF_FAILED(spacingConfig->get_Padding(&padding));

            ABI::AdaptiveCards::Rendering::WinUI3::ActionMode showCardActionMode;
            RETURN_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));*/
            auto spacingConfig = hostConfig.Spacing();
            uint32_t padding = spacingConfig.Padding();

            rtrender::ActionMode showCardActionmode = showCardActionConfig.ActionMode();

            // Set the top margin
           /* ComPtr<IFrameworkElement> showCardFrameworkElement;
            RETURN_IF_FAILED(localUiShowCard.As(&showCardFrameworkElement));

            UINT32 inlineTopMargin;
            RETURN_IF_FAILED(showCardActionConfig->get_InlineTopMargin(&inlineTopMargin));*/

            uint32_t inlineTopMargin = showCardActionConfig.InlineTopMargin();

            const double negativePadding = -(static_cast<double>(padding));
            const double sideMargin = negativePadding;
            const double topMargin = isBottomActionBar ? inlineTopMargin + padding : inlineTopMargin;
            const double bottomMargin = negativePadding;

            rtxaml::Thickness margin = {sideMargin, topMargin, sideMargin, bottomMargin};
           /* RETURN_IF_FAILED(showCardFrameworkElement->put_Margin(margin));*/
            localUiShowCard.Margin(margin);

            /*ComPtr<IUIElement> showCardUIElement;
            RETURN_IF_FAILED(localUiShowCard.As(&showCardUIElement));*/

            // Set the visibility as Collapsed until the action is triggered
            /*RETURN_IF_FAILED(showCardUIElement->put_Visibility(Visibility_Collapsed));*/
            localUiShowCard.Visibility(rtxaml::Visibility::Collapsed);

            //*uiShowCard = showCardUIElement.Detach();
            //return S_OK;
            return localUiShowCard;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
