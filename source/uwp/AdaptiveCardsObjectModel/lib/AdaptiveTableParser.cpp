// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveTable.h"
#include "AdaptiveTableParser.h"
#include "ObjectModelUtil.h"

using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation::Collections;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveTableParser::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTableParser::FromJson(_In_ IJsonObject* jsonObject,
                                            _In_ IAdaptiveElementParserRegistration* elementParserRegistration,
                                            _In_ IAdaptiveActionParserRegistration* actionParserRegistration,
                                            _In_ IVector<AdaptiveWarning*>* adaptiveWarnings,
                                            _COM_Outptr_ IAdaptiveCardElement** element) noexcept
    try
    {
        return AdaptiveCards::ObjectModel::Uwp::FromJson<AdaptiveCards::ObjectModel::Uwp::AdaptiveTable, AdaptiveCards::Table, AdaptiveCards::TableParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
