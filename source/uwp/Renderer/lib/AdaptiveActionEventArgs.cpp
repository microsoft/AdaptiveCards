#include "pch.h"
#include "AdaptiveActionEventArgs.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Data::Json;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveActionEventArgs::RuntimeClassInitialize()
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionEventArgs::RuntimeClassInitialize(IAdaptiveActionElement* action, IJsonObject* inputs)
    {
        m_action = action;
        m_inputs = inputs;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionEventArgs::get_Action(IAdaptiveActionElement** action)
    {
        ComPtr<IAdaptiveActionElement> localAction(m_action);
        *action = localAction.Detach();
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionEventArgs::get_Inputs(IJsonObject** inputs)
    {
        ComPtr<IJsonObject> localInputs(m_inputs);
        *inputs = localInputs.Detach();
        return S_OK;
    }
}}