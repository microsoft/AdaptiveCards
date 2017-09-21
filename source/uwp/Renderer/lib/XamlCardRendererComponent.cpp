#include "pch.h"
#include "XamlCardRendererComponent.h"

#include "AdaptiveCard.h"
#include "AsyncOperations.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>
#include "XamlBuilder.h"
#include "XamlCardResourceResolvers.h"
#include "XamlHelpers.h"
#include "AdaptiveHostConfig.h"
#include "InputItem.h"
#include "AdaptiveRenderResult.h"

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
        return MakeAndInitialize<XamlCardResourceResolvers>(&m_resourceResolvers);
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
    HRESULT  XamlCardRenderer::SetFixedDimensions(_In_ UINT32 desiredWidth, _In_ UINT32 desiredHeight)
    {
        m_explicitDimensions = true;
        m_desiredWidth = desiredWidth;
        m_desiredHeight = desiredHeight;

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  XamlCardRenderer::ResetFixedDimensions()
    {
        m_explicitDimensions = false;
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
        IAdaptiveRenderResult** result)
    {
        *result = nullptr;
        ComPtr<IUIElement> xamlTreeRoot;
        bool isValid = false;
        auto inputElements = std::make_shared<std::vector<InputItem>>();

        if (adaptiveCard)
        {
            XamlBuilder builder;

            if (m_overrideDictionary != nullptr)
            {
                THROW_IF_FAILED(builder.SetOverrideDictionary(m_overrideDictionary.Get()));
            }

            if (m_hostConfig != nullptr)
            {
                THROW_IF_FAILED(builder.SetHostConfig(m_hostConfig.Get()));
            }

            if (m_explicitDimensions)
            {
                THROW_IF_FAILED(builder.SetFixedDimensions(m_desiredWidth, m_desiredHeight));
            }

            // This path is used for synchronous Xaml card rendering, so we don't want
            // to manually download the image assets and instead just want xaml to do
            // that automatically
            builder.SetEnableXamlImageHandling(true);
            try
            {

                builder.BuildXamlTreeFromAdaptiveCard(adaptiveCard, inputElements, &xamlTreeRoot, this);
                isValid = true;
            }
            catch (...)
            {
                //TODO: Add to Render Errors
                isValid = false;
            }
        }
        else
        {
            //TODO: Add to Render errors.
            isValid = false;
        }
        ComPtr<IAdaptiveRenderResult> renderResult;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderResult>(
            &renderResult,
            isValid,
            adaptiveCard,
            xamlTreeRoot.Get(),
            inputElements));
        ComPtr<IAdaptiveRenderResult> asInterface;
        RETURN_IF_FAILED(renderResult.As(&asInterface));
        *result = asInterface.Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderCardAsXamlAsync(
        IAdaptiveCard* adaptiveCard,
        IAsyncOperation<ABI::AdaptiveCards::XamlCardRenderer::AdaptiveRenderResult*>** result)
    {
        *result = Make<RenderCardAsXamlAsyncOperation>(adaptiveCard, this).Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderAdaptiveJsonAsXaml(
        HSTRING adaptiveJson,
        IAdaptiveRenderResult** result)
    {
        ComPtr<IAdaptiveCard> adaptiveCard;
        HRESULT hr = CreateAdaptiveCardFromJson(adaptiveJson, &adaptiveCard);
        if (FAILED(hr))
        {
            ComPtr<IAdaptiveRenderResult> renderResult;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderResult>(
                &renderResult,
                false,
                nullptr,
                nullptr,
                std::make_shared<std::vector<InputItem>>()));
            ComPtr<IAdaptiveRenderResult> asInterface;
            renderResult.As(&asInterface);
            *result = asInterface.Detach();
            return S_OK;
        }
        else
        {
            return RenderCardAsXaml(adaptiveCard.Get(), result);
        }
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderAdaptiveJsonAsXamlAsync(
        HSTRING adaptiveJson,
        IAsyncOperation<ABI::AdaptiveCards::XamlCardRenderer::AdaptiveRenderResult*>** result)
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
    HRESULT XamlCardRenderer::get_ResourceResolvers(IXamlCardResourceResolvers** value)
    {
        ComPtr<IXamlCardResourceResolvers> localResourceResolvers(m_resourceResolvers);
        *value = localResourceResolvers.Detach();
        return S_OK;
    }

    ABI::Windows::UI::Xaml::IResourceDictionary* XamlCardRenderer::GetOverrideDictionary()
    {
        return m_overrideDictionary.Get();
    }

    bool XamlCardRenderer::GetFixedDimensions(_Out_ UINT32* width, _Out_ UINT32* height)
    {
        *width = 0;
        *height = 0;

        if (m_explicitDimensions)
        {
            *width = m_desiredWidth;
            *height = m_desiredHeight;
        }

        return m_explicitDimensions;
    }

}}