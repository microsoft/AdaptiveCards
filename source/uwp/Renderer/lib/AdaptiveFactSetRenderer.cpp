// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFactSetRenderer.h"
#include "AdaptiveFactSetRenderer.g.cpp"
#include "TextHelpers.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    rtxaml::UIElement AdaptiveFactSetRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                      rtrender::AdaptiveRenderContext const& renderContext,
                                                      rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto adaptiveFactSet = cardElement.as<rtom::AdaptiveFactSet>();

            rtxaml::Controls::Grid xamlGrid{};

            rtxaml::Controls::ColumnDefinition titleColumn{};
            rtxaml::Controls::ColumnDefinition valueColumn{};

            // TODO: does value(0 in this case) matter when type=Auto?
            rtxaml::GridLength factSetGridTitleLength{0, rtxaml::GridUnitType::Auto};
            rtxaml::GridLength factSetGridValueLength{1, rtxaml::GridUnitType::Star};

            titleColumn.Width(factSetGridTitleLength);
            valueColumn.Width(factSetGridValueLength);

            auto columnDefinitions = xamlGrid.ColumnDefinitions();
            columnDefinitions.Append(titleColumn);
            columnDefinitions.Append(valueColumn);

            rtxaml::GridLength factSetGridHeight{0, rtxaml::GridUnitType::Auto};

            auto heightType = cardElement.Height();

            if (heightType == rtom::HeightType::Stretch)
            {
                factSetGridHeight = {1, rtxaml::GridUnitType::Star};
            }

            auto facts = adaptiveFactSet.Facts();

            int currentFact = 0, validFacts = 0;

            for (auto fact : facts)
            {
                rtxaml::Controls::RowDefinition factRow{};
                factRow.Height(factSetGridHeight);

                auto rowDefinitions = xamlGrid.RowDefinitions();
                rowDefinitions.Append(factRow);

                auto hostConfig = renderContext.HostConfig();
                auto factSetConfig = hostConfig.FactSet();

                // Get Language
                winrt::hstring language = fact.Language();

                // Create the title xaml textblock and style it from Host options
                auto titleTextConfig = factSetConfig.Title();
                rtxaml::Controls::TextBlock titleTextBlock{};

                winrt::hstring factTitle = fact.Title();

                SetXamlInlinesWithFactSetTextConfig(renderContext, renderArgs, titleTextConfig, language, factTitle, titleTextBlock);

                // Create the value xaml textblock and style it from Host options
                auto valueTextConfig = factSetConfig.Value();
                rtxaml::Controls::TextBlock valueTextBlock{};

                winrt::hstring factValue = fact.Value();

                SetXamlInlinesWithFactSetTextConfig(renderContext, renderArgs, valueTextConfig, language, factValue, valueTextBlock);

                if (!factTitle.empty() || !factValue.empty())
                {
                    // Mark the column container with the current column

                    auto spacing = factSetConfig.Spacing();
                    titleTextBlock.Margin({0, 0, (double)spacing, 0});

                    ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                                 L"Adaptive.Fact.Title",
                                                                                                 titleTextBlock);

                    ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                                 L"Adaptive.Fact.Value",
                                                                                                 valueTextBlock);

                    rtxaml::Controls::Grid::SetColumn(titleTextBlock, 0);
                    rtxaml::Controls::Grid::SetRow(titleTextBlock, currentFact);

                    rtxaml::Controls::Grid::SetColumn(valueTextBlock, 1);
                    rtxaml::Controls::Grid::SetRow(valueTextBlock, currentFact);

                    // Finally add the column container to the grid, and increment the column count

                    ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AppendXamlElementToPanel(titleTextBlock, xamlGrid);
                    ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AppendXamlElementToPanel(valueTextBlock, xamlGrid);
                    ++currentFact;
                    ++validFacts;
                }
            }

            if (validFacts == 0)
            {
                // TODO: is this right? or we're supposed to do something else?
                return nullptr;
            }

            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.FactSet", xamlGrid);

            return xamlGrid;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
