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
        ComPtr<RenderedAdaptiveCard> strongRenderResult = renderResult;
        return strongRenderResult.AsWeak(&m_weakRenderResult);
    }
    CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveActionInvoker::SendActionEvent(IAdaptiveActionElement* actionElement)
    {
        ComPtr<IRenderedAdaptiveCard> strongRenderResult;
        RETURN_IF_FAILED(m_weakRenderResult.As(&strongRenderResult));
        if (strongRenderResult != nullptr)
        {
            ComPtr<RenderedAdaptiveCard> renderResult = PeekInnards<RenderedAdaptiveCard>(strongRenderResult);
            if (renderResult != nullptr)
            {
                RETURN_IF_FAILED(renderResult->SendActionEvent(actionElement));
            }
        }
        return S_OK;
    }

AdaptiveNamespaceEnd
