// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveExecuteActionRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionRenderer,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParser>
    {
        AdaptiveRuntime(AdaptiveExecuteActionRenderer);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement* action,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept override;

        IFACEMETHODIMP
        FromJson(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
                 _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
                 _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
                 _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>* adaptiveWarnings,
                 _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement** element) noexcept override;
    };

    ActivatableClass(AdaptiveExecuteActionRenderer);
}
