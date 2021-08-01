// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveShowCardActionRenderer.h"
#include "ActionHelpers.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveShowCardActionRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveShowCardActionRenderer::Render(_In_ IAdaptiveActionElement* action,
                                                   _In_ IAdaptiveRenderContext* renderContext,
                                                   _In_ IAdaptiveRenderArgs* renderArgs,
                                                   _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept
    try
    {
        return ActionHelpers::BuildAction(action, renderContext, renderArgs, result);
    }
    CATCH_RETURN;

    HRESULT AdaptiveShowCardActionRenderer::BuildShowCard(_In_ IAdaptiveCard* showCard,
                                                          _In_ IAdaptiveRenderContext* renderContext,
                                                          _In_ IAdaptiveRenderArgs* renderArgs,
                                                          bool isBottomActionBar,
                                                          _Outptr_ IUIElement** uiShowCard) noexcept
    try
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ComPtr<IAdaptiveActionsConfig> actionsConfig;
        RETURN_IF_FAILED(hostConfig->get_Actions(&actionsConfig));

        ComPtr<IAdaptiveShowCardActionConfig> showCardActionConfig;
        RETURN_IF_FAILED(actionsConfig->get_ShowCard(&showCardActionConfig));

        ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle showCardConfigStyle;
        RETURN_IF_FAILED(showCardActionConfig->get_Style(&showCardConfigStyle));

        boolean wasInShowCard;
        RETURN_IF_FAILED(renderArgs->get_IsInShowCard(&wasInShowCard));
        RETURN_IF_FAILED(renderArgs->put_IsInShowCard(true));

        RETURN_IF_FAILED(renderContext->LinkCardToParent(showCard, renderArgs));

        ComPtr<IFrameworkElement> localUiShowCard;
        RETURN_IF_FAILED(
            XamlBuilder::BuildXamlTreeFromAdaptiveCard(showCard, localUiShowCard.GetAddressOf(), renderContext, nullptr, showCardConfigStyle));

        RETURN_IF_FAILED(renderArgs->put_IsInShowCard(wasInShowCard));

        ComPtr<IGrid2> showCardGrid;
        RETURN_IF_FAILED(localUiShowCard.As(&showCardGrid));

        // Set the padding
        ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        RETURN_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

        UINT32 padding;
        RETURN_IF_FAILED(spacingConfig->get_Padding(&padding));

        ABI::AdaptiveCards::Rendering::Uwp::ActionMode showCardActionMode;
        RETURN_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));

        // Set the top margin
        ComPtr<IFrameworkElement> showCardFrameworkElement;
        RETURN_IF_FAILED(localUiShowCard.As(&showCardFrameworkElement));

        UINT32 inlineTopMargin;
        RETURN_IF_FAILED(showCardActionConfig->get_InlineTopMargin(&inlineTopMargin));

        const double negativePadding = -(static_cast<double>(padding));
        const double sideMargin = negativePadding;
        const double topMargin = isBottomActionBar ? inlineTopMargin + padding : inlineTopMargin;
        const double bottomMargin = negativePadding;

        Thickness margin = {sideMargin, topMargin, sideMargin, bottomMargin};
        RETURN_IF_FAILED(showCardFrameworkElement->put_Margin(margin));

        ComPtr<IUIElement> showCardUIElement;
        RETURN_IF_FAILED(localUiShowCard.As(&showCardUIElement));

        // Set the visibility as Collapsed until the action is triggered
        RETURN_IF_FAILED(showCardUIElement->put_Visibility(Visibility_Collapsed));

        *uiShowCard = showCardUIElement.Detach();
        return S_OK;
    }
    CATCH_RETURN;
}
