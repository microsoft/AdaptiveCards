#include "pch.h"
#include "AdaptiveToggleVisibilityTarget.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "ToggleVisibilityTarget.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveToggleVisibilityTarget::RuntimeClassInitialize() noexcept try
    {
        RuntimeClassInitialize(std::make_shared<ToggleVisibilityTarget>());
        return S_OK;
    }
    CATCH_RETURN;

    _Use_decl_annotations_ HRESULT AdaptiveToggleVisibilityTarget::RuntimeClassInitialize(
        const std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget>& sharedToggleTarget)
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedToggleTarget->GetElementId(), m_elementId.GetAddressOf()));
        m_visibilityToggle = (ABI::AdaptiveNamespace::IsVisible)sharedToggleTarget->GetIsVisible();
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveToggleVisibilityTarget::get_ElementId(HSTRING* title)
    {
        return m_elementId.CopyTo(title);
    }

    _Use_decl_annotations_ HRESULT AdaptiveToggleVisibilityTarget::put_ElementId(HSTRING title)
    {
        return m_elementId.Set(title);
    }

    _Use_decl_annotations_ HRESULT AdaptiveToggleVisibilityTarget::get_IsVisible(ABI::AdaptiveNamespace::IsVisible* value)
    {
        *value = m_visibilityToggle;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveToggleVisibilityTarget::put_IsVisible(ABI::AdaptiveNamespace::IsVisible value)
    {
        m_visibilityToggle = value;
        return S_OK;
    }

    HRESULT AdaptiveToggleVisibilityTarget::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget> toggleTarget =
            std::make_shared<AdaptiveSharedNamespace::ToggleVisibilityTarget>();

        std::string id;
        RETURN_IF_FAILED(HStringToUTF8(m_elementId.Get(), id));
        toggleTarget->SetElementId(id);
        toggleTarget->SetIsVisible((AdaptiveSharedNamespace::IsVisible)m_visibilityToggle);

        sharedModel = toggleTarget;
        return S_OK;
    }
    CATCH_RETURN;
}
