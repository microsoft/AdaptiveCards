#include "pch.h"

#include "AdaptiveRenderArgs.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveRenderArgs::RuntimeClassInitialize() noexcept
    {
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::RuntimeClassInitialize(
        ABI::AdaptiveCards::Uwp::ContainerStyle containerStyle) noexcept try
    {
        m_containerStyle = containerStyle;
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveRenderArgs::get_ContainerStyle(ABI::AdaptiveCards::Uwp::ContainerStyle *value)
    {
        *value = m_containerStyle;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderArgs::put_ContainerStyle(ABI::AdaptiveCards::Uwp::ContainerStyle value)
    {
        m_containerStyle = value;
        return S_OK;
    }
}}
