// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Column.h"

namespace AdaptiveCards::ObjectModel::WinUI3
{
    class AdaptiveColumnParser
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParser>
    {
        AdaptiveRuntime(AdaptiveColumnParser);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP FromJson(ABI::Windows::Data::Json::IJsonObject*,
                                ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParserRegistration* elementParsers,
                                ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParserRegistration* actionParsers,
                                ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning*>* adaptiveWarnings,
                                ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement** element) noexcept override;
    };

    ActivatableClass(AdaptiveColumnParser);
}
