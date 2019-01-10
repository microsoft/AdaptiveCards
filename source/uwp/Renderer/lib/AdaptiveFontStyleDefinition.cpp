#include "pch.h"
#include "AdaptiveFontStyleDefinition.h"
#include "AdaptiveFontWeightsConfig.h"
#include "AdaptiveFontSizesConfig.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveFontStyleDefinition::RuntimeClassInitialize() noexcept try
    {
        FontStyleDefinition styleDefinition;
        return RuntimeClassInitialize(styleDefinition);
    }
    CATCH_RETURN;

    HRESULT AdaptiveFontStyleDefinition::RuntimeClassInitialize(FontStyleDefinition styleDefinition) noexcept
    {
        RETURN_IF_FAILED(UTF8ToHString(styleDefinition.fontFamily, m_fontFamily.GetAddressOf()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontWeightsConfig>(m_fontWeights.GetAddressOf(), styleDefinition.fontWeights));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontSizesConfig>(m_fontSizes.GetAddressOf(), styleDefinition.fontSizes));
        return S_OK;
    }

    HRESULT AdaptiveFontStyleDefinition::get_FontFamily(_Outptr_ HSTRING* value) { return m_fontFamily.CopyTo(value); }

    HRESULT AdaptiveFontStyleDefinition::put_FontFamily(_In_ HSTRING fontFamily)
    {
        return m_fontFamily.Set(fontFamily);
    }

    HRESULT AdaptiveFontStyleDefinition::get_FontWeights(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig** weightsConfig)
    {
        return m_fontWeights.CopyTo(weightsConfig);
    }

    HRESULT AdaptiveFontStyleDefinition::put_FontWeights(_In_ ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig* weightsConfig)
    {
        m_fontWeights = weightsConfig;
        return S_OK;
    }

    HRESULT AdaptiveFontStyleDefinition::get_FontSizes(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig** sizesConfig)
    {
        return m_fontSizes.CopyTo(sizesConfig);
    }

    HRESULT AdaptiveFontStyleDefinition::put_FontSizes(_In_ ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig* sizesConfig)
    {
        m_fontSizes = sizesConfig;
        return S_OK;
    }
}
