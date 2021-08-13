// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Table.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class AdaptiveTableParser
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParser>
    {
        AdaptiveRuntime(AdaptiveTableParser);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP FromJson(
            _In_ ABI::Windows::Data::Json::IJsonObject*,
            _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParserRegistration* elementParsers,
            _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParserRegistration* actionParsers,
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning*>* adaptiveWarnings,
            _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement** element) noexcept override;
    };

    ActivatableClass(AdaptiveTableParser);
}
