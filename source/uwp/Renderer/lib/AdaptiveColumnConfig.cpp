#include "pch.h"
#include "AdaptiveColumnConfig.h"
#include "AdaptiveSeparationConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveColumnConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveColumnConfig::RuntimeClassInitialize(ColumnConfig columnConfig) noexcept
    {
        m_sharedColumnConfig = columnConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnConfig::get_Separation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedColumnConfig.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnConfig::put_Separation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }
}
}
