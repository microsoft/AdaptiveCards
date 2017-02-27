#pragma once
#include "pch.h"

#include "AdaptiveCards.XamlCardRenderer.h"
#include <wrl\async.h>
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
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* card)
        : m_card(card)
    {
        // Get the dispatcher to we can run an async operation to build the xaml tree
        ComPtr<ABI::Windows::UI::Core::ICoreWindowStatic> coreWindowStatic;
        THROW_IF_FAILED(Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), &coreWindowStatic));
        ComPtr<ABI::Windows::UI::Core::ICoreWindow> coreWindow;
        THROW_IF_FAILED(coreWindowStatic->GetForCurrentThread(coreWindow.GetAddressOf()));
        THROW_IF_FAILED(coreWindow->get_Dispatcher(&m_dispatcher));

        m_builder = Microsoft::WRL::Make<AdaptiveCards::XamlCardRenderer::XamlBuilder>();
        AsyncBase::Start();
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

protected:
    Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_rootXamlElement;
    Microsoft::WRL::ComPtr<ABI::Windows::UI::Core::ICoreDispatcher> m_dispatcher;
    Microsoft::WRL::ComPtr<AdaptiveCards::XamlCardRenderer::XamlBuilder> m_builder;

    HRESULT OnStart(void) override
    {
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncAction> dispatcherAsyncAction;
        m_dispatcher->RunAsync(ABI::Windows::UI::Core::CoreDispatcherPriority_Normal,
            MakeAgileDispatcherCallback([this]() -> HRESULT
        {
            m_builder->AddListener(this);

            ComPtr<IUIElement> rootElement;
            m_builder->BuildXamlTreeFromAdaptiveCard(m_card.Get(), &m_rootXamlElement);
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

private:
    Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard> m_card;
    std::function<ABI::Windows::UI::Xaml::IUIElement*(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard*)> m_dispatchFunction;
};



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

    STDMETHODIMP ABI::Windows::Foundation::IAsyncOperation_impl<TResult_complex>::GetResults(ABI::Windows::UI::Xaml::IUIElement** rootElement)
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

class RenderCardAsImageAsyncOperation :
    public RenderAsyncBase<ABI::AdaptiveCards::XamlCardRenderer::ImageRenderResult>
{
public:
    RenderCardAsImageAsyncOperation(
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* card)
        : RenderAsyncBase<ABI::AdaptiveCards::XamlCardRenderer::ImageRenderResult>(card)
    {
        AsyncBase::Start();
    }

    STDMETHODIMP ABI::Windows::Foundation::IAsyncOperation_impl<TResult_complex>::GetResults(ABI::AdaptiveCards::XamlCardRenderer::IImageRenderResult** imageRenderResult)
    {
        return m_imageRenderResult.CopyTo(imageRenderResult);
    }

protected:
    HRESULT XamlRenderCompleted(ABI::Windows::Foundation::IAsyncAction* /*action*/, ABI::Windows::Foundation::AsyncStatus /*status*/) override
    {
        return S_OK;
    }

    HRESULT OnXamlImagesLoaded()
    {
        //TODO MSFT:10826539 XamlTileRenderer:Render image via RenderTargetBitmap
        /*
        RETURN_IF_FAILED(Microsoft::WRL::MakeAndInitialize<AdaptiveCards::XamlCardRenderer::RenderXamlToImageExecutionInstance>(&m_runInstance));
        RETURN_IF_FAILED(m_runInstance->SetXamlRoot(m_rootXamlElement.Get()));

        Microsoft::WRL::ComPtr<ABI::Windows::ApplicationModel::Background::IBackgroundTaskInstance> bgTaskInstance;
        m_runInstance.As(&bgTaskInstance);

        Microsoft::WRL::ComPtr<IInspectable> spTaskAsInspectable;
        RETURN_IF_FAILED(Microsoft::WRL::MakeAndInitialize<AdaptiveCards::XamlCardRenderer::RenderXamlToImageTask>(&spTaskAsInspectable));
        RETURN_IF_FAILED(spTaskAsInspectable.As(&m_backgroundTask));

        RETURN_IF_FAILED(m_backgroundTask->Run(bgTaskInstance.Get()));
        */

        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncAction> dispatcherAsyncAction;
        m_dispatcher->RunAsync(ABI::Windows::UI::Core::CoreDispatcherPriority_Normal,
            MakeAgileDispatcherCallback([this]() -> HRESULT
        {
            m_renderTargetBitmap = AdaptiveCards::XamlCardRenderer::XamlHelpers::CreateXamlClass<ABI::Windows::UI::Xaml::Media::Imaging::IRenderTargetBitmap>(Microsoft::WRL::Wrappers::HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_RenderTargetBitmap));
            Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncAction> renderAsyncAction;
            m_renderTargetBitmap->RenderToSizeAsync(m_rootXamlElement.Get(), 100, 100, &renderAsyncAction);

            renderAsyncAction->put_Completed(
                Microsoft::WRL::Callback<ABI::Windows::Foundation::IAsyncActionCompletedHandler>(
                    [this](ABI::Windows::Foundation::IAsyncAction* action, ABI::Windows::Foundation::AsyncStatus status) -> HRESULT
            {
                return RenderTargetBitmapRenderAsyncCompleted(action, status);
            }).Get());

            return S_OK;
        }).Get(),
            &dispatcherAsyncAction);

        return S_OK;
    }


private:
    Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::Imaging::IRenderTargetBitmap> m_renderTargetBitmap;
    Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IImageRenderResult> m_imageRenderResult;

    //Microsoft::WRL::ComPtr<AdaptiveCards::XamlCardRenderer::IRenderXamlToImageExecutionInstance> m_runInstance;
    Microsoft::WRL::ComPtr<ABI::Windows::ApplicationModel::Background::IBackgroundTask> m_backgroundTask;

    HRESULT RenderTargetBitmapRenderAsyncCompleted(ABI::Windows::Foundation::IAsyncAction* /*action*/, ABI::Windows::Foundation::AsyncStatus /*status*/)
    {
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperation<ABI::Windows::Storage::Streams::IBuffer*>> getPixelsAsyncOperation;
        m_renderTargetBitmap->GetPixelsAsync(&getPixelsAsyncOperation);
        getPixelsAsyncOperation->put_Completed(
            Microsoft::WRL::Callback<ABI::Windows::Foundation::IAsyncOperationCompletedHandler<ABI::Windows::Storage::Streams::IBuffer*>>(
                [this](ABI::Windows::Foundation::IAsyncOperation<ABI::Windows::Storage::Streams::IBuffer*>* operation, AsyncStatus /*status*/) -> HRESULT
        {
            Microsoft::WRL::ComPtr<ABI::Windows::Storage::Streams::IBuffer> pixelsBuffer;
            operation->GetResults(&pixelsBuffer);
            return RenderTargetBitmapGetPixelsCompleted(pixelsBuffer.Get());
        }).Get());

        return S_OK;
    }

    HRESULT RenderTargetBitmapGetPixelsCompleted(ABI::Windows::Storage::Streams::IBuffer* /*pixelsBuffer*/)
    {
        int pixelHeight;
        int pixelWidth;
        RETURN_IF_FAILED(m_renderTargetBitmap->get_PixelHeight(&pixelHeight));
        RETURN_IF_FAILED(m_renderTargetBitmap->get_PixelWidth(&pixelWidth));

        //TODO MSFT:10826539 XamlTileRenderer:Render image via RenderTargetBitmap
        //Microsoft::WRL::MakeAndInitialize<ABI::AdaptiveCards::XamlCardRenderer::ImageRenderResult>(&m_imageRenderResult,
            //Microsoft::WRL::Wrappers::HStringReference(L"Alt Text").Get(), pixelsBuffer, pixelWidth, pixelHeight);
                
        return AsyncBase::FireCompletion();
    }
};