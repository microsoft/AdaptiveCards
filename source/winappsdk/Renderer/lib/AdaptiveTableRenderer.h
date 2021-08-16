// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Table.h"

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveTableRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveElementRenderer>
    {
        AdaptiveRuntime(AdaptiveTableRenderer);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement* cardElement,
                              _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** tableControl) noexcept override;

    private:
        HRESULT RenderCell(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTableCell* cell,
                           _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                           _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                           _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>* verticalContentAlignment,
                           boolean showGridLines,
                           ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle gridStyle,
                           UINT32 rowNumber,
                           UINT32 columnNumber,
                           _COM_Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** renderedCell);

        HRESULT RenderRow(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTableRow* row,
                          _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTableColumnDefinition*>* columns,
                          _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                          _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                          _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>* verticalContentAlignment,
                          boolean firstRowAsHeaders,
                          boolean showGridLines,
                          ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle gridStyle,
                          UINT32 rowNumber,
                          _In_ ABI::Windows::UI::Xaml::Controls::IGrid* xamlGrid);
    };

    ActivatableClass(AdaptiveTableRenderer);
}
