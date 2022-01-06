// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveColumnSetRenderer.h"
#include "AdaptiveColumnSetRenderer.g.cpp"

#include "ActionHelpers.h"
#include "AdaptiveRenderArgs.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    rtxaml::UIElement AdaptiveColumnSetRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                        winrt::AdaptiveRenderContext const& renderContext,
                                                        winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto adaptiveColumnSet = cardElement.as<winrt::AdaptiveColumnSet>();

            winrt::Border columnSetBorder{};

            auto gridContainer = winrt::make<winrt::implementation::WholeItemsPanel>();

            columnSetBorder.Child(gridContainer);

            winrt::ContainerStyle containerStyle =
                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleStylingAndPadding(adaptiveColumnSet, columnSetBorder, renderContext, renderArgs);

            auto parentElement = renderArgs.ParentElement();
            auto newRenderArgs =
                winrt::make<winrt::implementation::AdaptiveRenderArgs>(containerStyle, parentElement, renderArgs);

            winrt::Grid xamlGrid{};

            auto columns = adaptiveColumnSet.Columns();

            int currentColumn = 0;
            auto columnRenderer = renderContext.ElementRenderers().Get(L"Column");

            if (columnRenderer == nullptr)
            {
                renderContext.AddWarning(winrt::WarningStatusCode::NoRendererForType, L"No renderer found for type: Column");
                return nullptr;
            }

            auto hostConfig = renderContext.HostConfig();
            auto ancestorHasFallback = renderArgs.AncestorHasFallback();

            bool ifFailureOccured = false;
            for (auto column : columns)
            {
                try
                {
                    auto columnAsCardElement = column.as<winrt::IAdaptiveCardElement>();

                    auto columnDefinitions = xamlGrid.ColumnDefinitions();

                    winrt::FallbackType fallbackType = column.FallbackType();

                    // Build the Column
                    newRenderArgs.AncestorHasFallback(ancestorHasFallback || fallbackType != winrt::FallbackType::None);

                    // TODO: look at the BuildPanel children and callBack in XamlBuilder, ColumnRenderer
                    auto xamlColumn = columnRenderer.Render(column, renderContext, newRenderArgs);
                    /* if (hr == E_PERFORM_FALLBACK)*/

                    // TODO: figure out how to do fallback properly
                    if (!xamlColumn)
                    {
                        // TODO: am I doing this right?
                        std::tie(xamlColumn, std::ignore) =
                            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::RenderFallback(column, renderContext, newRenderArgs);
                    }
                    newRenderArgs.AncestorHasFallback(ancestorHasFallback);

                    // Check the column for nullptr as it may have been dropped due to fallback
                    if (xamlColumn)
                    {
                        // If not the first column
                        rtxaml::UIElement separator{nullptr};
                        if (currentColumn > 0)
                        {
                            // Add Separator to the columnSet
                            // TODO: do I need to cast?
                            auto needsSeparator = ::AdaptiveCards::Rendering::Uwp::XamlHelpers::NeedsSeparator(column);
                            // TODO: separator thickness can be 0 in many cases
                            // TODO: is it wise to insert an additional element into the tree just for spacing?

                            if (needsSeparator)
                            {
                                auto separatorParams =
                                    ::AdaptiveCards::Rendering::Uwp::XamlHelpers::GetSeparatorParameters(column, hostConfig);

                                // Create a new ColumnDefinition for the separator

                                winrt::ColumnDefinition separatorColumnDefinition{};
                                separatorColumnDefinition.Width({1.0, rtxaml::GridUnitType::Auto});
                                columnDefinitions.Append(separatorColumnDefinition);

                                separator = ::AdaptiveCards::Rendering::Uwp::XamlHelpers::CreateSeparator(
                                    renderContext, separatorParams.spacing, separatorParams.thickness, separatorParams.color, false);
                                // TODO: is this the right logic?
                                if (const auto separatorAsFrameworkElement = separator.try_as<rtxaml::FrameworkElement>())
                                {
                                    winrt::Grid::SetColumn(separatorAsFrameworkElement, currentColumn++);
                                }
                                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AppendXamlElementToPanel(separator, xamlGrid);
                            }
                        }

                        // Determine if the column is auto, stretch, or percentage width, and set the column width
                        winrt::ColumnDefinition columnDefinition{};

                        auto isVisible = column.IsVisible();

                        ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleColumnWidth(column, isVisible, columnDefinition);

                        columnDefinitions.Append(columnDefinition);

                        // Mark the column container with the current column
                        if (const auto columnAsFrameworkElement = xamlColumn.try_as<rtxaml::FrameworkElement>())
                        {
                            winrt::Grid::SetColumn(columnAsFrameworkElement, currentColumn++);
                        }

                        ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AddRenderedControl(
                            xamlColumn, column, xamlGrid, separator, columnDefinition, [](rtxaml::UIElement const&) {});
                    }
                }
                catch (winrt::hresult_error const& ex)
                {
                    // TODO: probably log an error?
                    // TODO: I don't think we need this inner try/catc. The one outside should handle this, right?
                    winrt::throw_last_error();
                    // ifFailureOccured = true;
                }
            }

            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetSeparatorVisibility(xamlGrid);

            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.ColumnSet", xamlGrid);
            xamlGrid.VerticalAlignment(rtxaml::VerticalAlignment::Stretch);

            auto selectAction = adaptiveColumnSet.SelectAction();
            auto columnSetHeightType = adaptiveColumnSet.Height();

            auto columnSetMinHeight = adaptiveColumnSet.MinHeight();
            if (columnSetMinHeight > 0)
            {
                gridContainer.MinHeight(columnSetMinHeight);
            }

            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AppendXamlElementToPanel(xamlGrid, gridContainer, columnSetHeightType);

            return ::AdaptiveCards::Rendering::Uwp::ActionHelpers::HandleSelectAction(
                cardElement,
                selectAction,
                renderContext,
                columnSetBorder,
                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SupportsInteractivity(hostConfig),
                true);
        }

        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
