#include "pch.h"
#include "RenderingActionEventArgs.h"

#include <Windows.UI.Xaml.h>

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI::Xaml;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT RenderingActionEventArgs::RuntimeClassInitialize()
    {
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT RenderingActionEventArgs::RuntimeClassInitialize(IAdaptiveActionElement* action)
    {
        m_action = action;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT RenderingActionEventArgs::get_Action(IAdaptiveActionElement** action)
    {
        ComPtr<IAdaptiveActionElement> localAction(m_action);
        *action = localAction.Detach();
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT RenderingActionEventArgs::get_CustomFrameworkElement(IFrameworkElement** customFrameworkElement)
    {
        ComPtr<IFrameworkElement> localCustomFrameworkElement(m_customFrameworkElement);
        *customFrameworkElement = localCustomFrameworkElement.Detach();
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT RenderingActionEventArgs::put_CustomFrameworkElement(IFrameworkElement* customFrameworkElement)
    {
        m_customFrameworkElement = customFrameworkElement;
        return S_OK;
    }
}}