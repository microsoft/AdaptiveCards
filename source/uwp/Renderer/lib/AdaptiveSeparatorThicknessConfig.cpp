#include "pch.h"
#include "AdaptiveSeparatorThicknessConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveSeparatorThicknessConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveSeparatorThicknessConfig::RuntimeClassInitialize(SeparatorThicknessConfig SeparatorThicknessConfig) noexcept try
    {
        m_sharedSeparatorThicknessConfig = SeparatorThicknessConfig;
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
        HRESULT AdaptiveSeparatorThicknessConfig::get_Default(UINT32* smallSeparatorThickness)
    {
        *smallSeparatorThickness = m_sharedSeparatorThicknessConfig.defaultSeparatorThickness;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveSeparatorThicknessConfig::put_Default(UINT32 smallSeparatorThickness)
    {
        m_sharedSeparatorThicknessConfig.defaultSeparatorThickness = smallSeparatorThickness;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparatorThicknessConfig::get_Thick(UINT32* thickSeparatorThickness)
    {
        *thickSeparatorThickness = m_sharedSeparatorThicknessConfig.thickSeparatorThickness;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparatorThicknessConfig::put_Thick(UINT32 thickSeparatorThickness)
    {
        m_sharedSeparatorThicknessConfig.thickSeparatorThickness = thickSeparatorThickness;
        return S_OK;
    }
}
}
