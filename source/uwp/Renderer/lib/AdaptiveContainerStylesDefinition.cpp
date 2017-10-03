#include "pch.h"
#include "AdaptiveContainerStyleDefinition.h"
#include "AdaptiveContainerStylesDefinition.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveContainerStylesDefinition::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveContainerStylesDefinition::RuntimeClassInitialize(ContainerStylesDefinition stylesDefinition) noexcept
    {
        m_sharedContainerStylesDefinition = stylesDefinition;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStylesDefinition::get_Default(ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition ** value)
    {
        return MakeAndInitialize<AdaptiveContainerStyleDefinition>(value, m_sharedContainerStylesDefinition.defaultPalette);
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStylesDefinition::put_Default(ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition * value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStylesDefinition::get_Emphasis(ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition ** value)
    {
        return MakeAndInitialize<AdaptiveContainerStyleDefinition>(value, m_sharedContainerStylesDefinition.emphasisPalette);
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStylesDefinition::put_Emphasis(ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition * value)
    {
        return E_NOTIMPL;
    }
}
}
