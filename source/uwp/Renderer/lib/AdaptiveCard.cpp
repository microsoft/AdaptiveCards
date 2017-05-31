#include "pch.h"
#include "AdaptiveCard.h"

#include <json.h>
#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    _Use_decl_annotations_
    HRESULT AdaptiveCardStaticsImpl::CreateCardFromJson(HSTRING adaptiveJson, IAdaptiveCard** card) noexcept try
    {
        *card = nullptr;

        std::string adaptiveJsonString;
        RETURN_IF_FAILED(HStringToUTF8(adaptiveJson, adaptiveJsonString));

        std::shared_ptr<::AdaptiveCards::AdaptiveCard> sharedAdaptiveCard = ::AdaptiveCards::AdaptiveCard::DeserializeFromString(adaptiveJsonString);
        return MakeAndInitialize<AdaptiveCard>(card, sharedAdaptiveCard);
    } CATCH_RETURN;

    HRESULT AdaptiveCard::RuntimeClassInitialize()
    {
        m_sharedAdaptiveCard = std::make_shared<AdaptiveCards::AdaptiveCard>();
       
        m_body = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
        if (m_body == nullptr)
        {
            return E_FAIL;
        }
        
        m_actions = Microsoft::WRL::Make<Vector<IAdaptiveActionElement*>>();
        if (m_actions == nullptr)
        {
            return E_FAIL;
        }        
        
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::RuntimeClassInitialize(std::shared_ptr<::AdaptiveCards::AdaptiveCard> sharedAdaptiveCard)
    {
        RETURN_IF_FAILED(RuntimeClassInitialize());
        m_sharedAdaptiveCard = sharedAdaptiveCard;

        RETURN_IF_FAILED(GenerateContainedElementsProjection(m_sharedAdaptiveCard->GetBody(), m_body.Get()));

        RETURN_IF_FAILED(GenerateActionsProjection(m_sharedAdaptiveCard->GetActions(), m_actions.Get()));

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Version(HSTRING* version)
    {
        return UTF8ToHString(m_sharedAdaptiveCard->GetVersion(), version);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_Version(HSTRING version)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(version, out));
        m_sharedAdaptiveCard->SetVersion(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_MinVersion(HSTRING* minVersion)
    {
        return UTF8ToHString(m_sharedAdaptiveCard->GetMinVersion(), minVersion);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_MinVersion(HSTRING minVersion)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(minVersion, out));
        m_sharedAdaptiveCard->SetMinVersion(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_FallbackText(HSTRING* fallbackText)
    {
        return UTF8ToHString(m_sharedAdaptiveCard->GetFallbackText(), fallbackText);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_FallbackText(HSTRING fallbackText)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(fallbackText, out));
        m_sharedAdaptiveCard->SetFallbackText(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Body(IVector<IAdaptiveCardElement*>** body)
    {
        return m_body.CopyTo(body);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Actions(IVector<IAdaptiveActionElement*>** actions)
    {
        return m_actions.CopyTo(actions);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::AdaptiveCard;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_BackgroundImageUrl(IUriRuntimeClass** url)
    {
        *url = nullptr;
        ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
        RETURN_IF_FAILED(GetActivationFactory(
            HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(),
            &uriActivationFactory));

        HSTRING imageUri;
        RETURN_IF_FAILED(UTF8ToHString(m_sharedAdaptiveCard->GetBackgroundImageUrl(), &imageUri));
        RETURN_IF_FAILED(uriActivationFactory->CreateUri(imageUri, url));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_BackgroundImageUrl(IUriRuntimeClass* url) try
    {
        if (url == nullptr)
        {
            return E_INVALIDARG;
        }

        HString urlTemp;
        url->get_AbsoluteUri(urlTemp.GetAddressOf());

        std::string urlString;
        RETURN_IF_FAILED(HStringToUTF8(urlTemp.Get(), urlString));
        m_sharedAdaptiveCard->SetBackgroundImageUrl(urlString);

        return S_OK;
    } CATCH_RETURN;
}}