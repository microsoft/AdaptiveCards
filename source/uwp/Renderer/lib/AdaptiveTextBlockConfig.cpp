#include "pch.h"
#include "AdaptiveTextBlockConfig.h"
#include "AdaptiveSeparationConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveTextBlockConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveTextBlockConfig::RuntimeClassInitialize(TextBlockConfig textBlockConfig) noexcept
    {
        m_sharedTextBlockConfig = textBlockConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockConfig::get_SmallSeparation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedTextBlockConfig.smallSeparation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockConfig::put_SmallSeparation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockConfig::get_NormalSeparation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedTextBlockConfig.normalSeparation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockConfig::put_NormalSeparation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockConfig::get_MediumSeparation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedTextBlockConfig.mediumSeparation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockConfig::put_MediumSeparation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockConfig::get_LargeSeparation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedTextBlockConfig.largeSeparation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockConfig::put_LargeSeparation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockConfig::get_ExtraLargeSeparation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedTextBlockConfig.extraLargeSeparation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockConfig::put_ExtraLargeSeparation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }
}
}
