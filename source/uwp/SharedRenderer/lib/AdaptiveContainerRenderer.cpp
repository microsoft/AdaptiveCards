// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "ActionHelpers.h"
#include "AdaptiveContainerRenderer.h"
#include "AdaptiveContainerRenderer.g.cpp"
#include "AdaptiveRenderArgs.h"
#include "WholeItemsPanel.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::UIElement AdaptiveContainerRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                       winrt::AdaptiveRenderContext const& renderContext,
                                                       winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto adaptiveContainer = cardElement.as<winrt::IAdaptiveContainer>();
            auto adaptiveContainerBase = cardElement.as<winrt::IAdaptiveContainerBase>();
            auto containerPanel = winrt::make<winrt::implementation::WholeItemsPanel>();

            // Get any RTL setting set on either the current context or on this container. Any value set on the
            // container should be set on the context to apply to all children
            auto previousContextRtl = renderContext.Rtl();
            auto currentRtl = previousContextRtl;
            auto containerRtl = adaptiveContainer.Rtl();

            bool updatedRtl = false;
            if (containerRtl)
            {
                currentRtl = containerRtl;
                renderContext.Rtl(currentRtl);
                updatedRtl = true;
            }

            if (currentRtl)
            {
                boolean rtlValue = currentRtl.GetBoolean();
                containerPanel.FlowDirection(rtlValue ? winrt::FlowDirection::RightToLeft : winrt::FlowDirection::LeftToRight);
            }

            // Assign vertical alignment to strech so column will stretch and respect vertical content alignment
            auto containerHeightType = cardElement.Height();
            if (containerHeightType == winrt::HeightType::Auto)
            {
                containerPanel.VerticalAlignment(winrt::VerticalAlignment::Stretch);
            }

            uint32_t containerMinHeight = adaptiveContainerBase.MinHeight();

            if (containerMinHeight > 0)
            {
                containerPanel.MinHeight(containerMinHeight);
            }

            winrt::Border containerBorder{};

            auto containerStyle =
                XamlHelpers::HandleStylingAndPadding(adaptiveContainerBase, containerBorder, renderContext, renderArgs);
            auto newRenderArgs =
                winrt::make<winrt::implementation::AdaptiveRenderArgs>(containerStyle, renderArgs.ParentElement(), renderArgs);

            auto parentElement = renderArgs.ParentElement();

            auto childItems = adaptiveContainer.Items();
            ::AdaptiveCards::Rendering::Xaml_Rendering::XamlBuilder::BuildPanelChildren(
                childItems, containerPanel.as<winrt::Panel>(), renderContext, newRenderArgs, [](winrt::UIElement) {});

            // If we changed the context's rtl setting, set it back after rendering the children
            if (updatedRtl)
            {
                renderContext.Rtl(previousContextRtl);
            }

            auto verticalContentAlignmentReference = adaptiveContainer.VerticalContentAlignment();
            winrt::VerticalContentAlignment verticalContentAlignment =
                GetValueFromRef(verticalContentAlignmentReference, winrt::VerticalContentAlignment::Top);

            XamlHelpers::SetVerticalContentAlignmentToChildren(containerPanel, verticalContentAlignment);

            // Check if backgroundImage defined
            auto backgroundImage = adaptiveContainer.BackgroundImage();

            if (IsBackgroundImageValid(backgroundImage))
            {
                winrt::Grid rootElement{};
                XamlHelpers::ApplyBackgroundToRoot(rootElement, backgroundImage, renderContext);

                // Add rootElement to containerBorder
                containerBorder.Child(rootElement);

                // Add containerPanel to rootElement
                XamlHelpers::AppendXamlElementToPanel(containerPanel, rootElement, containerHeightType);
            }
            else
            {
                // instead, directly add containerPanel to containerBorder
                containerBorder.Child(containerPanel);
            }

            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Container", containerPanel);

            auto selectAction = adaptiveContainerBase.SelectAction();
            auto hostConfig = renderContext.HostConfig();

            return ::AdaptiveCards::Rendering::Xaml_Rendering::ActionHelpers::HandleSelectAction(
                cardElement, selectAction, renderContext, containerBorder, XamlHelpers::SupportsInteractivity(hostConfig), true);
        }
        catch (winrt::hresult_error const& ex)
        {
            // In case we need to perform fallback, propagate it up to the parent
            if (ex.code() == E_PERFORM_FALLBACK)
            {
                throw ex;
            }
            XamlHelpers::ErrForRenderFailedForElement(renderContext, cardElement.ElementTypeString(), ex.message());
            return nullptr;
        }
    }
}
