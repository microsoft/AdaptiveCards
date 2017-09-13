#include "pch.h"
#include "AdaptiveContainerConfig.h"
#include "AdaptiveContainerStyleConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveContainerConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveContainerConfig::RuntimeClassInitialize(ContainerConfig containerConfig) noexcept
    {
        m_sharedContainerConfig = containerConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerConfig::get_Normal(IAdaptiveContainerStyleConfig** containerStyleConfig)
    {
        return MakeAndInitialize<AdaptiveContainerStyleConfig>(containerStyleConfig, m_sharedContainerConfig.normal);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerConfig::put_Normal(IAdaptiveContainerStyleConfig*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerConfig::get_Emphasis(IAdaptiveContainerStyleConfig** containerStyleConfig)
    {
        return MakeAndInitialize<AdaptiveContainerStyleConfig>(containerStyleConfig, m_sharedContainerConfig.emphasis);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerConfig::put_Emphasis(IAdaptiveContainerStyleConfig*)
    {
        return E_NOTIMPL;
    }
}
}
