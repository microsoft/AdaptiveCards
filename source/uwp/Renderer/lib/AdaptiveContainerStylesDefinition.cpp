#include "pch.h"
#include "AdaptiveContainerStyleDefinition.h"
#include "AdaptiveContainerStylesDefinition.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveCards { namespace XamlCardRenderer
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
    HRESULT AdaptiveContainerStylesDefinition::get_Default(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition ** value)
    {
        return MakeAndInitialize<AdaptiveContainerStyleDefinition>(value, m_sharedContainerStylesDefinition.defaultPalette);
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStylesDefinition::put_Default(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition * value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStylesDefinition::get_Emphasis(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition ** value)
    {
        return MakeAndInitialize<AdaptiveContainerStyleDefinition>(value, m_sharedContainerStylesDefinition.emphasisPalette);
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStylesDefinition::put_Emphasis(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition * value)
    {
        return E_NOTIMPL;
    }
}
}
