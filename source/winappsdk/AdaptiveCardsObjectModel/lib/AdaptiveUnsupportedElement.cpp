// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveUnsupportedElement.h"
#include "AdaptiveUnsupportedElement.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    AdaptiveUnsupportedElement::AdaptiveUnsupportedElement(const std::shared_ptr<::AdaptiveCards::UnknownElement>& sharedUnknown) :
        m_actualType(sharedUnknown->GetElementTypeString())
    {
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveUnsupportedElement::GetSharedModel()
    {
        auto unknownElement = std::make_shared<::AdaptiveCards::UnknownElement>();
        unknownElement->SetElementTypeString(m_actualType);
        CopySharedElementProperties(*unknownElement);

        return unknownElement;
    }
}
