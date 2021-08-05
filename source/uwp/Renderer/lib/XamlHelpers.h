// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "WholeItemsPanel.h"

namespace AdaptiveCards::Rendering::Uwp::XamlHelpers
{
    template<typename T> Microsoft::WRL::ComPtr<T> CreateABIClass(Microsoft::WRL::Wrappers::HStringReference className)
    {
        Microsoft::WRL::ComPtr<IInspectable> inspectableClass;
        THROW_IF_FAILED(RoActivateInstance(className.Get(), inspectableClass.ReleaseAndGetAddressOf()));

        Microsoft::WRL::ComPtr<T> result;
        THROW_IF_FAILED(inspectableClass.As<T>(&result));
        return result;
    }

    inline Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IBrush> GetSolidColorBrush(_In_ ABI::Windows::UI::Color color)
    {
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::ISolidColorBrush> solidColorBrush =
            CreateABIClass<ABI::Windows::UI::Xaml::Media::ISolidColorBrush>(
                Microsoft::WRL::Wrappers::HStringReference(RuntimeClass_Windows_UI_Xaml_Media_SolidColorBrush));
        THROW_IF_FAILED(solidColorBrush->put_Color(color));
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IBrush> solidColorBrushAsBrush;
        THROW_IF_FAILED(solidColorBrush.As(&solidColorBrushAsBrush));
        return solidColorBrushAsBrush;
    }

    HRESULT SetStyleFromResourceDictionary(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                           HSTRING resourceName,
                                           _In_ ABI::Windows::UI::Xaml::IFrameworkElement* frameworkElement) noexcept;

    HRESULT SetStyleFromResourceDictionary(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                           const wchar_t* resourceName,
                                           _In_ ABI::Windows::UI::Xaml::IFrameworkElement* frameworkElement) noexcept;

    Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> CreateSeparator(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                                                               UINT spacing,
                                                                               UINT separatorThickness,
                                                                               ABI::Windows::UI::Color separatorColor,
                                                                               bool isHorizontal = true);

    template<typename T>
    HRESULT TryGetResourceFromResourceDictionaries(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* resourceDictionary,
                                                   HSTRING resourceName,
                                                   _COM_Outptr_result_maybenull_ T** style) noexcept
    {
        if (resourceDictionary == nullptr)
        {
            return E_INVALIDARG;
        }

        *style = nullptr;
        try
        {
            // Get a resource key for the requested style that we can use for ResourceDictionary Lookups
            ComPtr<IPropertyValueStatics> propertyValueStatics;
            THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(),
                                                 &propertyValueStatics));
            ComPtr<IInspectable> resourceKey;
            THROW_IF_FAILED(propertyValueStatics->CreateString(resourceName, resourceKey.GetAddressOf()));

            // Search for the named resource
            ComPtr<IResourceDictionary> strongDictionary = resourceDictionary;
            ComPtr<IInspectable> dictionaryValue;
            ComPtr<IMap<IInspectable*, IInspectable*>> resourceDictionaryMap;

            boolean hasKey{};
            if (SUCCEEDED(strongDictionary.As(&resourceDictionaryMap)) &&
                SUCCEEDED(resourceDictionaryMap->HasKey(resourceKey.Get(), &hasKey)) && hasKey &&
                SUCCEEDED(resourceDictionaryMap->Lookup(resourceKey.Get(), dictionaryValue.GetAddressOf())))
            {
                ComPtr<T> resourceToReturn;
                if (SUCCEEDED(dictionaryValue.As(&resourceToReturn)))
                {
                    THROW_IF_FAILED(resourceToReturn.CopyTo(style));
                    return S_OK;
                }
            }
        }
        catch (...)
        {
        }
        return E_FAIL;
    }

    template<typename T>
    HRESULT TryGetResourceFromResourceDictionaries(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* resourceDictionary,
                                                   const wchar_t* resourceName,
                                                   _COM_Outptr_result_maybenull_ T** style) noexcept
    {
        return TryGetResourceFromResourceDictionaries<T>(resourceDictionary, HStringReference(resourceName).Get(), style);
    }

    HRESULT SetSeparatorVisibility(_In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel);

    HRESULT HandleColumnWidth(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveColumn* column,
                              boolean isVisible,
                              _In_ ABI::Windows::UI::Xaml::Controls::IColumnDefinition* columnDefinition);

    HRESULT HandleTableColumnWidth(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTableColumnDefinition* column,
                                   _In_ ABI::Windows::UI::Xaml::Controls::IColumnDefinition* columnDefinition);

    template<typename T>
    void AppendXamlElementToPanel(_In_ T* xamlElement,
                                  _In_ ABI::Windows::UI::Xaml::Controls::IPanel* panel,
                                  ABI::AdaptiveCards::ObjectModel::Uwp::HeightType heightType = ABI::AdaptiveCards::ObjectModel::Uwp::HeightType::Auto)
    {
        if (!xamlElement)
        {
            return;
        }

        Microsoft::WRL::ComPtr<T> localXamlElement(xamlElement);

        ComPtr<IUIElement> elementToAppend;
        THROW_IF_FAILED(localXamlElement.As(&elementToAppend));

        ComPtr<IVector<UIElement*>> panelChildren;
        THROW_IF_FAILED(panel->get_Children(panelChildren.ReleaseAndGetAddressOf()));

        THROW_IF_FAILED(panelChildren->Append(elementToAppend.Get()));

        if (heightType == ABI::AdaptiveCards::ObjectModel::Uwp::HeightType::Stretch)
        {
            ComPtr<IPanel> spPanel(panel);
            ComPtr<IWholeItemsPanel> wholeItemsPanel;
            if (SUCCEEDED(spPanel.As(&wholeItemsPanel)))
            {
                ComPtr<WholeItemsPanel> wholeItemsPanelObj = PeekInnards<WholeItemsPanel>(wholeItemsPanel);
                wholeItemsPanelObj->AddElementToStretchablesList(elementToAppend.Get());
            }
        }
    }

    template<typename T> void SetToggleValue(_In_ T* item, boolean isChecked)
    {
        ComPtr<IPropertyValueStatics> propertyValueStatics;
        ABI::Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(),
                                                       &propertyValueStatics);

        ComPtr<IPropertyValue> propertyValue;
        propertyValueStatics->CreateBoolean(isChecked, &propertyValue);

        ComPtr<ABI::Windows::Foundation::IReference<bool>> boolProperty;
        propertyValue.As(&boolProperty);

        ComPtr<T> localItem(item);
        ComPtr<IToggleButton> toggleButton;
        THROW_IF_FAILED(localItem.As(&toggleButton));
        THROW_IF_FAILED(toggleButton->put_IsChecked(boolProperty.Get()));
    }

    template<typename T> void GetToggleValue(_In_ T* item, _Out_ boolean* isChecked)
    {
        ComPtr<T> localItem(item);
        ComPtr<IToggleButton> toggleButton;
        THROW_IF_FAILED(localItem.As(&toggleButton));

        ComPtr<IReference<bool>> isCheckedReference;
        THROW_IF_FAILED(toggleButton->get_IsChecked(&isCheckedReference));

        if (isCheckedReference != nullptr)
        {
            THROW_IF_FAILED(isCheckedReference->get_Value(isChecked));
        }
        else
        {
            *isChecked = false;
        }
    }

    template<typename T> void SetContent(_In_ T* item, _In_ HSTRING contentString, boolean wrap)
    {
        ComPtr<T> localItem(item);
        ComPtr<IContentControl> contentControl;
        THROW_IF_FAILED(localItem.As(&contentControl));

        ComPtr<ITextBlock> content =
            XamlHelpers::CreateABIClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
        THROW_IF_FAILED(content->put_Text(contentString));

        if (wrap)
        {
            THROW_IF_FAILED(content->put_TextWrapping(TextWrapping::TextWrapping_WrapWholeWords));
        }
        THROW_IF_FAILED(contentControl->put_Content(content.Get()));
    }

    template<typename T> void SetContent(T* item, HSTRING contentString) { SetContent(item, contentString, false); }

    template<typename T>
    void AddRow(_In_ T* item, _In_ ABI::Windows::UI::Xaml::Controls::IGrid* grid, ABI::Windows::UI::Xaml::GridLength rowHeight)
    {
        ComPtr<ABI::Windows::UI::Xaml::Controls::IGrid> localGrid(grid);

        ComPtr<IVector<RowDefinition*>> rowDefinitions;
        THROW_IF_FAILED(localGrid->get_RowDefinitions(&rowDefinitions));

        unsigned int rowIndex;
        THROW_IF_FAILED(rowDefinitions->get_Size(&rowIndex));
        ComPtr<IGridStatics> gridStatics;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));
        Microsoft::WRL::ComPtr<T> localItem(item);
        ComPtr<IFrameworkElement> localItemAsFrameworkElement;
        THROW_IF_FAILED(localItem.As(&localItemAsFrameworkElement));
        gridStatics->SetRow(localItemAsFrameworkElement.Get(), rowIndex);

        ComPtr<IRowDefinition> rowDefinition =
            XamlHelpers::CreateABIClass<IRowDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RowDefinition));
        THROW_IF_FAILED(rowDefinition->put_Height(rowHeight));
        THROW_IF_FAILED(rowDefinitions->Append(rowDefinition.Get()));

        ComPtr<ABI::Windows::UI::Xaml::Controls::IPanel> localPanel;
        THROW_IF_FAILED(localGrid.As(&localPanel));
        XamlHelpers::AppendXamlElementToPanel(item, localPanel.Get());
    }

    HRESULT HandleStylingAndPadding(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveContainerBase* adaptiveContainer,
                                    _In_ ABI::Windows::UI::Xaml::Controls::IBorder* containerBorder,
                                    _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                    _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                                    _Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle* containerStyle);

    bool SupportsInteractivity(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig);

    template<typename T>
    void SetVerticalContentAlignmentToChildren(_In_ T* container, _In_ ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment verticalContentAlignment)
    {
        ComPtr<T> localContainer(container);
        ComPtr<IWholeItemsPanel> containerAsPanel;
        THROW_IF_FAILED(localContainer.As(&containerAsPanel));

        ComPtr<WholeItemsPanel> panel = PeekInnards<WholeItemsPanel>(containerAsPanel);
        panel->SetVerticalContentAlignment(verticalContentAlignment);
    }

    HRESULT RenderInputLabel(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement* adaptiveInputElement,
                             _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                             _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                             _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** labelControl);

    HRESULT RenderInputErrorMessage(ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement* adaptiveInputElement,
                                    ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                    ABI::Windows::UI::Xaml::IUIElement** errorMessageControl);

    HRESULT CreateValidationBorder(ABI::Windows::UI::Xaml::IUIElement* childElement,
                                   ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                   ABI::Windows::UI::Xaml::Controls::IBorder** elementWithBorder);

    HRESULT HandleLabelAndErrorMessage(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement* adaptiveInput,
                                       _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                       _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                                       _Out_ ABI::Windows::UI::Xaml::IUIElement** inputLayout);

    HRESULT HandleInputLayoutAndValidation(ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement* adaptiveInput,
                                           ABI::Windows::UI::Xaml::IUIElement* inputUIElement,
                                           boolean hasTypeSpecificValidation,
                                           ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                           ABI::Windows::UI::Xaml::IUIElement** inputLayout,
                                           ABI::Windows::UI::Xaml::Controls::IBorder** validationBorderOut);

    template<typename TXamlControl>
    HRESULT SetXamlHeaderFromLabel(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement* adaptiveInputElement,
                                   _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                   _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                                   _In_ TXamlControl* xamlControl)
    {
        ComPtr<IUIElement> labelControl;
        RETURN_IF_FAILED(RenderInputLabel(adaptiveInputElement, renderContext, renderArgs, &labelControl));

        if (labelControl != nullptr)
        {
            ComPtr<IInspectable> labelControlAsInspectable;
            RETURN_IF_FAILED(labelControl.As(&labelControlAsInspectable));
            RETURN_IF_FAILED(xamlControl->put_Header(labelControlAsInspectable.Get()));
        }

        return S_OK;
    }

    HRESULT AddHandledTappedEvent(_In_ ABI::Windows::UI::Xaml::IUIElement* uiElement);

    void ApplyBackgroundToRoot(_In_ ABI::Windows::UI::Xaml::Controls::IPanel* rootPanel,
                               _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveBackgroundImage* backgroundImage,
                               _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                               _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs);

    HRESULT AddRenderedControl(_In_ ABI::Windows::UI::Xaml::IUIElement* newControl,
                               _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* element,
                               _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
                               _In_ ABI::Windows::UI::Xaml::IUIElement* separator,
                               _In_ ABI::Windows::UI::Xaml::Controls::IColumnDefinition* columnDefinition,
                               std::function<void(ABI::Windows::UI::Xaml::IUIElement* child)> childCreatedCallback);

    HRESULT RenderFallback(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* currentElement,
                           _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                           _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                           _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result,
                           _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement** renderedElement);

    void GetSeparationConfigForElement(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* element,
                                       _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                       _Out_ UINT* spacing,
                                       _Out_ UINT* separatorThickness,
                                       _Out_ ABI::Windows::UI::Color* separatorColor,
                                       _Out_ bool* needsSeparator);

    inline HRESULT WarnFallbackString(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                      const std::string& warning)
    {
        HString warningMsg;
        RETURN_IF_FAILED(UTF8ToHString(warning, warningMsg.GetAddressOf()));

        RETURN_IF_FAILED(renderContext->AddWarning(ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode::PerformingFallback,
                                                   warningMsg.Get()));
        return S_OK;
    }

    inline HRESULT WarnForFallbackContentElement(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                                 _In_ HSTRING parentElementType,
                                                 _In_ HSTRING fallbackElementType)
    try
    {
        std::string warning = "Performing fallback for element of type \"";
        warning.append(HStringToUTF8(parentElementType));
        warning.append("\" (fallback element type \"");
        warning.append(HStringToUTF8(fallbackElementType));
        warning.append("\")");

        return WarnFallbackString(renderContext, warning);
    }
    CATCH_RETURN;

    inline HRESULT WarnForFallbackDrop(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                       _In_ HSTRING elementType)
    try
    {
        std::string warning = "Dropping element of type \"";
        warning.append(HStringToUTF8(elementType));
        warning.append("\" for fallback");

        return WarnFallbackString(renderContext, warning);
    }
    CATCH_RETURN;

    void AddSeparatorIfNeeded(int& currentElement,
                              _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* element,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
                              _Outptr_ ABI::Windows::UI::Xaml::IUIElement** addedSeparator);

    HRESULT SetAutoImageSize(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* imageControl,
                             _In_ IInspectable* parentElement,
                             _In_ ABI::Windows::UI::Xaml::Media::Imaging::IBitmapSource* imageSource,
                             bool setVisible);

    HRESULT ApplyMarginToXamlElement(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                     _In_ ABI::Windows::UI::Xaml::IFrameworkElement* element) noexcept;
}
