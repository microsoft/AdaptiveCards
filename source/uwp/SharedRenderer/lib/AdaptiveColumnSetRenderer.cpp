// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveColumnSetRenderer.h"
#include "AdaptiveColumnSetRenderer.g.cpp"

#include "ActionHelpers.h"
#include "AdaptiveRenderArgs.h"
#include "WholeItemsPanel.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::UIElement AdaptiveColumnSetRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
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
                XamlHelpers::HandleStylingAndPadding(adaptiveColumnSet, columnSetBorder, renderContext, renderArgs);

            auto newRenderArgs =
                winrt::make<winrt::implementation::AdaptiveRenderArgs>(containerStyle, renderArgs.ParentElement(), renderArgs);

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

            for (auto column : columns)
            {
                auto columnAsCardElement = column.as<winrt::IAdaptiveCardElement>();

                auto columnDefinitions = xamlGrid.ColumnDefinitions();

                winrt::FallbackType fallbackType = column.FallbackType();

                newRenderArgs.AncestorHasFallback(ancestorHasFallback || fallbackType != winrt::FallbackType::None);

                // Build the Column
                winrt::UIElement xamlColumn{nullptr};
                try
                {
                    xamlColumn = columnRenderer.Render(column, renderContext, newRenderArgs);
                }
                catch (winrt::hresult_error const& ex)
                {
                    if (ex.code() != E_PERFORM_FALLBACK)
                    {
                        throw ex;
                    }
                    // We try to perform callback in case column renderer threw a E_PERFROM_CALLBACK
                    std::tie(xamlColumn, std::ignore) = XamlHelpers::RenderFallback(column, renderContext, newRenderArgs);
                }
                newRenderArgs.AncestorHasFallback(ancestorHasFallback);

                // Check the column for nullptr as it may have been dropped due to fallback
                if (xamlColumn)
                {
                    // If not the first column
                    winrt::UIElement separator{nullptr};
                    if (currentColumn > 0)
                    {
                        // Add Separator to the columnSet
                        auto needsSeparator = XamlHelpers::NeedsSeparator(column);

                        if (needsSeparator)
                        {
                            auto separatorParams = XamlHelpers::GetSeparatorParameters(column, hostConfig);

                            // Create a new ColumnDefinition for the separator
                            winrt::ColumnDefinition separatorColumnDefinition{};
                            separatorColumnDefinition.Width({1.0, winrt::GridUnitType::Auto});
                            columnDefinitions.Append(separatorColumnDefinition);

                            separator = XamlHelpers::CreateSeparator(renderContext,
                                                                     separatorParams.spacing,
                                                                     separatorParams.thickness,
                                                                     separatorParams.color,
                                                                     false);

                            if (const auto separatorAsFrameworkElement = separator.try_as<winrt::FrameworkElement>())
                            {
                                winrt::Grid::SetColumn(separatorAsFrameworkElement, currentColumn++);
                            }
                            XamlHelpers::AppendXamlElementToPanel(separator, xamlGrid);
                        }
                    }

                    // Determine if the column is auto, stretch, or percentage width, and set the column width
                    winrt::ColumnDefinition columnDefinition{};

                    auto isVisible = column.IsVisible();

                    XamlHelpers::HandleColumnWidth(column, isVisible, columnDefinition);

                    columnDefinitions.Append(columnDefinition);

                    // Mark the column container with the current column
                    if (const auto columnAsFrameworkElement = xamlColumn.try_as<winrt::FrameworkElement>())
                    {
                        winrt::Grid::SetColumn(columnAsFrameworkElement, currentColumn++);
                    }

                    XamlHelpers::AddRenderedControl(xamlColumn, column, xamlGrid, separator, columnDefinition, [](winrt::UIElement const&) {});
                }
            }

            XamlHelpers::SetSeparatorVisibility(xamlGrid);

            const auto horizontalAlignmentRef = adaptiveColumnSet.HorizontalAlignment();
            auto horizontalAlignment =
                GetValueFromRef(horizontalAlignmentRef, winrt::HAlignment::Left);

            if (horizontalAlignment == winrt::HAlignment::Center)
            {
                xamlGrid.HorizontalAlignment(winrt::HorizontalAlignment::Center);
            }
			else if (horizontalAlignment == winrt::HAlignment::Right)
			{
				xamlGrid.HorizontalAlignment(winrt::HorizontalAlignment::Right);
			}

            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.ColumnSet", xamlGrid);
            xamlGrid.VerticalAlignment(winrt::VerticalAlignment::Stretch);

            auto selectAction = adaptiveColumnSet.SelectAction();
            auto columnSetHeightType = adaptiveColumnSet.Height();

            auto columnSetMinHeight = adaptiveColumnSet.MinHeight();
            if (columnSetMinHeight > 0)
            {
                gridContainer.MinHeight(columnSetMinHeight);
            }

            XamlHelpers::AppendXamlElementToPanel(xamlGrid, gridContainer, columnSetHeightType);

            return ::AdaptiveCards::Rendering::Xaml_Rendering::ActionHelpers::HandleSelectAction(
                cardElement, selectAction, renderContext, columnSetBorder, XamlHelpers::SupportsInteractivity(hostConfig), true);
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
