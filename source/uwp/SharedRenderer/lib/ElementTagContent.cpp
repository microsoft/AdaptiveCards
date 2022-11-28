// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"

#include "ElementTagContent.h"
#include "ElementTagContent.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    ElementTagContent::ElementTagContent(winrt::IAdaptiveCardElement const& cardElement,
                                         winrt::xaml_controls::Panel const& parentPanel,
                                         winrt::xaml::UIElement const& separator,
                                         winrt::xaml_controls::ColumnDefinition const& columnDefinition,
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
