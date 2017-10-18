#include "pch.h"
#include "AdaptiveContainerStyleDefinition.h"
#include "AdaptiveContainerStylesDefinition.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveContainerStylesDefinition::RuntimeClassInitialize() noexcept try
    {
        ContainerStylesDefinition stylesDefinition;
        return RuntimeClassInitialize(stylesDefinition);
    } CATCH_RETURN;

    HRESULT AdaptiveContainerStylesDefinition::RuntimeClassInitialize(ContainerStylesDefinition stylesDefinition) noexcept
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveContainerStyleDefinition>(m_default.GetAddressOf(), stylesDefinition.defaultPalette));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveContainerStyleDefinition>(m_emphasis.GetAddressOf(), stylesDefinition.defaultPalette));

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStylesDefinition::get_Default(ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition ** value)
    {
        ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition> defaultContainerStyle = m_default;
        *value = defaultContainerStyle.Detach(); 
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStylesDefinition::put_Default(ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition * value)
    {
        m_default = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStylesDefinition::get_Emphasis(ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition ** value)
    {
        ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition> emphasisContainerStyle = m_emphasis;
        *value = emphasisContainerStyle.Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStylesDefinition::put_Emphasis(ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition * value)
    {
        m_emphasis = value;
        return S_OK;
    }
}
}
