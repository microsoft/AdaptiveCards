#include "pch.h"
#include "AdaptiveContainerStyleDefinition.h"
#include "AdaptiveColorsConfig.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveContainerStyleDefinition::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveContainerStyleDefinition::RuntimeClassInitialize(ContainerStyleDefinition styleDefinition) noexcept
    {
        m_sharedContainerStyleDefinition = styleDefinition;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleDefinition::get_BackgroundColor(ABI::Windows::UI::Color* value)
    {
        return GetColorFromString(m_sharedContainerStyleDefinition.backgroundColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStyleDefinition::put_BackgroundColor(ABI::Windows::UI::Color /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStyleDefinition::get_ForegroundColors(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorsConfig** colorsConfig)
    {
        return MakeAndInitialize<AdaptiveColorsConfig>(colorsConfig, m_sharedContainerStyleDefinition.foregroundColors);
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStyleDefinition::put_ForegroundColors(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorsConfig*)
    {
        return E_NOTIMPL;
    }
}
}
