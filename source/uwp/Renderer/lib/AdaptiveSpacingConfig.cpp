#include "pch.h"
#include "AdaptiveSpacingConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveSpacingConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveSpacingConfig::RuntimeClassInitialize(SpacingConfig spacingConfig) noexcept try
    {
        m_sharedSpacingConfig = spacingConfig;
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingConfig::get_Small(UINT32* smallSpacing)
    {
        *smallSpacing = m_sharedSpacingConfig.smallSpacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingConfig::put_Small(UINT32 smallSpacing)
    {
        m_sharedSpacingConfig.smallSpacing = smallSpacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingConfig::get_Default(UINT32* smallSpacing)
    {
        *smallSpacing = m_sharedSpacingConfig.defaultSpacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingConfig::put_Default(UINT32 smallSpacing)
    {
        m_sharedSpacingConfig.smallSpacing = smallSpacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingConfig::get_Medium(UINT32* mediumSpacing)
    {
        *mediumSpacing = m_sharedSpacingConfig.mediumSpacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingConfig::put_Medium(UINT32 mediumSpacing)
    {
        m_sharedSpacingConfig.mediumSpacing = mediumSpacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingConfig::get_Large(UINT32* largeSpacing)
    {
        *largeSpacing = m_sharedSpacingConfig.largeSpacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingConfig::put_Large(UINT32 largeSpacing)
    {
        m_sharedSpacingConfig.largeSpacing = largeSpacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingConfig::get_ExtraLarge(UINT32* extraLargeSpacing)
    {
        *extraLargeSpacing = m_sharedSpacingConfig.extraLargeSpacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingConfig::put_ExtraLarge(UINT32 extraLargeSpacing)
    {
        m_sharedSpacingConfig.extraLargeSpacing = extraLargeSpacing;
        return S_OK;
    }
}
}
