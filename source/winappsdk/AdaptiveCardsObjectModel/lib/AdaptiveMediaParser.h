// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::ObjectModel::WinUI3
{
    class AdaptiveMediaParser
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParser>
    {
        AdaptiveRuntime(AdaptiveMediaParser);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP FromJson(
            _In_ ABI::Windows::Data::Json::IJsonObject*,
            _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementParserRegistration* elementParsers,
            _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionParserRegistration* actionParsers,
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning*>* adaptiveWarnings,
            _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement** element) noexcept override;
    };

    ActivatableClass(AdaptiveMediaParser);
}
