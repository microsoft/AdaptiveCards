#include "pch.h"
#include "Util.h"
#include "AdaptiveColorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

AdaptiveNamespaceStart
    HRESULT AdaptiveColorConfig::RuntimeClassInitialize() noexcept try
    {
        ColorConfig colorConfig;
        return RuntimeClassInitialize(colorConfig);
    } CATCH_RETURN;


    HRESULT AdaptiveColorConfig::RuntimeClassInitialize(ColorConfig colorConfig) noexcept
    {
        RETURN_IF_FAILED(GetColorFromString(colorConfig.defaultColor, &m_defaultColor));
        RETURN_IF_FAILED(GetColorFromString(colorConfig.subtleColor, &m_subtleColor));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorConfig::get_Default(ABI::Windows::UI::Color* value)
    {
        *value = m_defaultColor;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorConfig::put_Default(ABI::Windows::UI::Color color)
    {
        m_defaultColor = color;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorConfig::get_Subtle(ABI::Windows::UI::Color* value)
    {
        *value = m_subtleColor;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorConfig::put_Subtle(ABI::Windows::UI::Color color)
    {
        m_subtleColor = color;
        return S_OK;
    }
AdaptiveNamespaceEnd

