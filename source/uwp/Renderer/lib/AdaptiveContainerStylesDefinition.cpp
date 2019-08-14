// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveContainerStyleDefinition.h"
#include "AdaptiveContainerStylesDefinition.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveContainerStylesDefinition::RuntimeClassInitialize() noexcept try
    {
        ContainerStylesDefinition stylesDefinition;
        return RuntimeClassInitialize(stylesDefinition);
    }
    CATCH_RETURN;

    HRESULT AdaptiveContainerStylesDefinition::RuntimeClassInitialize(ContainerStylesDefinition stylesDefinition) noexcept
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveContainerStyleDefinition>(m_default.GetAddressOf(), stylesDefinition.defaultPalette));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveContainerStyleDefinition>(m_emphasis.GetAddressOf(), stylesDefinition.emphasisPalette));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveContainerStyleDefinition>(m_good.GetAddressOf(), stylesDefinition.goodPalette));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveContainerStyleDefinition>(m_attention.GetAddressOf(), stylesDefinition.attentionPalette));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveContainerStyleDefinition>(m_warning.GetAddressOf(), stylesDefinition.warningPalette));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveContainerStyleDefinition>(m_accent.GetAddressOf(), stylesDefinition.accentPalette));

        return S_OK;
    }

    HRESULT AdaptiveContainerStylesDefinition::get_Default(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value)
    {
        return m_default.CopyTo(value);
    }

    HRESULT AdaptiveContainerStylesDefinition::put_Default(_In_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value)
    {
        m_default = value;
        return S_OK;
    }

    HRESULT AdaptiveContainerStylesDefinition::get_Emphasis(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value)
    {
        return m_emphasis.CopyTo(value);
    }

    HRESULT AdaptiveContainerStylesDefinition::put_Emphasis(_In_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value)
    {
        m_emphasis = value;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveContainerStylesDefinition::get_Good(ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value)
    {
        return m_good.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveContainerStylesDefinition::put_Good(ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value)
    {
        m_good = value;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveContainerStylesDefinition::get_Attention(ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value)
    {
        return m_attention.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveContainerStylesDefinition::put_Attention(ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value)
    {
        m_emphasis = value;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveContainerStylesDefinition::get_Warning(ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value)
    {
        return m_warning.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveContainerStylesDefinition::put_Warning(ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value)
    {
        m_warning = value;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveContainerStylesDefinition::get_Accent(ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value)
    {
        return m_accent.CopyTo(value);
    }

    _Use_decl_annotations_ HRESULT AdaptiveContainerStylesDefinition::put_Accent(ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value)
    {
        m_accent = value;
        return S_OK;
    }
}
