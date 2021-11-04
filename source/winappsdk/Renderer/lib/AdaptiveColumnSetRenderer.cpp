// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveColumnSetRenderer.h"

#include "ActionHelpers.h"
#include "AdaptiveRenderArgs.h"

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
    /*HRESULT AdaptiveColumnSetRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN();*/

    rtxaml::UIElement AdaptiveColumnSetRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                        rtrender::AdaptiveRenderContext const& renderContext,
                                                        rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        /*  ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
          ComPtr<IAdaptiveColumnSet> adaptiveColumnSet;
          RETURN_IF_FAILED(cardElement.As(&adaptiveColumnSet));*/

        auto adaptiveColumnSet = cardElement.as<rtom::AdaptiveColumnSet>();

        // ComPtr<IBorder> columnSetBorder =
        // XamlHelpers::CreateABIClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

        rtxaml::Controls::Border columnSetBorder{};

        // ComPtr<WholeItemsPanel> gridContainer;
        // RETURN_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&gridContainer));

        auto gridContainer = winrt::make<rtrender::implementation::WholeItemsPanel>();

        /*ComPtr<IUIElement> gridContainerAsUIElement;
        RETURN_IF_FAILED(gridContainer.As(&gridContainerAsUIElement));*/

        columnSetBorder.Child(gridContainer);

        // RETURN_IF_FAILED(columnSetBorder->put_Child(gridContainerAsUIElement.Get()));

        /*ComPtr<IAdaptiveContainerBase> columnSetAsContainerBase;
        RETURN_IF_FAILED(adaptiveColumnSet.As(&columnSetAsContainerBase));*/

        /*ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle containerStyle;
        RETURN_IF_FAILED(XamlHelpers::HandleStylingAndPadding(
            columnSetAsContainerBase.Get(), columnSetBorder.Get(), renderContext, renderArgs, &containerStyle));*/

        rtom::ContainerStyle containerStyle =
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleStylingAndPadding(adaptiveColumnSet, columnSetBorder, renderContext, renderArgs);

        /*ComPtr<IFrameworkElement> parentElement;
        RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));*/
        auto parentElement = renderArgs.ParentElement();
        auto newRenderArgs = winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle, parentElement, renderArgs);

        /* ComPtr<IGrid> xamlGrid = XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
         ComPtr<IGridStatics> gridStatics;
         RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));*/

        rtxaml::Controls::Grid xamlGrid{};
        rtxaml::Controls::IGridStatics gridStatics{};

        // ComPtr<IVector<AdaptiveColumn*>> columns;
        // RETURN_IF_FAILED(adaptiveColumnSet->get_Columns(&columns));

        auto columns = adaptiveColumnSet.Columns();

        int currentColumn{};
        // ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        // RETURN_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
        // ComPtr<IAdaptiveElementRenderer> columnRenderer;
        // RETURN_IF_FAILED(elementRenderers->Get(HStringReference(L"Column").Get(), &columnRenderer));
        auto elementRenderers = renderContext.ElementRenderers();
        auto columnRenderer = elementRenderers.Get(L"Column");

        if (columnRenderer == nullptr)
        {
            /* renderContext->AddWarning(ABI::AdaptiveCards::ObjectModel::WinUI3::WarningStatusCode::NoRendererForType,
                                       HStringReference(L"No renderer found for type: Column").Get());
             *columnSetControl = nullptr;*/
            // TODO: revisit and see what we need to return
            renderContext.AddWarning(rtom::WarningStatusCode::NoRendererForType, L"No renderer found for type: Column");
            return nullptr;
            // return S_OK;
        }

        /*  ComPtr<IAdaptiveHostConfig> hostConfig;
          RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

          boolean ancestorHasFallback;
          RETURN_IF_FAILED(renderArgs->get_AncestorHasFallback(&ancestorHasFallback));

          ComPtr<IPanel> gridAsPanel;
          RETURN_IF_FAILED(xamlGrid.As(&gridAsPanel));*/

        auto hostConfig = renderContext.HostConfig();
        auto ancestorHasFallback = renderArgs.AncestorHasFallback();

        /*  HRESULT hrColumns = IterateOverVectorWithFailure<AdaptiveColumn, IAdaptiveColumn>(
              columns.Get(),
              ancestorHasFallback,
              [&](IAdaptiveColumn* column)
              {*/
        bool ifFailureOccured = false;
        for (auto column : columns)
        {
            try
            {
                /*ComPtr<IAdaptiveCardElement> columnAsCardElement;
                ComPtr<IAdaptiveColumn> localColumn(column);
                RETURN_IF_FAILED(localColumn.As(&columnAsCardElement));*/

                auto columnAsCardElement = column.as<rtom::IAdaptiveCardElement>();

                /*ComPtr<IAdaptiveColumn> testColumn;
                columnAsCardElement.As(&testColumn);*/

                /*ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
                RETURN_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));*/
                auto columnDefinitions = xamlGrid.ColumnDefinitions();

                rtom::FallbackType fallbackType = column.FallbackType();
                // RETURN_IF_FAILED(columnAsCardElement->get_FallbackType(&fallbackType));

                // Build the Column
                /* RETURN_IF_FAILED(newRenderArgs->put_AncestorHasFallback(
                     ancestorHasFallback || fallbackType != ABI::AdaptiveCards::ObjectModel::WinUI3::FallbackType::None));*/
                newRenderArgs.AncestorHasFallback(ancestorHasFallback || fallbackType != rtom::FallbackType::None);

                /*ComPtr<IUIElement> xamlColumn;
                HRESULT hr = columnRenderer->Render(columnAsCardElement.Get(), renderContext, newRenderArgs.Get(), &xamlColumn);*/
                // TODO: look at the BuildPanel children and callBack in XamlBuilder, ColumnRenderer
                auto xamlColumn = columnRenderer.Render(column, renderContext, newRenderArgs);
                /* if (hr == E_PERFORM_FALLBACK)*/

                // TODO: figure out how to do fallback properly
                if (xamlColumn == nullptr)
                {
                    /*RETURN_IF_FAILED(
                        XamlHelpers::RenderFallback(columnAsCardElement.Get(), renderContext, newRenderArgs.Get(), &xamlColumn, nullptr));*/
                    // TODO: am I doing this right?
                    std::tie(xamlColumn, std::ignore) =
                        ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::RenderFallback(column, renderContext, newRenderArgs);
                }

                /*RETURN_IF_FAILED(newRenderArgs->put_AncestorHasFallback(ancestorHasFallback));*/
                newRenderArgs.AncestorHasFallback(ancestorHasFallback);

                // Check the column for nullptr as it may have been dropped due to fallback
                if (xamlColumn != nullptr)
                {
                    // If not the first column
                    /* ComPtr<IUIElement> separator;*/
                    rtxaml::UIElement separator{nullptr};
                    if (currentColumn > 0)
                    {
                        // Add Separator to the columnSet
                        // TODO: do I need to cast?
                        auto needsSeparator = ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::NeedsSeparator(column);
                        /*
                        UINT spacing;
                        UINT separatorThickness;
                        ABI::Windows::UI::Color separatorColor;
                        XamlHelpers::GetSeparationConfigForElement(
                            columnAsCardElement.Get(), hostConfig.Get(), &spacing, &separatorThickness, &separatorColor, &needsSeparator);*/

                        if (needsSeparator)
                        {
                            auto separatorConfig = hostConfig.Separator();
                            auto spacing = GetSpacingSizeFromSpacing(hostConfig, column.Spacing());
                            auto separatorThickness = separatorConfig.LineThickness();
                            auto separatorColor = separatorConfig.LineColor();

                            // Create a new ColumnDefinition for the separator
                            /* ComPtr<IColumnDefinition> separatorColumnDefinition = XamlHelpers::CreateABIClass<IColumnDefinition>(
                                 HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
                             RETURN_IF_FAILED(separatorColumnDefinition->put_Width({1.0, GridUnitType::GridUnitType_Auto}));
                             RETURN_IF_FAILED(columnDefinitions->Append(separatorColumnDefinition.Get()));*/
                            rtxaml::Controls::ColumnDefinition separatorColumnDefinition{};
                            separatorColumnDefinition.Width({1.0, rtxaml::GridUnitType::Auto});
                            columnDefinitions.Append(separatorColumnDefinition);

                            separator = ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::CreateSeparator(
                                renderContext, spacing, separatorThickness, separatorColor, false);
                            if (const auto separatorAsFrameworkElement = separator.try_as<rtxaml::FrameworkElement>())
                            {
                                gridStatics.SetColumn(separatorAsFrameworkElement, currentColumn++);
                            }
                            /*  ComPtr<IFrameworkElement> separatorAsFrameworkElement;
                              RETURN_IF_FAILED(separator.As(&separatorAsFrameworkElement));*/
                            /*gridStatics->SetColumn(separatorAsFrameworkElement.Get(), currentColumn++);
                            XamlHelpers::AppendXamlElementToPanel(separator.Get(), gridAsPanel.Get());*/
                        }
                    }

                    // Determine if the column is auto, stretch, or percentage width, and set the column width appropriately
                    /*ComPtr<IColumnDefinition> columnDefinition = XamlHelpers::CreateABIClass<IColumnDefinition>(
                        HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));*/
                    rtxaml::Controls::ColumnDefinition columnDefinition{};

                    // boolean isVisible;
                    // RETURN_IF_FAILED(columnAsCardElement->get_IsVisible(&isVisible));
                    auto isVisible = column.IsVisible();

                    /*RETURN_IF_FAILED(XamlHelpers::HandleColumnWidth(column, isVisible, columnDefinition.Get()));*/
                    ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleColumnWidth(column, isVisible, columnDefinition);

                    /*RETURN_IF_FAILED(columnDefinitions->Append(columnDefinition.Get()));*/
                    columnDefinitions.Append(columnDefinition);

                    // Mark the column container with the current column
                    /* ComPtr<IFrameworkElement> columnAsFrameworkElement;
                     RETURN_IF_FAILED(xamlColumn.As(&columnAsFrameworkElement));
                     gridStatics->SetColumn(columnAsFrameworkElement.Get(), currentColumn++);*/
                    if (const auto columnAsFrameworkElement = xamlColumn.try_as<rtxaml::FrameworkElement>())
                    {
                        gridStatics.SetColumn(columnAsFrameworkElement, currentColumn++);
                    }

                    // Finally add the column container to the grid
                    /*RETURN_IF_FAILED(XamlHelpers::AddRenderedControl(xamlColumn.Get(),
                                                                     columnAsCardElement.Get(),
                                                                     gridAsPanel.Get(),
                                                                     separator.Get(),
                                                                     columnDefinition.Get(),
                                                                     [](IUIElement*) {}));*/

                    ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AddRenderedControl(
                        xamlColumn, column, xamlGrid, separator, columnDefinition, [](rtxaml::UIElement const&) {});
                }
            }
            catch (winrt::hresult_error const& ex)
            {
                // TODO: probably log an error?
                ifFailureOccured = true;
            }
        }
        /*RETURN_IF_FAILED(hrColumns);*/
        // TODO: Rethink this. Should I rewrite VectorWithFailure to encompass try/catch?
        if (ifFailureOccured)
        {
            return nullptr;
        }

        /*RETURN_IF_FAILED(XamlHelpers::SetSeparatorVisibility(gridAsPanel.Get()));*/
        ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetSeparatorVisibility(xamlGrid);

        /*ComPtr<IFrameworkElement> columnSetAsFrameworkElement;
        RETURN_IF_FAILED(xamlGrid.As(&columnSetAsFrameworkElement));
        RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                     L"Adaptive.ColumnSet",
                                                                     columnSetAsFrameworkElement.Get()));*/
        ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.ColumnSet", xamlGrid);
        xamlGrid.VerticalAlignment(rtxaml::VerticalAlignment::Stretch);
        /*RETURN_IF_FAILED(columnSetAsFrameworkElement->put_VerticalAlignment(VerticalAlignment_Stretch));*/

        /* ComPtr<IAdaptiveActionElement> selectAction;
         RETURN_IF_FAILED(columnSetAsContainerBase->get_SelectAction(&selectAction));

         ComPtr<IPanel> gridContainerAsPanel;
         RETURN_IF_FAILED(gridContainer.As(&gridContainerAsPanel));

         ComPtr<IFrameworkElement> gridContainerAsFrameworkElement;
         RETURN_IF_FAILED(gridContainer.As(&gridContainerAsFrameworkElement));

         ComPtr<IUIElement> gridAsUIElement;
         RETURN_IF_FAILED(xamlGrid.As(&gridAsUIElement));

         ComPtr<IAdaptiveCardElement> columnSetAsCardElement;
         RETURN_IF_FAILED(adaptiveColumnSet.As(&columnSetAsCardElement));

         ABI::AdaptiveCards::ObjectModel::WinUI3::HeightType columnSetHeightType;
         RETURN_IF_FAILED(columnSetAsCardElement->get_Height(&columnSetHeightType));

         ComPtr<IAdaptiveContainerBase> columnAsContainerBase;
         RETURN_IF_FAILED(adaptiveColumnSet.As(&columnAsContainerBase));*/

        auto selectAction = adaptiveColumnSet.SelectAction();
        auto columnSetHeightType = adaptiveColumnSet.Height();

        /*UINT32 columnSetMinHeight{};
        RETURN_IF_FAILED(columnAsContainerBase->get_MinHeight(&columnSetMinHeight));*/

        auto columnSetMinHeight = adaptiveColumnSet.MinHeight();
        if (columnSetMinHeight > 0)
        {
            /*RETURN_IF_FAILED(gridContainerAsFrameworkElement->put_MinHeight(columnSetMinHeight));*/
            gridContainer.MinHeight(columnSetMinHeight);
        }

        ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AppendXamlElementToPanel(xamlGrid, gridContainer, columnSetHeightType);

        /*ComPtr<IUIElement> columnSetBorderAsUIElement;
        RETURN_IF_FAILED(columnSetBorder.As(&columnSetBorderAsUIElement));*/

        return ::AdaptiveCards::Rendering::WinUI3::ActionHelpers::HandleSelectAction(
            cardElement,
            selectAction,
            renderContext,
            columnSetBorder,
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SupportsInteractivity(hostConfig),
            true);
    }
}
