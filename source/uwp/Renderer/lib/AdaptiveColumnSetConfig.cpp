#include "pch.h"
#include "AdaptiveColumnSetConfig.h"
#include "AdaptiveSeparationConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveColumnSetConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveColumnSetConfig::RuntimeClassInitialize(ColumnSetConfig columnSetConfig) noexcept
    {
        m_sharedColumnSetConfig = columnSetConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSetConfig::get_Separation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedColumnSetConfig.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSetConfig::put_Separation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }
}
}
