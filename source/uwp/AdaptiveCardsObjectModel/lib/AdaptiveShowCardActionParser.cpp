// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveShowCardAction.h"
#include "AdaptiveShowCardActionParser.h"
#include "AdaptiveElementParserRegistration.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveShowCardActionParser::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveShowCardActionParser::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement** element) noexcept
    try
    {
        return AdaptiveCards::ObjectModel::Uwp::FromJson<AdaptiveCards::ObjectModel::Uwp::AdaptiveShowCardAction, AdaptiveCards::ShowCardAction, AdaptiveCards::ShowCardActionParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;

}
