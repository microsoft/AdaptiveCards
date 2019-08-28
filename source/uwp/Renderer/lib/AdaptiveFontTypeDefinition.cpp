// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFontTypeDefinition.h"
#include "AdaptiveFontWeightsConfig.h"
#include "AdaptiveFontSizesConfig.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveFontTypeDefinition::RuntimeClassInitialize() noexcept try
    {
        FontTypeDefinition typeDefinition;
        return RuntimeClassInitialize(typeDefinition);
    }
    CATCH_RETURN;

    HRESULT AdaptiveFontTypeDefinition::RuntimeClassInitialize(FontTypeDefinition typeDefinition) noexcept
    {
        RETURN_IF_FAILED(UTF8ToHString(typeDefinition.fontFamily, m_fontFamily.GetAddressOf()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontWeightsConfig>(m_fontWeights.GetAddressOf(), typeDefinition.fontWeights));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontSizesConfig>(m_fontSizes.GetAddressOf(), typeDefinition.fontSizes));
        return S_OK;
    }

    HRESULT AdaptiveFontTypeDefinition::get_FontFamily(_Outptr_ HSTRING* value) { return m_fontFamily.CopyTo(value); }

    HRESULT AdaptiveFontTypeDefinition::put_FontFamily(_In_ HSTRING fontFamily)
    {
        return m_fontFamily.Set(fontFamily);
    }

    HRESULT AdaptiveFontTypeDefinition::get_FontWeights(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig** weightsConfig)
    {
        return m_fontWeights.CopyTo(weightsConfig);
    }

    HRESULT AdaptiveFontTypeDefinition::put_FontWeights(_In_ ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig* weightsConfig)
    {
        m_fontWeights = weightsConfig;
        return S_OK;
    }

    HRESULT AdaptiveFontTypeDefinition::get_FontSizes(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig** sizesConfig)
    {
        return m_fontSizes.CopyTo(sizesConfig);
    }

    HRESULT AdaptiveFontTypeDefinition::put_FontSizes(_In_ ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig* sizesConfig)
    {
        m_fontSizes = sizesConfig;
        return S_OK;
    }
}
