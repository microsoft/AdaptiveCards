// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveColumnRenderer.h"
#include "AdaptiveColumnRenderer.g.cpp"

#include "ActionHelpers.h"
#include "AdaptiveRenderArgs.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    rtxaml::UIElement AdaptiveColumnRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                     rtrender::AdaptiveRenderContext const& renderContext,
                                                     rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto adaptiveColumn = cardElement.as<rtom::AdaptiveColumn>();

            rtxaml::Controls::Border columnBorder{};

            auto columnPanel = winrt::make<rtrender::implementation::WholeItemsPanel>();

            columnBorder.Child(columnPanel);

            auto previousContextRtl = renderContext.Rtl();
            auto currentRtl = previousContextRtl;
            auto containerRtl = adaptiveColumn.Rtl();

            bool updatedRtl = false;

            if (containerRtl != nullptr)
            {
                currentRtl = containerRtl;
                renderContext.Rtl(currentRtl);
                updatedRtl = true;
            }

            if (currentRtl != nullptr)
            {
                columnPanel.FlowDirection(currentRtl.Value() ? rtxaml::FlowDirection::RightToLeft : rtxaml::FlowDirection::LeftToRight);
            }

            rtom::ContainerStyle containerStyle{};

            // TODO: do I even need this if (const auto..) ?
            if (const auto columnAsContainerBase = adaptiveColumn.try_as<rtom::IAdaptiveContainerBase>())
            {
                containerStyle = ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleStylingAndPadding(columnAsContainerBase,
                                                                                                          columnBorder,
                                                                                                          renderContext,
                                                                                                          renderArgs);
            }

            auto parentElement = renderArgs.ParentElement();

            auto newRenderArgs =
                winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle, parentElement, renderArgs);

            auto childItems = adaptiveColumn.Items();

            ::AdaptiveCards::Rendering::WinUI3::XamlBuilder::BuildPanelChildren(
                childItems, columnPanel, renderContext, newRenderArgs, [](rtxaml::IUIElement) {});

            // If we changed the context's rtl setting, set it back after rendering the children
            if (updatedRtl)
            {
                renderContext.Rtl(previousContextRtl);
            }

            auto verticalContentAlignmentReference = adaptiveColumn.VerticalContentAlignment();

            rtom::VerticalContentAlignment verticalContentAlignment =
                GetValueFromRef(verticalContentAlignmentReference, rtom::VerticalContentAlignment::Top);

            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetVerticalContentAlignmentToChildren(columnPanel, verticalContentAlignment);

            // Assign vertical alignment to strech so column will stretch and respect vertical content alignment
            columnPanel.VerticalAlignment(rtxaml::VerticalAlignment::Stretch);

            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Column", columnPanel);

            uint32_t columnMinHeight = adaptiveColumn.MinHeight();

            // TODO: Do I need to cast adaptiveColumn to rtom::ContainerBase?
            if (columnMinHeight > 0)
            {
                columnPanel.MinHeight(columnMinHeight);
            }

            auto selectAction = adaptiveColumn.SelectAction();

            // Define column As UIElement based on the existence of a backgroundImage
            rtxaml::UIElement columnAsUIElement{nullptr};

            auto backgroundImage = adaptiveColumn.BackgroundImage();

            if (IsBackgroundImageValid(backgroundImage))
            {
                rtxaml::Controls::Grid rootElement{};

                // TODO:No need to cast right? Winrt will call QueryInterface and cast Grid to Panel?
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::ApplyBackgroundToRoot(rootElement, backgroundImage, renderContext, newRenderArgs);

                // TODO: why is it called height if it's HeightType?
                auto columnHeightType = cardElement.Height();

                // Add columnBorder to rootElement
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AppendXamlElementToPanel(columnBorder, rootElement, columnHeightType);

                columnAsUIElement = rootElement;
            }
            else
            {
                columnAsUIElement = columnBorder;
            }

            auto hostConfig = renderContext.HostConfig();

            auto columnControl = ::AdaptiveCards::Rendering::WinUI3::ActionHelpers::HandleSelectAction(
                cardElement,
                selectAction,
                renderContext,
                columnAsUIElement,
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SupportsInteractivity(hostConfig),
                false);

            return columnControl;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
