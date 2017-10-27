#include "pch.h"
#include "AdaptiveCard.h"
#include "AdaptiveCardParseResult.h"
#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveElementParserRegistration.h"

#include <json.h>
#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveCards { namespace Uwp
{
    _Use_decl_annotations_
    HRESULT AdaptiveCardStaticsImpl::FromJsonString(HSTRING adaptiveJson, IAdaptiveCardParseResult** parseResult) noexcept try
    {
        return FromJsonStringWithParserRegistration(adaptiveJson, nullptr, nullptr, parseResult);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveCardStaticsImpl::FromJsonStringWithParserRegistration(
        HSTRING adaptiveJson, 
        IAdaptiveElementParserRegistration* elementParserRegistration,
        IAdaptiveActionParserRegistration* actionParserRegistration,
        IAdaptiveCardParseResult** parseResult) noexcept try
    {
        *parseResult = nullptr;

        std::string adaptiveJsonString;
        RETURN_IF_FAILED(HStringToUTF8(adaptiveJson, adaptiveJsonString));

        return FromJsonString(adaptiveJsonString, elementParserRegistration, actionParserRegistration, parseResult);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveCardStaticsImpl::FromJson(IJsonObject* adaptiveJson, IAdaptiveCardParseResult** parseResult) noexcept try
    {
        return FromJsonWithParserRegistration(adaptiveJson, nullptr, nullptr, parseResult);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveCardStaticsImpl::FromJsonWithParserRegistration(
        IJsonObject* adaptiveJson, 
        IAdaptiveElementParserRegistration* elementParserRegistration,
        IAdaptiveActionParserRegistration* actionParserRegistration,
        IAdaptiveCardParseResult** parseResult) noexcept try
    {
        *parseResult = nullptr;

        std::string adaptiveJsonString;
        RETURN_IF_FAILED(JsonObjectToString(adaptiveJson, adaptiveJsonString));

        return FromJsonString(adaptiveJsonString, elementParserRegistration, actionParserRegistration, parseResult);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveCardStaticsImpl::FromJsonString(
        const std::string jsonString, 
        IAdaptiveElementParserRegistration* elementParserRegistration,
        IAdaptiveActionParserRegistration* actionParserRegistration, 
        IAdaptiveCardParseResult** parseResult)
    {
        std::shared_ptr<ElementParserRegistration> sharedModelElementParserRegistration;
        if (elementParserRegistration != nullptr)
        {
            ComPtr<AdaptiveElementParserRegistration> elementParserRegistrationImpl = PeekInnards<AdaptiveElementParserRegistration>(elementParserRegistration);
            if (elementParserRegistrationImpl != nullptr)
            {
                sharedModelElementParserRegistration = elementParserRegistrationImpl->GetSharedParserRegistration();
            }
        }

        std::shared_ptr<ActionParserRegistration> sharedModelActionParserRegistration;
        if (actionParserRegistration != nullptr)
        {
            ComPtr<AdaptiveActionParserRegistration> actionParserRegistrationImpl = PeekInnards<AdaptiveActionParserRegistration>(actionParserRegistration);
            if (actionParserRegistrationImpl != nullptr)
            {
                sharedModelActionParserRegistration = actionParserRegistrationImpl->GetSharedParserRegistration();
            }
        }

        std::shared_ptr<::AdaptiveCards::AdaptiveCard> sharedAdaptiveCard = ::AdaptiveCards::AdaptiveCard::DeserializeFromString(jsonString, sharedModelElementParserRegistration, sharedModelActionParserRegistration);

        ComPtr<IAdaptiveCard> adaptiveCard;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCard>(&adaptiveCard, sharedAdaptiveCard));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCardParseResult>(parseResult, adaptiveCard.Get()));
        return S_OK;
    }

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
    HRESULT AdaptiveCard::get_BackgroundImage(IUriRuntimeClass** url)
    {
        *url = nullptr;
        ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
        RETURN_IF_FAILED(GetActivationFactory(
            HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(),
            &uriActivationFactory));

        HSTRING imageUri;
        RETURN_IF_FAILED(UTF8ToHString(m_sharedAdaptiveCard->GetBackgroundImage(), &imageUri));
        RETURN_IF_FAILED(uriActivationFactory->CreateUri(imageUri, url));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_BackgroundImage(IUriRuntimeClass* url) try
    {
        if (url == nullptr)
        {
            return E_INVALIDARG;
        }

        HString urlTemp;
        url->get_AbsoluteUri(urlTemp.GetAddressOf());

        std::string urlString;
        RETURN_IF_FAILED(HStringToUTF8(urlTemp.Get(), urlString));
        m_sharedAdaptiveCard->SetBackgroundImage(urlString);

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Style(ABI::AdaptiveCards::Uwp::ContainerStyle* style)
    {
        *style = static_cast<ABI::AdaptiveCards::Uwp::ContainerStyle>(m_sharedAdaptiveCard->GetStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_Style(ABI::AdaptiveCards::Uwp::ContainerStyle style)
    {
        m_sharedAdaptiveCard->SetStyle(static_cast<AdaptiveCards::ContainerStyle>(style));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedAdaptiveCard->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedAdaptiveCard->SetSpeak(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::ToJson(IJsonObject** result)
    {
        return StringToJsonObject(m_sharedAdaptiveCard->Serialize(), result);
    }
}}