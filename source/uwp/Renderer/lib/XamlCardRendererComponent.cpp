#include "pch.h"
#include "XamlCardRendererComponent.h"

#include "AdaptiveCard.h"
#include "AsyncOperations.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>
#include "XamlBuilder.h"
#include "XamlCardImageResolvers.h"
#include "XamlHelpers.h"
#include "AdaptiveHostConfig.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Storage::Streams;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Core;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    XamlCardRenderer::XamlCardRenderer()
    {
    }

    HRESULT XamlCardRenderer::RuntimeClassInitialize()
    {
        m_events.reset(new ActionEventSource);
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveHostConfig>(&m_hostConfig));
        RETURN_IF_FAILED(MakeAndInitialize<XamlCardImageResolvers>(&m_imageResolvers));
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::SetRenderOptions(ABI::AdaptiveCards::XamlCardRenderer::RenderOptions /*options*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::SetOverrideStyles(ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary)
    {
        m_overrideDictionary = overrideDictionary;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  XamlCardRenderer::SetHostConfig(IAdaptiveHostConfig* hostConfig)
    {
        m_hostConfig = hostConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::add_Action(
        ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::XamlCardRenderer::XamlCardRenderer*, ABI::AdaptiveCards::XamlCardRenderer::AdaptiveActionEventArgs*>* handler,
        EventRegistrationToken* token)
    {
        return m_events->Add(handler, token);
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::remove_Action(EventRegistrationToken token)
    {
        return m_events->Remove(token);
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderCardAsXaml(
        IAdaptiveCard* adaptiveCard, 
        IUIElement** result) try
    {
        *result = nullptr;

        if (adaptiveCard)
        {
            XamlBuilder builder;
            ComPtr<IUIElement> xamlTreeRoot;
            
            if (m_overrideDictionary != nullptr)
            {
                builder.SetOverrideDictionary(m_overrideDictionary.Get());
            }

            if (m_hostConfig != nullptr)
            {
                builder.SetHostConfig(m_hostConfig.Get());
            }

            // This path is used for synchronous Xaml card rendering, so we don't want
            // to manually download the image assets and instead just want xaml to do
            // that automatically
            builder.SetEnableXamlImageHandling(true);

            builder.BuildXamlTreeFromAdaptiveCard(adaptiveCard, &xamlTreeRoot, this);
            *result = xamlTreeRoot.Detach();
        }

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderCardAsXamlAsync(
        IAdaptiveCard* adaptiveCard,
        IAsyncOperation<UIElement*>** result)
    {
        *result = Make<RenderCardAsXamlAsyncOperation>(adaptiveCard, this).Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderAdaptiveJsonAsXaml(
        HSTRING adaptiveJson,
        IUIElement** result)
    {
        ComPtr<IAdaptiveCard> adaptiveCard;
        RETURN_IF_FAILED(CreateAdaptiveCardFromJson(adaptiveJson, &adaptiveCard));

        return RenderCardAsXaml(adaptiveCard.Get(), result);
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderAdaptiveJsonAsXamlAsync(
        HSTRING adaptiveJson,
        IAsyncOperation<UIElement*>** result)
    {
        ComPtr<IAdaptiveCard> adaptiveCard;
        RETURN_IF_FAILED(CreateAdaptiveCardFromJson(adaptiveJson, &adaptiveCard));

        return RenderCardAsXamlAsync(adaptiveCard.Get(), result);
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::CreateAdaptiveCardFromJson(HSTRING adaptiveJson, ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard** adaptiveCard)
    {
        ComPtr<IAdaptiveCardStatics> adaptiveCardStatics;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCardStaticsImpl>(&adaptiveCardStatics));
        RETURN_IF_FAILED(adaptiveCardStatics->CreateCardFromJson(adaptiveJson, adaptiveCard));
        return S_OK;
    }

    HRESULT XamlCardRenderer::SendActionEvent(IAdaptiveActionEventArgs* eventArgs)
    {
        return m_events->InvokeAll(this, eventArgs);
    }

    IAdaptiveHostConfig* XamlCardRenderer::GetHostConfig()
    {
        return m_hostConfig.Get();
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::get_ImageResolvers(IXamlCardImageResolvers** value)
    {
        ComPtr<IXamlCardImageResolvers> localImageResolvers(m_imageResolvers);
        *value = localImageResolvers.Detach();
        return S_OK;
    }
}}