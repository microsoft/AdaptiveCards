// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveUnsupportedElement.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::WinUI3
{
    HRESULT AdaptiveUnsupportedElement::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::UnknownElement> unknownElement = std::make_shared<AdaptiveCards::UnknownElement>();
        return RuntimeClassInitialize(unknownElement);
    }
    CATCH_RETURN();

    HRESULT AdaptiveUnsupportedElement::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::UnknownElement>& sharedUnknown)
    try
    {
        if (sharedUnknown == nullptr)
        {
            return E_INVALIDARG;
        }

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedUnknown));
        m_actualType = sharedUnknown->GetElementTypeString();
        return S_OK;
    }
    CATCH_RETURN();

    HRESULT AdaptiveUnsupportedElement::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::Unsupported;
        return S_OK;
    }

    std::shared_ptr<AdaptiveCards::BaseCardElement> AdaptiveUnsupportedElement::GetSharedModel()
    {
        auto unknownElement = std::make_shared<AdaptiveCards::UnknownElement>();

        unknownElement->SetElementTypeString(m_actualType);
        THROW_IF_FAILED(CopySharedElementProperties(*unknownElement));

        return unknownElement;
    }
}
