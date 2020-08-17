// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveToggleVisibilityTarget.h"
#include "ToggleVisibilityTarget.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveToggleVisibilityTarget::RuntimeClassInitialize() noexcept
    try
    {
        RuntimeClassInitialize(std::make_shared<ToggleVisibilityTarget>());
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveToggleVisibilityTarget::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget>& sharedToggleTarget)
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleTarget->GetElementId(), m_elementId.GetAddressOf()));
        m_visibilityToggle = (ABI::AdaptiveNamespace::IsVisible)sharedToggleTarget->GetIsVisible();
        return S_OK;
    }

    HRESULT AdaptiveToggleVisibilityTarget::get_ElementId(_Outptr_ HSTRING* title) { return m_elementId.CopyTo(title); }

    HRESULT AdaptiveToggleVisibilityTarget::put_ElementId(_In_ HSTRING title) { return m_elementId.Set(title); }

    HRESULT AdaptiveToggleVisibilityTarget::get_IsVisible(_Out_ ABI::AdaptiveNamespace::IsVisible* value)
    {
        *value = m_visibilityToggle;
        return S_OK;
    }

    HRESULT AdaptiveToggleVisibilityTarget::put_IsVisible(ABI::AdaptiveNamespace::IsVisible value)
    {
        m_visibilityToggle = value;
        return S_OK;
    }

    HRESULT AdaptiveToggleVisibilityTarget::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget> toggleTarget =
            std::make_shared<AdaptiveSharedNamespace::ToggleVisibilityTarget>();

        std::string id;
        RETURN_IF_FAILED(HStringToUTF8(m_elementId.Get(), id));
        toggleTarget->SetElementId(id);
        toggleTarget->SetIsVisible((AdaptiveSharedNamespace::IsVisible)m_visibilityToggle);

        sharedModel = std::move(toggleTarget);
        return S_OK;
    }
    CATCH_RETURN;
}
