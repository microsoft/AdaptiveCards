// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ElementTagContent.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT ElementTagContent::RuntimeClassInitialize(_In_ IAdaptiveCardElement* cardElement,
                                                      _In_ IPanel* parentPanel,
                                                      _In_ IUIElement* separator,
                                                      _In_ IColumnDefinition* columnDefinition)
    {
        ComPtr<IPanel> localParentPanel(parentPanel);
        RETURN_IF_FAILED(localParentPanel.AsWeak(&m_parentPanel));

        m_columnDefinition = columnDefinition;
        m_separator = separator;
        m_cardElement = cardElement;
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
}
