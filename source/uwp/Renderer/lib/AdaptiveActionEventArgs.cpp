#include "pch.h"
#include "AdaptiveActionEventArgs.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;

AdaptiveNamespaceStart
    HRESULT AdaptiveActionEventArgs::RuntimeClassInitialize()
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionEventArgs::RuntimeClassInitialize(IAdaptiveActionElement* action, IAdaptiveInputs* inputs)
    {
        m_action = action;
        m_inputs = inputs;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionEventArgs::get_Action(IAdaptiveActionElement** action)
    {
        return m_action.CopyTo(action);
    }

    IFACEMETHODIMP AdaptiveActionEventArgs::get_Inputs(IAdaptiveInputs** inputs)
    {
        return m_inputs.CopyTo(inputs);
    }
AdaptiveNamespaceEnd
