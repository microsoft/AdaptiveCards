// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveColumnSetRenderer.h"
#include "AdaptiveColumnSetRenderer.g.cpp"

#include "ActionHelpers.h"
#include "AdaptiveRenderArgs.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    rtxaml::UIElement AdaptiveColumnSetRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                        rtrender::AdaptiveRenderContext const& renderContext,
                                                        rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto adaptiveColumnSet = cardElement.as<rtom::AdaptiveColumnSet>();

            rtxaml::Controls::Border columnSetBorder{};

            auto gridContainer = winrt::make<rtrender::implementation::WholeItemsPanel>();

            columnSetBorder.Child(gridContainer);

            rtom::ContainerStyle containerStyle =
                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleStylingAndPadding(adaptiveColumnSet, columnSetBorder, renderContext, renderArgs);

            auto parentElement = renderArgs.ParentElement();
            auto newRenderArgs =
                winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle, parentElement, renderArgs);

            rtxaml::Controls::Grid xamlGrid{};

            auto columns = adaptiveColumnSet.Columns();

            int currentColumn = 0;
            auto columnRenderer = renderContext.ElementRenderers().Get(L"Column");

            if (columnRenderer == nullptr)
            {
                renderContext.AddWarning(rtom::WarningStatusCode::NoRendererForType, L"No renderer found for type: Column");
                return nullptr;
            }

            auto hostConfig = renderContext.HostConfig();
            auto ancestorHasFallback = renderArgs.AncestorHasFallback();

            bool ifFailureOccured = false;
            for (auto column : columns)
            {
                try
                {
                    auto columnAsCardElement = column.as<rtom::IAdaptiveCardElement>();

                    auto columnDefinitions = xamlGrid.ColumnDefinitions();

                    rtom::FallbackType fallbackType = column.FallbackType();

                    // Build the Column
                    newRenderArgs.AncestorHasFallback(ancestorHasFallback || fallbackType != rtom::FallbackType::None);

                    // TODO: look at the BuildPanel children and callBack in XamlBuilder, ColumnRenderer
                    auto xamlColumn = columnRenderer.Render(column, renderContext, newRenderArgs);
                    /* if (hr == E_PERFORM_FALLBACK)*/

                    // TODO: figure out how to do fallback properly
                    if (xamlColumn == nullptr)
                    {
                        // TODO: am I doing this right?
                        std::tie(xamlColumn, std::ignore) =
                            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::RenderFallback(column, renderContext, newRenderArgs);
                    }
                    newRenderArgs.AncestorHasFallback(ancestorHasFallback);

                    // Check the column for nullptr as it may have been dropped due to fallback
                    if (xamlColumn != nullptr)
                    {
                        // If not the first column
                        rtxaml::UIElement separator{nullptr};
                        if (currentColumn > 0)
                        {
                            // Add Separator to the columnSet
                            // TODO: do I need to cast?
                            auto needsSeparator = ::AdaptiveCards::Rendering::Uwp::XamlHelpers::NeedsSeparator(column);

                            if (needsSeparator)
                            {
                                auto separatorConfig = hostConfig.Separator();
                                auto spacing = GetSpacingSizeFromSpacing(hostConfig, column.Spacing());
                                auto separatorThickness = separatorConfig.LineThickness();
                                auto separatorColor = separatorConfig.LineColor();

                                // Create a new ColumnDefinition for the separator

                                rtxaml::Controls::ColumnDefinition separatorColumnDefinition{};
                                separatorColumnDefinition.Width({1.0, rtxaml::GridUnitType::Auto});
                                columnDefinitions.Append(separatorColumnDefinition);

                                separator = ::AdaptiveCards::Rendering::Uwp::XamlHelpers::CreateSeparator(
                                    renderContext, spacing, separatorThickness, separatorColor, false);
                                // TODO: is this the right logic?
                                if (const auto separatorAsFrameworkElement = separator.try_as<rtxaml::FrameworkElement>())
                                {
                                    rtxaml::Controls::Grid::SetColumn(separatorAsFrameworkElement, currentColumn++);
                                }
                                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AppendXamlElementToPanel(separator, xamlGrid);
                            }
                        }

                        // Determine if the column is auto, stretch, or percentage width, and set the column width
                        rtxaml::Controls::ColumnDefinition columnDefinition{};

                        auto isVisible = column.IsVisible();

                        ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleColumnWidth(column, isVisible, columnDefinition);

                        columnDefinitions.Append(columnDefinition);

                        // Mark the column container with the current column
                        if (const auto columnAsFrameworkElement = xamlColumn.try_as<rtxaml::FrameworkElement>())
                        {
                            rtxaml::Controls::Grid::SetColumn(columnAsFrameworkElement, currentColumn++);
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
