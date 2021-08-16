// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.ObjectModel.WinUI3.h"

namespace AdaptiveCards::ObjectModel::WinUI3
{
    class AdaptiveOpenUrlActionParser
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParser>
    {
        AdaptiveRuntime(AdaptiveOpenUrlActionParser);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP FromJson(
            _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
            _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParserRegistration* elementParserRegistration,
            _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParserRegistration* actionParserRegistration,
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning*>* adaptiveWarnings,
            _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement** element) noexcept override;
    };

    ActivatableClass(AdaptiveOpenUrlActionParser);
}
