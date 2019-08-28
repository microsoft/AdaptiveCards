// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveColumnSet.h"
#include "AdaptiveColumnSetRenderer.h"
#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveRenderArgs.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveColumnSetRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveColumnSetRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                              _In_ IAdaptiveRenderContext* renderContext,
                                              _In_ IAdaptiveRenderArgs* renderArgs,
                                              _COM_Outptr_ IUIElement** columnSetControl) noexcept try
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveColumnSet> adaptiveColumnSet;
        RETURN_IF_FAILED(cardElement.As(&adaptiveColumnSet));

        ComPtr<IBorder> columnSetBorder =
            XamlHelpers::CreateXamlClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

        ComPtr<WholeItemsPanel> gridContainer;
        RETURN_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&gridContainer));

        ComPtr<IUIElement> gridContainerAsUIElement;
        RETURN_IF_FAILED(gridContainer.As(&gridContainerAsUIElement));

        RETURN_IF_FAILED(columnSetBorder->put_Child(gridContainerAsUIElement.Get()));

        ComPtr<IAdaptiveContainerBase> columnSetAsContainerBase;
        RETURN_IF_FAILED(adaptiveColumnSet.As(&columnSetAsContainerBase));

        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        RETURN_IF_FAILED(XamlHelpers::HandleStylingAndPadding(
            columnSetAsContainerBase.Get(), columnSetBorder.Get(), renderContext, renderArgs, &containerStyle));

        ComPtr<IFrameworkElement> parentElement;
        RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));
        ComPtr<IAdaptiveRenderArgs> newRenderArgs;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&newRenderArgs, containerStyle, parentElement.Get(), renderArgs));

        ComPtr<IGrid> xamlGrid =
            XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IGridStatics> gridStatics;
        RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

        ComPtr<IVector<AdaptiveColumn*>> columns;
        RETURN_IF_FAILED(adaptiveColumnSet->get_Columns(&columns));
        int currentColumn{};
        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        RETURN_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
        ComPtr<IAdaptiveElementRenderer> columnRenderer;
        RETURN_IF_FAILED(elementRenderers->Get(HStringReference(L"Column").Get(), &columnRenderer));

        if (columnRenderer == nullptr)
        {
            renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::NoRendererForType,
                                      HStringReference(L"No renderer found for type: Column").Get());
            *columnSetControl = nullptr;
            return S_OK;
        }

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        boolean ancestorHasFallback;
        RETURN_IF_FAILED(renderArgs->get_AncestorHasFallback(&ancestorHasFallback));

        ComPtr<IPanel> gridAsPanel;
        RETURN_IF_FAILED(xamlGrid.As(&gridAsPanel));

        HRESULT hrColumns = XamlHelpers::IterateOverVectorWithFailure<AdaptiveColumn, IAdaptiveColumn>(columns.Get(), ancestorHasFallback, [&](IAdaptiveColumn* column) {
            ComPtr<IAdaptiveCardElement> columnAsCardElement;
            ComPtr<IAdaptiveColumn> localColumn(column);
            RETURN_IF_FAILED(localColumn.As(&columnAsCardElement));

            ComPtr<IAdaptiveColumn> testColumn;
            columnAsCardElement.As(&testColumn);

            ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
            RETURN_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));

            ABI::AdaptiveNamespace::FallbackType fallbackType;
            RETURN_IF_FAILED(columnAsCardElement->get_FallbackType(&fallbackType));

            // Build the Column
            RETURN_IF_FAILED(newRenderArgs->put_AncestorHasFallback(
                ancestorHasFallback || fallbackType != ABI::AdaptiveNamespace::FallbackType::None));

            ComPtr<IUIElement> xamlColumn;
            HRESULT hr = columnRenderer->Render(columnAsCardElement.Get(), renderContext, newRenderArgs.Get(), &xamlColumn);
            if (hr == E_PERFORM_FALLBACK)
            {
                RETURN_IF_FAILED(XamlHelpers::RenderFallback(columnAsCardElement.Get(), renderContext, newRenderArgs.Get(), &xamlColumn));
            }

            RETURN_IF_FAILED(newRenderArgs->put_AncestorHasFallback(ancestorHasFallback));

            // Check the column for nullptr as it may have been dropped due to fallback
            if (xamlColumn != nullptr)
            {
                // If not the first column
                ComPtr<IUIElement> separator;
                if (currentColumn > 0)
                {
                    // Add Separator to the columnSet
                    bool needsSeparator;
                    UINT spacing;
                    UINT separatorThickness;
                    ABI::Windows::UI::Color separatorColor;
                    XamlHelpers::GetSeparationConfigForElement(
                        columnAsCardElement.Get(), hostConfig.Get(), &spacing, &separatorThickness, &separatorColor, &needsSeparator);

                    if (needsSeparator)
                    {
                        // Create a new ColumnDefinition for the separator
                        ComPtr<IColumnDefinition> separatorColumnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(
                            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
                        RETURN_IF_FAILED(separatorColumnDefinition->put_Width({1.0, GridUnitType::GridUnitType_Auto}));
                        RETURN_IF_FAILED(columnDefinitions->Append(separatorColumnDefinition.Get()));

                        separator = XamlHelpers::CreateSeparator(renderContext, spacing, separatorThickness, separatorColor, false);
                        ComPtr<IFrameworkElement> separatorAsFrameworkElement;
                        RETURN_IF_FAILED(separator.As(&separatorAsFrameworkElement));
                        gridStatics->SetColumn(separatorAsFrameworkElement.Get(), currentColumn++);
                        XamlHelpers::AppendXamlElementToPanel(separator.Get(), gridAsPanel.Get());
                    }
                }

                // Determine if the column is auto, stretch, or percentage width, and set the column width appropriately
                ComPtr<IColumnDefinition> columnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));

                boolean isVisible;
                RETURN_IF_FAILED(columnAsCardElement->get_IsVisible(&isVisible));

                RETURN_IF_FAILED(XamlHelpers::HandleColumnWidth(column, isVisible, columnDefinition.Get()));

                RETURN_IF_FAILED(columnDefinitions->Append(columnDefinition.Get()));

                // Mark the column container with the current column
                ComPtr<IFrameworkElement> columnAsFrameworkElement;
                RETURN_IF_FAILED(xamlColumn.As(&columnAsFrameworkElement));
                gridStatics->SetColumn(columnAsFrameworkElement.Get(), currentColumn++);

                // Finally add the column container to the grid
                RETURN_IF_FAILED(XamlHelpers::AddRenderedControl(xamlColumn.Get(),
                                                                 columnAsCardElement.Get(),
                                                                 gridAsPanel.Get(),
                                                                 separator.Get(),
                                                                 columnDefinition.Get(),
                                                                 [](IUIElement*) {}));
            }
            return S_OK;
        });
        RETURN_IF_FAILED(hrColumns);

        RETURN_IF_FAILED(XamlHelpers::SetSeparatorVisibility(gridAsPanel.Get()));

        ComPtr<IFrameworkElement> columnSetAsFrameworkElement;
        RETURN_IF_FAILED(xamlGrid.As(&columnSetAsFrameworkElement));
        RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                     L"Adaptive.ColumnSet",
                                                                     columnSetAsFrameworkElement.Get()));
        RETURN_IF_FAILED(columnSetAsFrameworkElement->put_VerticalAlignment(VerticalAlignment_Stretch));

        ComPtr<IAdaptiveActionElement> selectAction;
        RETURN_IF_FAILED(columnSetAsContainerBase->get_SelectAction(&selectAction));

        ComPtr<IPanel> gridContainerAsPanel;
        RETURN_IF_FAILED(gridContainer.As(&gridContainerAsPanel));

        ComPtr<IFrameworkElement> gridContainerAsFrameworkElement;
        RETURN_IF_FAILED(gridContainer.As(&gridContainerAsFrameworkElement));

        ComPtr<IUIElement> gridAsUIElement;
        RETURN_IF_FAILED(xamlGrid.As(&gridAsUIElement));

        ComPtr<IAdaptiveCardElement> columnSetAsCardElement;
        RETURN_IF_FAILED(adaptiveColumnSet.As(&columnSetAsCardElement));

        ABI::AdaptiveNamespace::HeightType columnSetHeightType;
        RETURN_IF_FAILED(columnSetAsCardElement->get_Height(&columnSetHeightType));

        ComPtr<IAdaptiveContainerBase> columnAsContainerBase;
        RETURN_IF_FAILED(adaptiveColumnSet.As(&columnAsContainerBase));

        UINT32 columnSetMinHeight{};
        RETURN_IF_FAILED(columnAsContainerBase->get_MinHeight(&columnSetMinHeight));
        if (columnSetMinHeight > 0)
        {
            RETURN_IF_FAILED(gridContainerAsFrameworkElement->put_MinHeight(columnSetMinHeight));
        }

        XamlHelpers::AppendXamlElementToPanel(xamlGrid.Get(), gridContainerAsPanel.Get(), columnSetHeightType);

        ComPtr<IUIElement> columnSetBorderAsUIElement;
        RETURN_IF_FAILED(columnSetBorder.As(&columnSetBorderAsUIElement));

        XamlHelpers::HandleSelectAction(adaptiveCardElement,
                                        selectAction.Get(),
                                        renderContext,
                                        columnSetBorderAsUIElement.Get(),
                                        XamlHelpers::SupportsInteractivity(hostConfig.Get()),
                                        true,
                                        columnSetControl);
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveColumnSetRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveColumnSet, AdaptiveSharedNamespace::ColumnSet, AdaptiveSharedNamespace::ColumnSetParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
