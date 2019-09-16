// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ElementTagContent.h"

using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT ElementTagContent::RuntimeClassInitialize(_In_ IAdaptiveCardElement* cardElement,
                                                      _In_ IPanel* parentPanel,
                                                      _In_ IUIElement* separator,
                                                      _In_ IColumnDefinition* columnDefinition,
                                                      _In_ boolean expectedVisibility)
    {
        m_columnDefinition = columnDefinition;
        m_parentPanel = parentPanel;
        m_separator = separator;
        m_cardElement = cardElement;
        m_expectedVisibility = expectedVisibility;
        return S_OK;
    }

    HRESULT ElementTagContent::get_ColumnDefinition(_COM_Outptr_ IColumnDefinition** columnDefinition)
    {
        return m_columnDefinition.CopyTo(columnDefinition);
    }

    HRESULT ElementTagContent::get_AdaptiveCardElement(_COM_Outptr_ IAdaptiveCardElement** cardElement)
    {
        return m_cardElement.CopyTo(cardElement);
    }

    HRESULT ElementTagContent::get_Separator(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** separator)
    {
        return m_separator.CopyTo(separator);
    }

    HRESULT ElementTagContent::get_ParentPanel(_COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel** parentPanel)
    {
        return m_parentPanel.CopyTo(parentPanel);
    }

    HRESULT ElementTagContent::get_ExpectedVisibility(_Outptr_ boolean* expectedVisibility)
    {
        *expectedVisibility = m_expectedVisibility;
        return S_OK;
    }

    HRESULT ElementTagContent::set_ExpectedVisibility(boolean expectedVisibility)
    {
        m_expectedVisibility = expectedVisibility;
        return S_OK;
    }
}
