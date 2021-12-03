// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveContainerStyleDefinition.h"
#include "AdaptiveColorsConfig.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveContainerStyleDefinition::RuntimeClassInitialize() noexcept
    try
    {
        ContainerStyleDefinition styleDefinition;
        return RuntimeClassInitialize(styleDefinition);
    }
    CATCH_RETURN;

    HRESULT AdaptiveContainerStyleDefinition::RuntimeClassInitialize(ContainerStyleDefinition styleDefinition) noexcept
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveColorsConfig>(m_foregroundColors.GetAddressOf(), styleDefinition.foregroundColors));
        RETURN_IF_FAILED(GetColorFromString(styleDefinition.backgroundColor, &m_backgroundColor));
        RETURN_IF_FAILED(GetColorFromString(styleDefinition.borderColor, &m_borderColor));
        return S_OK;
    }

    HRESULT AdaptiveContainerStyleDefinition::get_BackgroundColor(_Out_ ABI::Windows::UI::Color* value)
    {
        *value = m_backgroundColor;
        return S_OK;
    }

    HRESULT AdaptiveContainerStyleDefinition::put_BackgroundColor(ABI::Windows::UI::Color color)
    {
        m_backgroundColor = color;
        return S_OK;
    }

    HRESULT AdaptiveContainerStyleDefinition::get_BorderColor(_Out_ ABI::Windows::UI::Color* value)
    {
        *value = m_borderColor;
        return S_OK;
    }

    HRESULT AdaptiveContainerStyleDefinition::put_BorderColor(ABI::Windows::UI::Color value)
    {
        m_borderColor = value;
        return S_OK;
    }

    HRESULT AdaptiveContainerStyleDefinition::get_ForegroundColors(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorsConfig** colorsConfig)
    {
        return m_foregroundColors.CopyTo(colorsConfig);
    }

    HRESULT AdaptiveContainerStyleDefinition::put_ForegroundColors(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorsConfig* colorsConfig)
    {
        m_foregroundColors = colorsConfig;
        return S_OK;
    }
    HRESULT AdaptiveContainerStyleDefinition::get_HighlightColors(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorsConfig** colorsConfig)
    {
        return m_highlightColors.CopyTo(colorsConfig);
    }

    HRESULT AdaptiveContainerStyleDefinition::put_HighlightColors(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorsConfig* colorsConfig)
    {
        m_highlightColors = colorsConfig;
        return S_OK;
    }
}
