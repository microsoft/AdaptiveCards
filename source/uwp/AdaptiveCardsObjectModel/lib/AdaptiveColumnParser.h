// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Column.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class AdaptiveColumnParser
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParser>
    {
        AdaptiveRuntime(AdaptiveColumnParser);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP FromJson(ABI::Windows::Data::Json::IJsonObject*,
                                ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParserRegistration* elementParsers,
                                ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParserRegistration* actionParsers,
                                ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning*>* adaptiveWarnings,
                                ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement** element) noexcept override;
    };

    ActivatableClass(AdaptiveColumnParser);
}
