// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Table.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveTableRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRenderer,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParser>
    {
        AdaptiveRuntime(AdaptiveTableRenderer);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement* cardElement,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** tableControl) noexcept override;

        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject*,
                                _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration* elementParsers,
                                _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration* actionParsers,
                                _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>* adaptiveWarnings,
                                _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** element) noexcept override;

    private:
        HRESULT RenderCell(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTableCell* cell,
                           _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                           _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                           _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::Rendering::Uwp::VerticalContentAlignment>* verticalContentAlignment,
                           boolean showGridLines,
                           ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle gridStyle,
                           UINT32 rowNumber,
                           UINT32 columnNumber,
                           _COM_Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** renderedCell);

        HRESULT RenderRow(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTableRow* row,
                          _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveTableColumnDefinition*>* columns,
                          _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                          _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                          _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::Rendering::Uwp::VerticalContentAlignment>* verticalContentAlignment,
                          boolean firstRowAsHeaders,
                          boolean showGridLines,
                          ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle gridStyle,
                          UINT32 rowNumber,
                          _In_ ABI::Windows::UI::Xaml::Controls::IGrid* xamlGrid);
    };

    ActivatableClass(AdaptiveTableRenderer);
}
