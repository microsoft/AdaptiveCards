// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Util.h"
#include "AdaptiveCardConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::UI;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveCardConfig::RuntimeClassInitialize() noexcept
    try
    {
        AdaptiveCards::AdaptiveCardConfig cardConfig;
        return RuntimeClassInitialize(cardConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveCardConfig::RuntimeClassInitialize(AdaptiveCards::AdaptiveCardConfig adaptiveCardConfig) noexcept
    {
        m_allowCustomStyle = adaptiveCardConfig.allowCustomStyle;
        return S_OK;
    }

    HRESULT AdaptiveCardConfig::get_AllowCustomStyle(_Out_ boolean* allowCustomStyle)
    {
        *allowCustomStyle = m_allowCustomStyle;
        return S_OK;
    }

    HRESULT AdaptiveCardConfig::put_AllowCustomStyle(boolean allowCustomStyle)
    {
        m_allowCustomStyle = allowCustomStyle;
        return S_OK;
    }
}
