#include "pch.h"
#include "Util.h"
#include "AdaptiveContainerStyleConfig.h"
#include "AdaptiveSpacingDefinition.h"

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
    HRESULT AdaptiveContainerStyleConfig::get_BackgroundColor(ABI::Windows::UI::Color* value)
    {
        return GetColorFromString(m_sharedContainerStyleConfig.backgroundColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::put_BackgroundColor(ABI::Windows::UI::Color /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::get_BorderColor(ABI::Windows::UI::Color* value)
    {
        return GetColorFromString(m_sharedContainerStyleConfig.borderColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::put_BorderColor(ABI::Windows::UI::Color /*value*/)
    {
        return E_NOTIMPL;
    }

    HRESULT AdaptiveContainerStyleConfig::RuntimeClassInitialize(AdaptiveCards::ContainerStyleConfig containerStyleConfig) noexcept
    {
        m_sharedContainerStyleConfig = containerStyleConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::get_BorderThickness(IAdaptiveSpacingDefinition** spacingDefinition)
    {
        return MakeAndInitialize<AdaptiveSpacingDefinition>(spacingDefinition, m_sharedContainerStyleConfig.borderThickness);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::put_BorderThickness(IAdaptiveSpacingDefinition* /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::get_Padding(IAdaptiveSpacingDefinition** spacingDefinition)
    {
        return MakeAndInitialize<AdaptiveSpacingDefinition>(spacingDefinition, m_sharedContainerStyleConfig.padding);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleConfig::put_Padding(IAdaptiveSpacingDefinition* /*value*/)
    {
        return E_NOTIMPL;
    }


}}
