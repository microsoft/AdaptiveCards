#include "pch.h"
#include "AdaptiveFontStyleDefinition.h"
#include "AdaptiveFontStylesDefinition.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveFontStylesDefinition::RuntimeClassInitialize() noexcept try
    {
        FontStylesDefinition stylesDefinition;
        return RuntimeClassInitialize(stylesDefinition);
    }
    CATCH_RETURN;

    HRESULT AdaptiveFontStylesDefinition::RuntimeClassInitialize(FontStylesDefinition stylesDefinition) noexcept
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontStyleDefinition>(m_default.GetAddressOf(), stylesDefinition.defaultStyle));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontStyleDefinition>(m_display.GetAddressOf(), stylesDefinition.displayStyle));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontStyleDefinition>(m_monospace.GetAddressOf(), stylesDefinition.monospaceStyle));

        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontStylesDefinition::get_Default(ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition** value)
    {
        return m_default.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontStylesDefinition::put_Default(ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition* value)
    {
        m_default = value;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontStylesDefinition::get_Display(ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition** value)
    {
        return m_display.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontStylesDefinition::put_Display(ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition* value)
    {
        m_display = value;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontStylesDefinition::get_Monospace(ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition** value)
    {
        return m_monospace.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontStylesDefinition::put_Monospace(ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition* value)
    {
        m_monospace = value;
        return S_OK;
    }
}
