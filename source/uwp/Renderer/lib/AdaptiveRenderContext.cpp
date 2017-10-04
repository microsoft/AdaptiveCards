#include "pch.h"

#include "AdaptiveRenderContext.h"
#include "AdaptiveHostConfig.h"
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
        IAdaptiveActionRendererRegistration* actionRendererRegistration,
        RenderedAdaptiveCard* renderResult) noexcept try
    {
        m_hostConfig = hostConfig;
        m_elementRendererRegistration = elementRendererRegistration;
        m_actionRendererRegistration = actionRendererRegistration;
        m_renderResult = renderResult;

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::get_HostConfig(IAdaptiveHostConfig** value)
    {
        m_hostConfig.CopyTo(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::get_ElementRenderers(IAdaptiveElementRendererRegistration** value)
    {
        m_elementRendererRegistration.CopyTo(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::get_ActionRenderers(IAdaptiveActionRendererRegistration** value)
    {
        m_actionRendererRegistration.CopyTo(value);
        return S_OK;
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

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::SendActionEvent(IAdaptiveActionEventArgs* eventArgs)
    {
        return m_renderResult->SendActionEvent(eventArgs);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::get_ParentContainerStyle(ABI::AdaptiveCards::Uwp::ContainerStyle *value)
    {
        *value = m_containerStyle;
        return S_OK;
    }
    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::put_ParentContainerStyle(ABI::AdaptiveCards::Uwp::ContainerStyle value)
    {
        m_containerStyle = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderContext::get_UserInputs(IAdaptiveInputs** value)
    {
        return m_renderResult->get_UserInputs(value);
    }
}}
