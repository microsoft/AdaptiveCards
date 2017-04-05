#pragma once
#include "AsyncOperations.h"

#include "XamlBuilder.h"
#include "XamlCardRendererComponent.h"
#include "XamlHelpers.h"

#define MakeAgileDispatcherCallback ::Microsoft::WRL::Callback<::Microsoft::WRL::Implements<::Microsoft::WRL::RuntimeClassFlags<::Microsoft::WRL::ClassicCom>, ::ABI::Windows::UI::Core::IDispatchedHandler, ::Microsoft::WRL::FtmBase>>

RenderAsyncBase::RenderAsyncBase(
    ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* card)
    : m_card(card)
{
    // Get the dispatcher to we can run an async operation to build the xaml tree
    ComPtr<ICoreWindowStatic> coreWindowStatic;
    THROW_IF_FAILED(Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), &coreWindowStatic));
    ComPtr<ICoreWindow> coreWindow;
    THROW_IF_FAILED(coreWindowStatic->GetForCurrentThread(coreWindow.GetAddressOf()));
    THROW_IF_FAILED(coreWindow->get_Dispatcher(&m_dispatcher));

    m_builder = Microsoft::WRL::Make<AdaptiveCards::XamlCardRenderer::XamlBuilder>();
    AsyncBase::Start();
}

HRESULT RenderAsyncBase::AllImagesLoaded()
{
    return OnXamlImagesLoaded();
}

HRESULT RenderAsyncBase::OnStart(void) override
{
    Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncAction> dispatcherAsyncAction;
    ComPtr<IXamlBuilderListener> strongThis(this);
    RETURN_IF_FAILED(m_dispatcher->RunAsync(ABI::Windows::UI::Core::CoreDispatcherPriority_Normal,
        MakeAgileDispatcherCallback([strongThis]() -> HRESULT
    {
        RETURN_IF_FAILED(m_builder->AddListener(strongThis));

        ComPtr<IUIElement> rootElement;
        RETURN_IF_FAILED(m_builder->BuildXamlTreeFromAdaptiveCard(m_card.Get(), &m_rootXamlElement));
        return S_OK;
    }).Get(),
    &dispatcherAsyncAction));

    RETURN_IF_FAILED(dispatcherAsyncAction->put_Completed(
        Microsoft::WRL::Callback<ABI::Windows::Foundation::IAsyncActionCompletedHandler>(
            [this](ABI::Windows::Foundation::IAsyncAction* action, ABI::Windows::Foundation::AsyncStatus status) -> HRESULT
    {
        return XamlRenderCompleted(action, status);
    }).Get()));
    return S_OK;
}

void RenderAsyncBase::OnClose() override
{
}

void RenderAsyncBase::OnCancel() override
{
}

class RenderCardAsXamlAsyncOperation : 
    public RenderAsyncBase<ABI::Windows::UI::Xaml::UIElement>
{
public:
    RenderCardAsXamlAsyncOperation(
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* card) 
        : RenderAsyncBase<ABI::Windows::UI::Xaml::UIElement>(card)
    {
        AsyncBase::Start();
    }

    HRESULT ABI::Windows::Foundation::IAsyncOperation_impl<TResult_complex>::GetResults(ABI::Windows::UI::Xaml::IUIElement** rootElement)
    {
        return m_rootXamlElement.CopyTo(rootElement);
    }

protected:
    HRESULT XamlRenderCompleted(ABI::Windows::Foundation::IAsyncAction* /*action*/, ABI::Windows::Foundation::AsyncStatus /*status*/) override
    {
        return S_OK;
    }

    HRESULT OnXamlImagesLoaded()
    {
        return AsyncBase::FireCompletion();
    }

};