#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include <wrl\async.h>
#include "AdaptiveRenderResult.h"
#include "InputItem.h"
#include "XamlBuilder.h"
#include "XamlCardRendererComponent.h"
#include "XamlHelpers.h"

#define MakeAgileDispatcherCallback ::Microsoft::WRL::Callback<::Microsoft::WRL::Implements<::Microsoft::WRL::RuntimeClassFlags<::Microsoft::WRL::ClassicCom>, ::ABI::Windows::UI::Core::IDispatchedHandler, ::Microsoft::WRL::FtmBase>>

/// A base class for IAsyncOperation<T> implementations for use with WRL
template<typename T>
class RenderAsyncBase :
    public Microsoft::WRL::RuntimeClass<
    Microsoft::WRL::AsyncBase<ABI::Windows::Foundation::IAsyncOperationCompletedHandler<T*>>,
    ABI::Windows::Foundation::IAsyncOperation<T*>,
    AdaptiveCards::XamlCardRenderer::IXamlBuilderListener>
{
    InspectableClass(L"Windows.Foundation.IAsyncInfo", BaseTrust)

public:
    typedef ABI::Windows::Foundation::IAsyncOperationCompletedHandler<T*> HandlerType;

    RenderAsyncBase(
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* card, AdaptiveCards::XamlCardRenderer::XamlCardRenderer* renderer)
        : m_card(card), 
          m_renderer(renderer)
    {
        // Get the dispatcher to we can run an async operation to build the xaml tree
        ComPtr<ABI::Windows::UI::Core::ICoreWindowStatic> coreWindowStatic;
        THROW_IF_FAILED(Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), &coreWindowStatic));
        ComPtr<ABI::Windows::UI::Core::ICoreWindow> coreWindow;
        THROW_IF_FAILED(coreWindowStatic->GetForCurrentThread(coreWindow.GetAddressOf()));
        THROW_IF_FAILED(coreWindow->get_Dispatcher(&m_dispatcher));

        m_builder = Microsoft::WRL::Make<AdaptiveCards::XamlCardRenderer::XamlBuilder>();
        m_inputElements = std::make_shared<std::vector<AdaptiveCards::XamlCardRenderer::InputItem>>();
        THROW_IF_FAILED(m_builder->SetHostConfig(m_renderer->GetHostConfig()));
        THROW_IF_FAILED(m_builder->SetOverrideDictionary(m_renderer->GetOverrideDictionary()));
        UINT32 width = 0;
        UINT32 height = 0;
        bool explicitDimensions = m_renderer->GetFixedDimensions(&width, &height);
        if (explicitDimensions)
        {
            THROW_IF_FAILED(m_builder->SetFixedDimensions(width, height));
        }
    }

    // IAsyncOperation
    virtual auto STDMETHODCALLTYPE put_Completed(HandlerType* handler) -> HRESULT override
    {
        return AsyncBase::PutOnComplete(handler);
    }

    virtual auto STDMETHODCALLTYPE get_Completed(HandlerType** handler) -> HRESULT override
    {
        return AsyncBase::GetOnComplete(handler);
    }

    // IXamlBuilderListener
    IFACEMETHODIMP AllImagesLoaded()
    {
        return OnXamlImagesLoaded();
    }

    IFACEMETHODIMP ImagesLoadingHadError()
    {
        return OnXamlImagesHadError();
    }

    IFACEMETHODIMP XamlBuilderHadError()
    {
        return OnXamlBuilderHadError();
    }

protected:
    Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_rootXamlElement;
    Microsoft::WRL::ComPtr<ABI::Windows::UI::Core::ICoreDispatcher> m_dispatcher;
    Microsoft::WRL::ComPtr<AdaptiveCards::XamlCardRenderer::XamlBuilder> m_builder;
    Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard> m_card;
    Microsoft::WRL::ComPtr<AdaptiveCards::XamlCardRenderer::XamlCardRenderer> m_renderer;
    std::shared_ptr<std::vector<AdaptiveCards::XamlCardRenderer::InputItem>> m_inputElements;
    bool m_isValid;

    HRESULT OnStart(void) override
    {
        Microsoft::WRL::ComPtr<RenderAsyncBase<T>> strongThis(this);
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncAction> dispatcherAsyncAction;
        m_dispatcher->RunAsync(ABI::Windows::UI::Core::CoreDispatcherPriority_Normal,
            MakeAgileDispatcherCallback([this, strongThis]() -> HRESULT
        {
            m_builder->AddListener(this);
            try
            {
                m_builder->BuildXamlTreeFromAdaptiveCard(m_card.Get(), m_inputElements, &m_rootXamlElement, m_renderer.Get());
                m_isValid = m_rootXamlElement != nullptr;
            }
            catch (...)
            {
                //Catch all non-Image loading related problems.
                m_isValid = false;
                return XamlBuilderHadError();
            }
            return S_OK;
        }).Get(),
            &dispatcherAsyncAction);

        dispatcherAsyncAction->put_Completed(
            Microsoft::WRL::Callback<ABI::Windows::Foundation::IAsyncActionCompletedHandler>(
                [this](ABI::Windows::Foundation::IAsyncAction* action, ABI::Windows::Foundation::AsyncStatus status) -> HRESULT
        {
            return XamlRenderCompleted(action, status);
        }).Get());
        return S_OK;
    }

    void OnClose() override
    {
    }

    void OnCancel() override
    {
    }

    virtual HRESULT XamlRenderCompleted(ABI::Windows::Foundation::IAsyncAction* action, ABI::Windows::Foundation::AsyncStatus status) = 0;
    virtual HRESULT OnXamlImagesLoaded() = 0;
    virtual HRESULT OnXamlImagesHadError() = 0;

    HRESULT OnXamlBuilderHadError()
    {
        AsyncBase::TryTransitionToError(E_FAIL);
        return AsyncBase::FireCompletion();
    }

private:
    std::function<ABI::Windows::UI::Xaml::IUIElement*(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard*)> m_dispatchFunction;
};


class RenderCardAsXamlAsyncOperation : 
    public RenderAsyncBase<ABI::AdaptiveCards::XamlCardRenderer::AdaptiveRenderResult>
{
public:
    RenderCardAsXamlAsyncOperation(
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* card,
        AdaptiveCards::XamlCardRenderer::XamlCardRenderer* renderer)
        : RenderAsyncBase<ABI::AdaptiveCards::XamlCardRenderer::AdaptiveRenderResult>(card, renderer)
    {
        AsyncBase::Start();
    }

    STDMETHODIMP ABI::Windows::Foundation::IAsyncOperation_impl<TResult_complex>::GetResults(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveRenderResult** renderResult)
    {
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveRenderResult> result;
        RETURN_IF_FAILED(Microsoft::WRL::Details::MakeAndInitialize<AdaptiveCards::XamlCardRenderer::AdaptiveRenderResult>(
            &result,
            m_isValid,
            m_card.Get(),
            m_rootXamlElement.Get(),
            m_inputElements));
        return result.CopyTo(renderResult);
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

    HRESULT OnXamlImagesHadError()
    {
        AsyncBase::TryTransitionToError(E_FAIL);
        return AsyncBase::FireCompletion();
    }

};