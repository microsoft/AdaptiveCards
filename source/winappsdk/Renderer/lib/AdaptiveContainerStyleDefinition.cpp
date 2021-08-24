// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveContainerStyleDefinition.h"
#include "AdaptiveContainerStyleDefinition.g.cpp"
#include "AdaptiveColorsConfig.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveContainerStyleDefinition::AdaptiveContainerStyleDefinition(::AdaptiveCards::ContainerStyleDefinition styleDefinition)
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveColorsConfig>(m_foregroundColors.GetAddressOf(), styleDefinition.foregroundColors));
        BackgroundColor = GetColorFromString(styleDefinition.backgroundColor);
        BorderColor = GetColorFromString(styleDefinition.borderColor);
    }
}
