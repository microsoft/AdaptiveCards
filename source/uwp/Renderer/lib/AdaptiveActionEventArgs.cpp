#include "pch.h"
#include "AdaptiveActionEventArgs.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveActionEventArgs::RuntimeClassInitialize()
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionEventArgs::RuntimeClassInitialize(IAdaptiveActionElement* action)
    {
        m_action = action;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionEventArgs::get_Action(IAdaptiveActionElement** action)
    {
        ComPtr<IAdaptiveActionElement> localAction(m_action);
        *action = localAction.Detach();
        return S_OK;
    }
}}