// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ActionSet.h"

namespace AdaptiveCards::ObjectModel::WinAppSDK
{
    class AdaptiveActionSetParser
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveElementParser>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_ObjectModel_WinAppSDK_AdaptiveActionSetParser, BaseTrust);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP FromJson(_In_ ABI::Windows::Data::Json::IJsonObject*,
                                _In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveElementParserRegistration* elementParsers,
                                _In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveActionParserRegistration* actionParsers,
                                _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinAppSDK::AdaptiveWarning*>* adaptiveWarnings,
                                _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveCardElement** element) noexcept;
    };

    ActivatableClass(AdaptiveActionSetParser);
}
