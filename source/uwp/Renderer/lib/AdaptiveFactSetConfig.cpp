#include "pch.h"
#include "AdaptiveFactSetConfig.h"
#include "AdaptiveTextConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveFactSetConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveFactSetConfig::RuntimeClassInitialize(FactSetConfig factSetConfig) noexcept
    {
        m_sharedFactSetConfig = factSetConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSetConfig::get_Title(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig** titleTextConfig)
    {
        return MakeAndInitialize<AdaptiveTextConfig>(titleTextConfig, m_sharedFactSetConfig.title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSetConfig::put_Title(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig* /*titleTextConfig*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSetConfig::get_Value(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig** valueTextConfig)
    {
        return MakeAndInitialize<AdaptiveTextConfig>(valueTextConfig, m_sharedFactSetConfig.value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSetConfig::put_Value(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig* /*valueTextConfig*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSetConfig::get_Spacing(UINT32 * value)
    {
        *value = m_sharedFactSetConfig.spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSetConfig::put_Spacing(UINT32 value)
    {
        m_sharedFactSetConfig.spacing = value;
        return S_OK;
    }
}
}
