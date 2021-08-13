// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Table.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveTableRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRenderer>
    {
        AdaptiveRuntime(AdaptiveTableRenderer);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* cardElement,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** tableControl) noexcept override;

    private:
        HRESULT RenderCell(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTableCell* cell,
                           _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                           _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                           _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>* verticalContentAlignment,
                           boolean showGridLines,
                           ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle gridStyle,
                           UINT32 rowNumber,
                           UINT32 columnNumber,
                           _COM_Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** renderedCell);

        HRESULT RenderRow(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTableRow* row,
                          _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableColumnDefinition*>* columns,
                          _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                          _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                          _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>* verticalContentAlignment,
                          boolean firstRowAsHeaders,
                          boolean showGridLines,
                          ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle gridStyle,
                          UINT32 rowNumber,
                          _In_ ABI::Windows::UI::Xaml::Controls::IGrid* xamlGrid);
    };

    ActivatableClass(AdaptiveTableRenderer);
}
