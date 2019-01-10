#include "pch.h"

#include "AdaptiveActionInvoker.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveActionInvoker::RuntimeClassInitialize() noexcept { return S_OK; }

    HRESULT AdaptiveActionInvoker::RuntimeClassInitialize(_In_ RenderedAdaptiveCard* renderResult) noexcept try
    {
        m_renderResult = renderResult;
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveActionInvoker::SendActionEvent(_In_ IAdaptiveActionElement* actionElement)
    {
        return m_renderResult->SendActionEvent(actionElement);
    }

}
