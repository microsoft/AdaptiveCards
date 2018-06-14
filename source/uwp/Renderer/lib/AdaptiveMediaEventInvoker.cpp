#include "pch.h"

#include "AdaptiveMediaEventInvoker.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;

AdaptiveNamespaceStart
    HRESULT AdaptiveMediaEventInvoker::RuntimeClassInitialize() noexcept
    {
        return S_OK;
    }

    HRESULT AdaptiveMediaEventInvoker::RuntimeClassInitialize(
        RenderedAdaptiveCard* renderResult) noexcept try
    {
        m_renderResult = renderResult;
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveMediaEventInvoker::SendMediaPlayEvent(IAdaptiveMedia* mediaElement)
    {
        return m_renderResult->SendMediaPlayEvent(mediaElement);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveMediaEventInvoker::SendMediaEndedEvent(IAdaptiveMedia* mediaElement)
    {
        return m_renderResult->SendMediaEndedEvent(mediaElement);
    }

AdaptiveNamespaceEnd
