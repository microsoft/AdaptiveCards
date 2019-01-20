#include "pch.h"

#include "AdaptiveMediaEventInvoker.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveMediaEventInvoker::RuntimeClassInitialize() noexcept { return S_OK; }

    HRESULT AdaptiveMediaEventInvoker::RuntimeClassInitialize(_In_ RenderedAdaptiveCard* renderResult) noexcept try
    {
        m_renderResult = renderResult;
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveMediaEventInvoker::SendMediaClickedEvent(_In_ IAdaptiveMedia* mediaElement)
    {
        return m_renderResult->SendMediaClickedEvent(mediaElement);
    }
}
