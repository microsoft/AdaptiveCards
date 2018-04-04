#include "pch.h"
#include "AdaptiveContainerStyleDefinition.h"
#include "AdaptiveContainerStylesDefinition.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

AdaptiveNamespaceStart
    HRESULT AdaptiveContainerStylesDefinition::RuntimeClassInitialize() noexcept try
    {
        ContainerStylesDefinition stylesDefinition;
        return RuntimeClassInitialize(stylesDefinition);
    } CATCH_RETURN;

    HRESULT AdaptiveContainerStylesDefinition::RuntimeClassInitialize(ContainerStylesDefinition stylesDefinition) noexcept
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveContainerStyleDefinition>(m_default.GetAddressOf(), stylesDefinition.defaultPalette));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveContainerStyleDefinition>(m_emphasis.GetAddressOf(), stylesDefinition.emphasisPalette));

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainerStylesDefinition::get_Default(ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition ** value)
    {
        return m_default.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStylesDefinition::put_Default(ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition * value)
    {
        m_default = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStylesDefinition::get_Emphasis(ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition ** value)
    {
        return m_emphasis.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveContainerStylesDefinition::put_Emphasis(ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition * value)
    {
        m_emphasis = value;
        return S_OK;
    }
AdaptiveNamespaceEnd
