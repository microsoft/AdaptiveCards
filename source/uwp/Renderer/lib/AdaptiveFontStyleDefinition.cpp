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

    _Use_decl_annotations_ HRESULT AdaptiveFontStyleDefinition::get_FontFamily(HSTRING* value)
    {
        return m_fontFamily.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontStyleDefinition::put_FontFamily(HSTRING fontFamily)
    {
        return m_fontFamily.Set(fontFamily);
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontStyleDefinition::get_FontWeights(ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig** weightsConfig)
    {
        return m_fontWeights.CopyTo(weightsConfig);
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontStyleDefinition::put_FontWeights(ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig* weightsConfig)
    {
        m_fontWeights = weightsConfig;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontStyleDefinition::get_FontSizes(ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig** sizesConfig)
    {
        return m_fontSizes.CopyTo(sizesConfig);
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontStyleDefinition::put_FontSizes(ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig* sizesConfig)
    {
        m_fontSizes = sizesConfig;
        return S_OK;
    }
}
