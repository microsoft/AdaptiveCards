// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveUnsupportedElement.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveUnsupportedElement::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::UnknownElement> unknownElement =
            std::make_shared<AdaptiveSharedNamespace::UnknownElement>();
        return RuntimeClassInitialize(unknownElement);
    }
    CATCH_RETURN;

    HRESULT AdaptiveUnsupportedElement::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::UnknownElement>& sharedUnknown) try
    {
        if (sharedUnknown == nullptr)
        {
            return E_INVALIDARG;
        }

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedUnknown));
        m_actualType = sharedUnknown->GetElementTypeString();
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveUnsupportedElement::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::Unsupported;
        return S_OK;
    }

    HRESULT AdaptiveUnsupportedElement::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedUnknown) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::UnknownElement> unknownElement =
            std::make_shared<AdaptiveSharedNamespace::UnknownElement>();

        unknownElement->SetElementTypeString(m_actualType);
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseCardElement>(unknownElement)));

        sharedUnknown = unknownElement;
        return S_OK;
    }
    CATCH_RETURN;
}
