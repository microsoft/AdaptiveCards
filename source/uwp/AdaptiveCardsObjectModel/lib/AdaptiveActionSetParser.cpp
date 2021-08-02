// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveActionSetParser.h"

#include "AdaptiveActionSet.h"
#include "AdaptiveElementParserRegistration.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveActionSetParser::RuntimeClassInitialize() noexcept { return S_OK; }

    HRESULT AdaptiveActionSetParser::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement** element) noexcept
    try
    {
        return AdaptiveCards::ObjectModel::Uwp::FromJson<AdaptiveCards::ObjectModel::Uwp::AdaptiveActionSet, AdaptiveCards::ActionSet, AdaptiveCards::ActionSetParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;

}
