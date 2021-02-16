// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveFactSet.h"
#include "AdaptiveFactSetRenderer.h"
#include "TextHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveFactSetRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveFactSetRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                            _In_ IAdaptiveRenderContext* renderContext,
                                            _In_ IAdaptiveRenderArgs* renderArgs,
                                            _COM_Outptr_ IUIElement** factSetControl) noexcept
    try
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveFactSet> adaptiveFactSet;

        RETURN_IF_FAILED(cardElement.As(&adaptiveFactSet));

        ComPtr<IGrid> xamlGrid =
            XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IGridStatics> gridStatics;
        RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

        ComPtr<IColumnDefinition> titleColumn = XamlHelpers::CreateXamlClass<IColumnDefinition>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        ComPtr<IColumnDefinition> valueColumn = XamlHelpers::CreateXamlClass<IColumnDefinition>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        GridLength factSetGridTitleLength = {0, GridUnitType::GridUnitType_Auto};
        GridLength factSetGridValueLength = {1, GridUnitType::GridUnitType_Star};

        RETURN_IF_FAILED(titleColumn->put_Width(factSetGridTitleLength));
        RETURN_IF_FAILED(valueColumn->put_Width(factSetGridValueLength));
        ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
        RETURN_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));
        RETURN_IF_FAILED(columnDefinitions->Append(titleColumn.Get()));
        RETURN_IF_FAILED(columnDefinitions->Append(valueColumn.Get()));

        GridLength factSetGridHeight = {0, GridUnitType::GridUnitType_Auto};
        ABI::AdaptiveNamespace::HeightType heightType;
        RETURN_IF_FAILED(cardElement->get_Height(&heightType));
        if (heightType == ABI::AdaptiveNamespace::HeightType::Stretch)
        {
            factSetGridHeight = {1, GridUnitType::GridUnitType_Star};
        }

        ComPtr<IVector<AdaptiveFact*>> facts;
        RETURN_IF_FAILED(adaptiveFactSet->get_Facts(&facts));
        int currentFact = 0, validFacts = 0;
        XamlHelpers::IterateOverVector<AdaptiveFact, IAdaptiveFact>(
            facts.Get(),
            [xamlGrid, gridStatics, factSetGridHeight, &currentFact, &validFacts, renderContext, renderArgs](IAdaptiveFact* fact) {
                ComPtr<IRowDefinition> factRow = XamlHelpers::CreateXamlClass<IRowDefinition>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RowDefinition));
                RETURN_IF_FAILED(factRow->put_Height(factSetGridHeight));

                ComPtr<IVector<RowDefinition*>> rowDefinitions;
                RETURN_IF_FAILED(xamlGrid->get_RowDefinitions(&rowDefinitions));
                RETURN_IF_FAILED(rowDefinitions->Append(factRow.Get()));

                ComPtr<IAdaptiveFact> localFact(fact);
                ComPtr<IAdaptiveHostConfig> hostConfig;
                RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
                ComPtr<IAdaptiveFactSetConfig> factSetConfig;
                RETURN_IF_FAILED(hostConfig->get_FactSet(&factSetConfig));

                // Get Language
                HString language;
                RETURN_IF_FAILED(localFact->get_Language(language.GetAddressOf()));

                // Create the title xaml textblock and style it from Host options
                ComPtr<IAdaptiveTextConfig> titleTextConfig;
                RETURN_IF_FAILED(factSetConfig->get_Title(&titleTextConfig));

                ComPtr<ITextBlock> titleTextBlock =
                    XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));

                HString factTitle;
                RETURN_IF_FAILED(localFact->get_Title(factTitle.GetAddressOf()));

                RETURN_IF_FAILED(SetXamlInlinesWithTextConfig(
                    renderContext, renderArgs, titleTextConfig.Get(), language.Get(), factTitle.Get(), titleTextBlock.Get()));

                // Create the value xaml textblock and style it from Host options
                ComPtr<IAdaptiveTextConfig> valueTextConfig;
                RETURN_IF_FAILED(factSetConfig->get_Value(&valueTextConfig));

                ComPtr<ITextBlock> valueTextBlock =
                    XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));

                HString factValue;
                RETURN_IF_FAILED(localFact->get_Value(factValue.GetAddressOf()));

                RETURN_IF_FAILED(SetXamlInlinesWithTextConfig(
                    renderContext, renderArgs, valueTextConfig.Get(), language.Get(), factValue.Get(), valueTextBlock.Get()));

                if (factTitle.Get() != nullptr || factValue.Get() != nullptr)
                {
                    // Mark the column container with the current column
                    ComPtr<IFrameworkElement> titleTextBlockAsFrameWorkElement;
                    RETURN_IF_FAILED(titleTextBlock.As(&titleTextBlockAsFrameWorkElement));
                    ComPtr<IFrameworkElement> valueTextBlockAsFrameWorkElement;
                    RETURN_IF_FAILED(valueTextBlock.As(&valueTextBlockAsFrameWorkElement));

                    UINT32 spacing;
                    RETURN_IF_FAILED(factSetConfig->get_Spacing(&spacing));
                    // Add spacing from hostconfig to right margin of title.
                    titleTextBlockAsFrameWorkElement->put_Margin({0, 0, (double)spacing, 0});

                    RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                 L"Adaptive.Fact.Title",
                                                                                 titleTextBlockAsFrameWorkElement.Get()));
                    RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                 L"Adaptive.Fact.Value",
                                                                                 valueTextBlockAsFrameWorkElement.Get()));

                    RETURN_IF_FAILED(gridStatics->SetColumn(titleTextBlockAsFrameWorkElement.Get(), 0));
                    RETURN_IF_FAILED(gridStatics->SetRow(titleTextBlockAsFrameWorkElement.Get(), currentFact));

                    RETURN_IF_FAILED(gridStatics->SetColumn(valueTextBlockAsFrameWorkElement.Get(), 1));
                    RETURN_IF_FAILED(gridStatics->SetRow(valueTextBlockAsFrameWorkElement.Get(), currentFact));

                    // Finally add the column container to the grid, and increment the column count
                    ComPtr<IPanel> gridAsPanel;
                    RETURN_IF_FAILED(xamlGrid.As(&gridAsPanel));
                    ComPtr<IUIElement> titleUIElement;
                    RETURN_IF_FAILED(titleTextBlockAsFrameWorkElement.As(&titleUIElement));
                    ComPtr<IUIElement> valueUIElement;
                    RETURN_IF_FAILED(valueTextBlockAsFrameWorkElement.As(&valueUIElement));

                    XamlHelpers::AppendXamlElementToPanel(titleUIElement.Get(), gridAsPanel.Get());
                    XamlHelpers::AppendXamlElementToPanel(valueUIElement.Get(), gridAsPanel.Get());
                    ++currentFact;
                    ++validFacts;
                }
                return S_OK;
            });

        if (validFacts == 0)
        {
            return S_OK;
        }

        ComPtr<IFrameworkElement> factSetAsFrameworkElement;
        RETURN_IF_FAILED(xamlGrid.As(&factSetAsFrameworkElement));
        RETURN_IF_FAILED(
            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.FactSet", factSetAsFrameworkElement.Get()));

        return xamlGrid.CopyTo(factSetControl);
    }
    CATCH_RETURN;

    HRESULT AdaptiveFactSetRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept
    try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveFactSet, AdaptiveSharedNamespace::FactSet, AdaptiveSharedNamespace::FactSetParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
