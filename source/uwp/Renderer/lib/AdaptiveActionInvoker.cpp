#include "pch.h"

#include "AdaptiveActionInvoker.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;

AdaptiveNamespaceStart
    HRESULT AdaptiveActionInvoker::RuntimeClassInitialize() noexcept
    {
        return S_OK;
    }

    HRESULT AdaptiveActionInvoker::RuntimeClassInitialize(
        RenderedAdaptiveCard* renderResult) noexcept try
    {
        m_renderResult = renderResult;
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveActionInvoker::SendActionEvent(IAdaptiveActionElement* actionElement)
    {
        return m_renderResult->SendActionEvent(actionElement);
    }

AdaptiveNamespaceEnd
