#include "pch.h"

#include "AdaptiveRenderContext.h"
#include "InputItem.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveRenderContext::RuntimeClassInitialize() noexcept
    {
        return S_OK;
    }

    HRESULT AdaptiveRenderContext::RuntimeClassInitialize(
        IAdaptiveHostConfig* hostConfig,
        IAdaptiveElementRendererRegistration* elementRendererRegistration,
        IAdaptiveCardResourceResolvers* resourceResolvers,
        RenderedAdaptiveCard* renderResult) noexcept try
    {
        m_hostConfig = hostConfig;
        m_elementRendererRegistration = elementRendererRegistration;
        m_renderResult = renderResult;
        m_resourceResolvers = resourceResolvers;

        return MakeAndInitialize<AdaptiveActionInvoker>(&m_actionInvoker, renderResult);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::get_HostConfig(IAdaptiveHostConfig** value)
    {
        return m_hostConfig.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::get_ElementRenderers(IAdaptiveElementRendererRegistration** value)
    {
        return m_elementRendererRegistration.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::get_ActionInvoker(IAdaptiveActionInvoker** value)
    {
        return m_actionInvoker.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::get_ResourceResolvers(IAdaptiveCardResourceResolvers** value)
    {
        return m_resourceResolvers.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::AddInputItem(IAdaptiveCardElement* cardElement, ABI::Windows::UI::Xaml::IUIElement* uiElement)
    {
        ComPtr<IAdaptiveCardElement> localCardElement(cardElement);
        ComPtr<IAdaptiveInputElement> inputElement;
        THROW_IF_FAILED(localCardElement.As(&inputElement));

        ComPtr<IUIElement> localUiElement(uiElement);

        InputItem item(inputElement.Get(), localUiElement.Get());

        auto inputItems = m_renderResult->GetInputItems();

        if (inputItems != nullptr)
        {
            inputItems->push_back(item);
        }
        else
        {
            // Add to Errors
        }

        return S_OK;
    }
}}
