#include "pch.h"
#include "AdaptiveTextBlockOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveTextBlockOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveTextBlockOptions::RuntimeClassInitialize(TextBlockOptions textBlockOptions) noexcept
    {
        m_sharedTextBlockOptions = textBlockOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockOptions::get_SmallSeparation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedTextBlockOptions.smallSeparation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockOptions::put_SmallSeparation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockOptions::get_NormalSeparation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedTextBlockOptions.normalSeparation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockOptions::put_NormalSeparation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockOptions::get_MediumSeparation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedTextBlockOptions.mediumSeparation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockOptions::put_MediumSeparation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockOptions::get_LargeSeparation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedTextBlockOptions.largeSeparation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockOptions::put_LargeSeparation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockOptions::get_ExtraLargeSeparation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedTextBlockOptions.extraLargeSeparation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlockOptions::put_ExtraLargeSeparation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}
}
