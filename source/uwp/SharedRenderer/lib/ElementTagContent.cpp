// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"

#include "ElementTagContent.h"
#include "ElementTagContent.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    ElementTagContent::ElementTagContent(winrt::IAdaptiveCardElement const& cardElement,
                                         winrt::Panel const& parentPanel,
                                         winrt::UIElement const& separator,
                                         winrt::ColumnDefinition const& columnDefinition,
                                         boolean expectedVisibility,
                                         boolean isStretchable)
    {
        m_cardElement = cardElement;
        m_parentPanel = parentPanel;
        m_separator = separator;
        m_columnDefinition = columnDefinition;
        ExpectedVisibility = expectedVisibility;
        IsStretchable = isStretchable;
    }

}
