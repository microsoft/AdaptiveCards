#include "pch.h"

#include "AdaptiveRenderArgs.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveRenderArgs::RuntimeClassInitialize() noexcept { return S_OK; }

    HRESULT AdaptiveRenderArgs::RuntimeClassInitialize(ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                                                       _In_ IInspectable* parentElement) noexcept try
    {
        m_containerStyle = containerStyle;
        m_parentElement = parentElement;
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveRenderArgs::get_ContainerStyle(_Out_ ABI::AdaptiveNamespace::ContainerStyle* value)
    {
        *value = m_containerStyle;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::put_ContainerStyle(ABI::AdaptiveNamespace::ContainerStyle value)
    {
        m_containerStyle = value;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::get_ParentElement(_COM_Outptr_ IInspectable** value)
    {
        return m_parentElement.CopyTo(value);
    }

    HRESULT AdaptiveRenderArgs::put_ParentElement(_In_ IInspectable* value)
    {
        m_parentElement = value;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::get_AncestorHasFallback(_Out_ boolean* hasFallback)
    {
        *hasFallback = m_ancestorHasFallback;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::put_AncestorHasFallback(boolean hasFallback)
    {
        m_ancestorHasFallback = hasFallback;
        return S_OK;
    }
}
