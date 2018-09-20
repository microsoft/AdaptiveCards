#include "pch.h"
#include "AdaptiveFactSetConfig.h"
#include "AdaptiveTextConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

AdaptiveNamespaceStart
    HRESULT AdaptiveFactSetConfig::RuntimeClassInitialize() noexcept try
    {
        FactSetConfig factSetConfig;
        return RuntimeClassInitialize(factSetConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveFactSetConfig::RuntimeClassInitialize(FactSetConfig factSetConfig) noexcept
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveTextConfig>(m_title.GetAddressOf(), factSetConfig.title));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveTextConfig>(m_value.GetAddressOf(), factSetConfig.value));
        m_spacing = factSetConfig.spacing;

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSetConfig::get_Title(ABI::AdaptiveNamespace::IAdaptiveTextConfig** titleTextConfig)
    {
        return m_title.CopyTo(titleTextConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSetConfig::put_Title(ABI::AdaptiveNamespace::IAdaptiveTextConfig* titleTextConfig)
    {
        m_title = titleTextConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSetConfig::get_Value(ABI::AdaptiveNamespace::IAdaptiveTextConfig** valueTextConfig)
    {
        return m_value.CopyTo(valueTextConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSetConfig::put_Value(ABI::AdaptiveNamespace::IAdaptiveTextConfig* valueTextConfig)
    {
        m_value = valueTextConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSetConfig::get_Spacing(UINT32 * value)
    {
        *value = m_spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSetConfig::put_Spacing(UINT32 value)
    {
        m_spacing = value;
        return S_OK;
    }
AdaptiveNamespaceEnd
