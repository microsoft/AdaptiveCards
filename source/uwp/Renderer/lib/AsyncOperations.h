#pragma once
#include "AdaptiveCards.Rendering.Uwp.h"
#include <wrl\async.h>
#include "XamlBuilder.h"
#include "AdaptiveCardRendererComponent.h"
#include "XamlHelpers.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveRenderContext.h"

#define MakeAgileDispatcherCallback \
    ::Microsoft::WRL::Callback< \
        ::Microsoft::WRL::Implements<::Microsoft::WRL::RuntimeClassFlags<::Microsoft::WRL::ClassicCom>, ::ABI::Windows::UI::Core::IDispatchedHandler, ::Microsoft::WRL::FtmBase>>

/// A base class for IAsyncOperation<T> implementations for use with WRL
template<typename T>
class RenderAsyncBase
    : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::AsyncBase<ABI::Windows::Foundation::IAsyncOperationCompletedHandler<T*>>,
                                          ABI::Windows::Foundation::IAsyncOperation<T*>,
                                          AdaptiveNamespace::IXamlBuilderListener>
{
    InspectableClass(L"Windows.Foundation.IAsyncInfo", BaseTrust)

        public : typedef ABI::Windows::Foundation::IAsyncOperationCompletedHandler<T*> HandlerType;

    RenderAsyncBase(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* card, _In_ AdaptiveNamespace::AdaptiveCardRenderer* renderer) :
        m_card(card), m_renderer(renderer)
    {
        // Get the dispatcher to we can run an async operation to build the xaml tree
        ComPtr<ABI::Windows::UI::Core::ICoreWindowStatic> coreWindowStatic;
        THROW_IF_FAILED(
            Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), &coreWindowStatic));
        ComPtr<ABI::Windows::UI::Core::ICoreWindow> coreWindow;
        THROW_IF_FAILED(coreWindowStatic->GetForCurrentThread(coreWindow.GetAddressOf()));
        THROW_IF_FAILED(coreWindow->get_Dispatcher(&m_dispatcher));

        UINT32 width = 0;
        UINT32 height = 0;
        bool explicitDimensions = m_renderer->GetFixedDimensions(&width, &height);
        if (explicitDimensions)
        {
            THROW_IF_FAILED(m_renderer->GetXamlBuilder()->SetFixedDimensions(width, height));
        }
    }

    // IAsyncOperation
    virtual auto STDMETHODCALLTYPE put_Completed(_In_ HandlerType* handler) -> HRESULT override
    {
        return AsyncBase::PutOnComplete(handler);
    }

    virtual auto STDMETHODCALLTYPE get_Completed(_COM_Outptr_ HandlerType** handler) -> HRESULT override
    {
        return AsyncBase::GetOnComplete(handler);
    }

    // IXamlBuilderListener
    IFACEMETHODIMP AllImagesLoaded() { return OnXamlImagesLoaded(); }

    IFACEMETHODIMP ImagesLoadingHadError() { return OnXamlImagesHadError(); }

    IFACEMETHODIMP XamlBuilderHadError() { return OnXamlBuilderHadError(); }

protected:
    Microsoft::WRL::ComPtr<AdaptiveNamespace::RenderedAdaptiveCard> m_renderResult;
    Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IFrameworkElement> m_rootXamlElement;
    Microsoft::WRL::ComPtr<ABI::Windows::UI::Core::ICoreDispatcher> m_dispatcher;
    Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCard> m_card;
    Microsoft::WRL::ComPtr<AdaptiveNamespace::AdaptiveCardRenderer> m_renderer;

    HRESULT OnStart(void) override
    {
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncAction> dispatcherAsyncAction;
        m_dispatcher->RunAsync(
            ABI::Windows::UI::Core::CoreDispatcherPriority_Normal,
            MakeAgileDispatcherCallback([this]() -> HRESULT {
                m_renderer->GetXamlBuilder()->AddListener(this);
                try
                {
                    THROW_IF_FAILED(MakeAndInitialize<AdaptiveNamespace::RenderedAdaptiveCard>(&m_renderResult));
                    ComPtr<ABI::AdaptiveNamespace::IAdaptiveElementRendererRegistration> elementRenderers;
                    THROW_IF_FAILED(m_renderer->get_ElementRenderers(&elementRenderers));
                    ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionRendererRegistration> actionRenderers;
                    THROW_IF_FAILED(m_renderer->get_ActionRenderers(&actionRenderers));
                    ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers> resourceResolvers;
                    THROW_IF_FAILED(m_renderer->get_ResourceResolvers(&resourceResolvers));
                    ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> overrideDictionary = m_renderer->GetMergedDictionary();
                    ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> actionSentimentDefaultDictionary =
                        m_renderer->GetActionSentimentResourceDictionary();

                    ComPtr<AdaptiveNamespace::AdaptiveRenderContext> renderContext;
                    THROW_IF_FAILED(
                        MakeAndInitialize<AdaptiveNamespace::AdaptiveRenderContext>(&renderContext,
                                                                                    m_renderer->GetHostConfig(),
                                                                                    elementRenderers.Get(),
                                                                                    actionRenderers.Get(),
                                                                                    resourceResolvers.Get(),
                                                                                    overrideDictionary.Get(),
                                                                                    actionSentimentDefaultDictionary.Get(),
                                                                                    m_renderResult.Get()));

                    AdaptiveNamespace::XamlBuilder::BuildXamlTreeFromAdaptiveCard(m_card.Get(),
                                                                                              &m_rootXamlElement,
                                                                                              renderContext.Get(),
                                                                                              m_renderer->GetXamlBuilder());
                }
                catch (...)
                {
                    // Catch all non-Image loading related problems.
                    return XamlBuilderHadError();
                }
                return S_OK;
            })
                .Get(),
            &dispatcherAsyncAction);

        dispatcherAsyncAction->put_Completed(
            Microsoft::WRL::Callback<ABI::Windows::Foundation::IAsyncActionCompletedHandler>(
                [this](ABI::Windows::Foundation::IAsyncAction* action, ABI::Windows::Foundation::AsyncStatus status) -> HRESULT {
                    return XamlRenderCompleted(action, status);
                })
                .Get());
        return S_OK;
    }

    void OnClose() override {}

    void OnCancel() override {}

    virtual HRESULT XamlRenderCompleted(_In_ ABI::Windows::Foundation::IAsyncAction* action,
                                        ABI::Windows::Foundation::AsyncStatus status) = 0;
    virtual HRESULT OnXamlImagesLoaded() = 0;
    virtual HRESULT OnXamlImagesHadError() = 0;

    HRESULT OnXamlBuilderHadError()
    {
        AsyncBase::TryTransitionToError(E_FAIL);
        return AsyncBase::FireCompletion();
    }

private:
    std::function<ABI::AdaptiveNamespace::IRenderedAdaptiveCard*(ABI::AdaptiveNamespace::IAdaptiveCard*)> m_dispatchFunction;
};

class RenderCardAsXamlAsyncOperation : public RenderAsyncBase<ABI::AdaptiveNamespace::RenderedAdaptiveCard>
{
public:
    RenderCardAsXamlAsyncOperation(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* card,
                                   _In_ AdaptiveNamespace::AdaptiveCardRenderer* renderer) :
        RenderAsyncBase<ABI::AdaptiveNamespace::RenderedAdaptiveCard>(card, renderer)
    {
        AsyncBase::Start();
    }

    STDMETHODIMP ABI::Windows::Foundation::IAsyncOperation_impl<TResult_complex>::GetResults(
        _COM_Outptr_ ABI::AdaptiveNamespace::IRenderedAdaptiveCard** result)
    {
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IRenderedAdaptiveCard> renderResultAsInterface;
        m_renderResult->SetFrameworkElement(m_rootXamlElement.Get());
        m_renderResult.As(&renderResultAsInterface);
        return renderResultAsInterface.CopyTo(result);
    }

protected:
    HRESULT XamlRenderCompleted(_In_ ABI::Windows::Foundation::IAsyncAction* /*action*/,
                                _In_ ABI::Windows::Foundation::AsyncStatus /*status*/) override
    {
        return S_OK;
    }

    HRESULT OnXamlImagesLoaded() { return AsyncBase::FireCompletion(); }

    HRESULT OnXamlImagesHadError()
    {
        AsyncBase::TryTransitionToError(E_FAIL);
        return AsyncBase::FireCompletion();
    }
};
