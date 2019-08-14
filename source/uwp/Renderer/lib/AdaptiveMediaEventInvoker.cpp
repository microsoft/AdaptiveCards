// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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
        ComPtr<RenderedAdaptiveCard> strongRenderResult = renderResult;
        return strongRenderResult.AsWeak(&m_weakRenderResult);
    }
    CATCH_RETURN;

    HRESULT AdaptiveMediaEventInvoker::SendMediaClickedEvent(_In_ IAdaptiveMedia* mediaElement)
    {
        ComPtr<IRenderedAdaptiveCard> strongRenderResult;
        RETURN_IF_FAILED(m_weakRenderResult.As(&strongRenderResult));
        if (strongRenderResult != nullptr)
        {
            ComPtr<RenderedAdaptiveCard> renderResult = PeekInnards<RenderedAdaptiveCard>(strongRenderResult);
            if (renderResult != nullptr)
            {
                RETURN_IF_FAILED(renderResult->SendMediaClickedEvent(mediaElement));
            }
        }
        return S_OK;
    }
}
