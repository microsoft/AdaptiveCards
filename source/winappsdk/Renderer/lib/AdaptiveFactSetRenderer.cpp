// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFactSetRenderer.h"
#include "TextHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    /*HRESULT AdaptiveFactSetRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN();*/

    rtxaml::UIElement AdaptiveFactSetRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                      rtrender::AdaptiveRenderContext const& renderContext,
                                                      rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            /*ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
            ComPtr<IAdaptiveFactSet> adaptiveFactSet;*/
            auto adaptiveFactSet = cardElement.as<rtom::AdaptiveFactSet>();

            // RETURN_IF_FAILED(cardElement.As(&adaptiveFactSet));

            /* ComPtr<IGrid> xamlGrid =
                 XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
             ComPtr<IGridStatics> gridStatics;
             RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));*/

            rtxaml::Controls::Grid xamlGrid{};
            rtxaml::Controls::IGridStatics gridStatics{};

            /*ComPtr<IColumnDefinition> titleColumn = XamlHelpers::CreateABIClass<IColumnDefinition>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
            ComPtr<IColumnDefinition> valueColumn = XamlHelpers::CreateABIClass<IColumnDefinition>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
            GridLength factSetGridTitleLength = {0, GridUnitType::GridUnitType_Auto};
            GridLength factSetGridValueLength = {1, GridUnitType::GridUnitType_Star};*/

            rtxaml::Controls::ColumnDefinition titleColumn{};
            rtxaml::Controls::ColumnDefinition valueColumn{};

            rtxaml::GridLength factSetGridTitleLength{0, rtxaml::GridUnitType::Auto};
            rtxaml::GridLength factSetGridValueLength{1, rtxaml::GridUnitType::Star};

            /*RETURN_IF_FAILED(titleColumn->put_Width(factSetGridTitleLength));
            RETURN_IF_FAILED(valueColumn->put_Width(factSetGridValueLength));*/

            titleColumn.Width(factSetGridTitleLength);
            valueColumn.Width(factSetGridValueLength);

            // ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
            // RETURN_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));
            // RETURN_IF_FAILED(columnDefinitions->Append(titleColumn.Get()));
            // RETURN_IF_FAILED(columnDefinitions->Append(valueColumn.Get()));
            auto columnDefinitions = xamlGrid.ColumnDefinitions();
            columnDefinitions.Append(titleColumn);
            columnDefinitions.Append(valueColumn);

            /*GridLength factSetGridHeight = {0, GridUnitType::GridUnitType_Auto};*/
            /* ABI::AdaptiveCards::ObjectModel::WinUI3::HeightType heightType;*/
            rtxaml::GridLength factSetGridHeight{0, rtxaml::GridUnitType::Auto};

            auto heightType = cardElement.Height();

            if (heightType == rtom::HeightType::Stretch)
            {
                factSetGridHeight = {1, rtxaml::GridUnitType::Star};
            }

            /*ComPtr<IVector<AdaptiveFact*>> facts;
            RETURN_IF_FAILED(adaptiveFactSet->get_Facts(&facts));*/
            auto facts = adaptiveFactSet.Facts();

            int currentFact = 0, validFacts = 0;
            /* IterateOverVector<AdaptiveFact, IAdaptiveFact>(
                 facts.Get(),
                 [xamlGrid, gridStatics, factSetGridHeight, &currentFact, &validFacts, renderContext, renderArgs](IAdaptiveFact* fact)
                 {*/
            for (auto fact : facts)
            {
                /*ComPtr<IRowDefinition> factRow = XamlHelpers::CreateABIClass<IRowDefinition>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RowDefinition));
                RETURN_IF_FAILED(factRow->put_Height(factSetGridHeight));*/

                rtxaml::Controls::RowDefinition factRow{};
                factRow.Height(factSetGridHeight);

                /* ComPtr<IVector<RowDefinition*>> rowDefinitions;
                 RETURN_IF_FAILED(xamlGrid->get_RowDefinitions(&rowDefinitions));
                 RETURN_IF_FAILED(rowDefinitions->Append(factRow.Get()));*/
                auto rowDefinitions = xamlGrid.RowDefinitions();
                rowDefinitions.Append(factRow);

                /*ComPtr<IAdaptiveFact> localFact(fact);
                ComPtr<IAdaptiveHostConfig> hostConfig;
                RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
                ComPtr<IAdaptiveFactSetConfig> factSetConfig;
                RETURN_IF_FAILED(hostConfig->get_FactSet(&factSetConfig));*/

                auto hostConfig = renderContext.HostConfig();
                auto factSetConfig = hostConfig.FactSet();

                // Get Language
                /* HString language;
                 RETURN_IF_FAILED(localFact->get_Language(language.GetAddressOf()));*/
                winrt::hstring language = fact.Language();

                // Create the title xaml textblock and style it from Host options
                /*ComPtr<IAdaptiveFactSetTextConfig> titleTextConfig;
                RETURN_IF_FAILED(factSetConfig->get_Title(&titleTextConfig));*/
                auto titleTextConfig = factSetConfig.Title();

                /*ComPtr<ITextBlock> titleTextBlock =
                    XamlHelpers::CreateABIClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));*/
                rtxaml::Controls::TextBlock titleTextBlock{};

                /*HString factTitle;
                RETURN_IF_FAILED(localFact->get_Title(factTitle.GetAddressOf()));*/
                winrt::hstring factTitle = fact.Title();

                /* RETURN_IF_FAILED(SetXamlInlinesWithFactSetTextConfig(
                     renderContext, renderArgs, titleTextConfig.Get(), language.Get(), factTitle.Get(), titleTextBlock.Get()));*/
                SetXamlInlinesWithFactSetTextConfig(renderContext, renderArgs, titleTextConfig, language, factTitle, titleTextBlock);

                // Create the value xaml textblock and style it from Host options
                /*ComPtr<IAdaptiveFactSetTextConfig> valueTextConfig;
                RETURN_IF_FAILED(factSetConfig->get_Value(&valueTextConfig));*/
                auto valueTextConfig = factSetConfig.Value();

                /*ComPtr<ITextBlock> valueTextBlock =
                    XamlHelpers::CreateABIClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));*/
                rtxaml::Controls::TextBlock valueTextBlock{};

                /*HString factValue;
                RETURN_IF_FAILED(localFact->get_Value(factValue.GetAddressOf()));*/
                winrt::hstring factValue = fact.Value();

                /* RETURN_IF_FAILED(SetXamlInlinesWithFactSetTextConfig(
                     renderContext, renderArgs, valueTextConfig.Get(), language.Get(), factValue.Get(), valueTextBlock.Get()));*/
                SetXamlInlinesWithFactSetTextConfig(renderContext, renderArgs, valueTextConfig, language, factValue, valueTextBlock);

                /* if (factTitle != nullptr || factValue != nullptr)*/
                if (!factTitle.empty() || !factValue.empty())
                {
                    // Mark the column container with the current column
                    /*ComPtr<IFrameworkElement> titleTextBlockAsFrameWorkElement;
                    RETURN_IF_FAILED(titleTextBlock.As(&titleTextBlockAsFrameWorkElement));
                    ComPtr<IFrameworkElement> valueTextBlockAsFrameWorkElement;
                    RETURN_IF_FAILED(valueTextBlock.As(&valueTextBlockAsFrameWorkElement));*/

                    auto spacing = factSetConfig.Spacing();
                    // RETURN_IF_FAILED(factSetConfig->get_Spacing(&spacing));
                    // Add spacing from hostconfig to right margin of title.
                    // titleTextBlockAsFrameWorkElement->put_Margin({0, 0, (double)spacing, 0});
                    titleTextBlock.Margin({0, 0, (double)spacing, 0});

                    ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                                    L"Adaptive.Fact.Title",
                                                                                                    titleTextBlock);
                    ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                                    L"Adaptive.Fact.Value",
                                                                                                    valueTextBlock);

                    gridStatics.SetColumn(titleTextBlock, 0);
                    gridStatics.SetRow(titleTextBlock, currentFact);

                    gridStatics.SetColumn(valueTextBlock, 1);
                    gridStatics.SetRow(valueTextBlock, currentFact);

                    // Finally add the column container to the grid, and increment the column count
                    /*  ComPtr<IPanel> gridAsPanel;
                      RETURN_IF_FAILED(xamlGrid.As(&gridAsPanel));
                      ComPtr<IUIElement> titleUIElement;
                      RETURN_IF_FAILED(titleTextBlockAsFrameWorkElement.As(&titleUIElement));
                      ComPtr<IUIElement> valueUIElement;
                      RETURN_IF_FAILED(valueTextBlockAsFrameWorkElement.As(&valueUIElement));*/

                    ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AppendXamlElementToPanel(titleTextBlock, xamlGrid);
                    ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AppendXamlElementToPanel(valueTextBlock, xamlGrid);
                    ++currentFact;
                    ++validFacts;
                }
            }

            if (validFacts == 0)
            {
                // TODO: is this right? or we're supposed to do something else?
                return nullptr;
            }

            /*ComPtr<IFrameworkElement> factSetAsFrameworkElement;
            RETURN_IF_FAILED(xamlGrid.As(&factSetAsFrameworkElement));*/
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.FactSet", xamlGrid);

            return xamlGrid;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
