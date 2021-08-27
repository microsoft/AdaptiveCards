// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveToggleVisibilityTarget.h"
#include "ToggleVisibilityTarget.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveToggleVisibilityTarget::RuntimeClassInitialize() noexcept
    try
    {
        RuntimeClassInitialize(std::make_shared<ToggleVisibilityTarget>());
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveToggleVisibilityTarget::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ToggleVisibilityTarget>& sharedToggleTarget)
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleTarget->GetElementId(), m_elementId.GetAddressOf()));
        m_visibilityToggle = (ABI::AdaptiveCards::ObjectModel::Uwp::IsVisible)sharedToggleTarget->GetIsVisible();
        return S_OK;
    }

    HRESULT AdaptiveToggleVisibilityTarget::get_ElementId(_Outptr_ HSTRING* title) { return m_elementId.CopyTo(title); }

    HRESULT AdaptiveToggleVisibilityTarget::put_ElementId(_In_ HSTRING title) { return m_elementId.Set(title); }

    HRESULT AdaptiveToggleVisibilityTarget::get_IsVisible(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::IsVisible* value)
    {
        *value = m_visibilityToggle;
        return S_OK;
    }

    HRESULT AdaptiveToggleVisibilityTarget::put_IsVisible(ABI::AdaptiveCards::ObjectModel::Uwp::IsVisible value)
    {
        m_visibilityToggle = value;
        return S_OK;
    }

    HRESULT AdaptiveToggleVisibilityTarget::GetSharedModel(std::shared_ptr<AdaptiveCards::ToggleVisibilityTarget>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::ToggleVisibilityTarget> toggleTarget =
            std::make_shared<AdaptiveCards::ToggleVisibilityTarget>();

        std::string id;
        RETURN_IF_FAILED(HStringToUTF8(m_elementId.Get(), id));
        toggleTarget->SetElementId(id);
        toggleTarget->SetIsVisible((AdaptiveCards::IsVisible)m_visibilityToggle);

        sharedModel = std::move(toggleTarget);
        return S_OK;
    }
    CATCH_RETURN;
}
