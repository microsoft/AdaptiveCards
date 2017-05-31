#include "pch.h"
#include "Util.h"
#include "AdaptiveContainerStyleConfig.h"
#include "AdaptiveBoundaryOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveContainerStyleConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::get_BackgroundColor(Color* value)
    {
        return GetColorFromString(m_sharedContainerStyleConfig.backgroundColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::put_BackgroundColor(Color value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::get_BorderColor(Color* value)
    {
        return GetColorFromString(m_sharedContainerStyleConfig.borderColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::put_BorderColor(Color value)
    {
        return E_NOTIMPL;
    }

    HRESULT AdaptiveContainerStyleConfig::RuntimeClassInitialize(AdaptiveCards::ContainerStyleConfig containerStyleConfig) noexcept
    {
        m_sharedContainerStyleConfig = containerStyleConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::get_BorderThickness(IAdaptiveBoundaryOptions** boundaryOptions)
    {
        return MakeAndInitialize<AdaptiveBoundaryOptions>(boundaryOptions, m_sharedContainerStyleConfig.borderThickness);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::put_BorderThickness(IAdaptiveBoundaryOptions* value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::get_Padding(IAdaptiveBoundaryOptions** boundaryOptions)
    {
        return MakeAndInitialize<AdaptiveBoundaryOptions>(boundaryOptions, m_sharedContainerStyleConfig.padding);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::put_Padding(IAdaptiveBoundaryOptions* value)
    {
        return E_NOTIMPL;
    }


}}
