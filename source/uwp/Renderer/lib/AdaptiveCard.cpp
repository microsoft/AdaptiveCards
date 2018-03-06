#include "pch.h"
#include "AdaptiveCard.h"
#include "AdaptiveCardParseResult.h"
#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveCardParseException.h"
#include "AdaptiveError.h"
#include "AdaptiveWarning.h"

#include <json.h>
#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveCards { namespace Rendering { namespace Uwp
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

        ComPtr<AdaptiveCardParseResult> adaptiveParseResult;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCardParseResult>(&adaptiveParseResult));
        try
        {
            const double c_rendererVersion = 1.0;
            std::shared_ptr<::AdaptiveCards::ParseResult> sharedParseResult = ::AdaptiveCards::AdaptiveCard::DeserializeFromString(jsonString, c_rendererVersion, sharedModelElementParserRegistration, sharedModelActionParserRegistration);
            ComPtr<IAdaptiveCard> adaptiveCard;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCard>(&adaptiveCard, sharedParseResult->GetAdaptiveCard()));
            RETURN_IF_FAILED(adaptiveParseResult->put_AdaptiveCard(adaptiveCard.Get()));

            ComPtr<IVector<IAdaptiveWarning*>> warnings;
            RETURN_IF_FAILED(adaptiveParseResult->get_Warnings(&warnings));

            for (auto sharedWarning : sharedParseResult->GetWarnings())
            {
                HString warningMessage;
                RETURN_IF_FAILED(UTF8ToHString(sharedWarning->GetReason(), warningMessage.GetAddressOf()));
                            
                ABI::AdaptiveCards::Rendering::Uwp::WarningStatusCode statusCode = static_cast<ABI::AdaptiveCards::Rendering::Uwp::WarningStatusCode>(sharedWarning->GetStatusCode());

                ComPtr<IAdaptiveWarning> adaptiveWarning;
                RETURN_IF_FAILED(MakeAndInitialize<AdaptiveWarning>(&adaptiveWarning, statusCode, warningMessage.Get()));

                RETURN_IF_FAILED(warnings->Append(adaptiveWarning.Get()));
            }

            return adaptiveParseResult.CopyTo(parseResult);
        }
        catch (const AdaptiveCardParseException& e)
        {
            ComPtr<IVector<IAdaptiveError*>> errors;
            RETURN_IF_FAILED(adaptiveParseResult->get_Errors(&errors));
            HString errorMessage;
            ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode statusCode = static_cast<ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode>(e.GetStatusCode());
            RETURN_IF_FAILED(UTF8ToHString(e.GetReason(), errorMessage.GetAddressOf()));
            ComPtr<IAdaptiveError> adaptiveError;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveError>(&adaptiveError, statusCode, errorMessage.Get()));
            RETURN_IF_FAILED(errors->Append(adaptiveError.Get()));
            return adaptiveParseResult.CopyTo(parseResult);
        }
    }

    HRESULT AdaptiveCard::RuntimeClassInitialize()
    {
        std::shared_ptr<AdaptiveCards::AdaptiveCard> adaptiveCard = std::make_shared<AdaptiveCards::AdaptiveCard>();
        return RuntimeClassInitialize(adaptiveCard);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::RuntimeClassInitialize(std::shared_ptr<::AdaptiveCards::AdaptiveCard> sharedAdaptiveCard)
    {
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

        RETURN_IF_FAILED(GenerateContainedElementsProjection(sharedAdaptiveCard->GetBody(), m_body.Get()));
        RETURN_IF_FAILED(GenerateActionsProjection(sharedAdaptiveCard->GetActions(), m_actions.Get()));

        RETURN_IF_FAILED(UTF8ToHString(sharedAdaptiveCard->GetVersion(), m_version.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedAdaptiveCard->GetFallbackText(), m_fallbackText.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedAdaptiveCard->GetSpeak(), m_speak.GetAddressOf()));

        m_style = static_cast<ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle>(sharedAdaptiveCard->GetStyle());

        ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
        RETURN_IF_FAILED(GetActivationFactory(
            HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(),
            &uriActivationFactory));

        HSTRING imageUri;
        RETURN_IF_FAILED(UTF8ToHString(sharedAdaptiveCard->GetBackgroundImage(), &imageUri));
        if (imageUri != nullptr)
        {
            RETURN_IF_FAILED(uriActivationFactory->CreateUri(imageUri, m_backgroundImage.GetAddressOf()));
        }

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Version(HSTRING* version)
    {
        return m_version.CopyTo(version);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_Version(HSTRING version)
    {
        return m_version.Set(version);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_FallbackText(HSTRING* fallbackText)
    {
        return m_fallbackText.CopyTo(fallbackText);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_FallbackText(HSTRING fallbackText)
    {
        return m_fallbackText.Set(fallbackText);
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
        return m_backgroundImage.CopyTo(url);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_BackgroundImage(IUriRuntimeClass* url) try
    {
        m_backgroundImage = url;
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Style(ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_Style(ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Speak(HSTRING* speak)
    {
        return m_speak.CopyTo(speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_Speak(HSTRING speak)
    {
        return m_speak.Set(speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::ToJson(IJsonObject** result)
    {
        std::shared_ptr<AdaptiveCards::AdaptiveCard> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::GetSharedModel(std::shared_ptr<AdaptiveCards::AdaptiveCard>& sharedModel)
    {
        std::shared_ptr<AdaptiveCards::AdaptiveCard> adaptiveCard = std::make_shared<AdaptiveCards::AdaptiveCard>();

        adaptiveCard->SetVersion(HStringToUTF8(m_version.Get()));
        adaptiveCard->SetFallbackText(HStringToUTF8(m_fallbackText.Get()));
        adaptiveCard->SetSpeak(HStringToUTF8(m_speak.Get()));

        if (m_backgroundImage != nullptr)
        {
            HString urlTemp;
            m_backgroundImage->get_AbsoluteUri(urlTemp.GetAddressOf());
            std::string urlString;
            RETURN_IF_FAILED(HStringToUTF8(urlTemp.Get(), urlString));
            adaptiveCard->SetBackgroundImage(urlString);
        }

        adaptiveCard->SetStyle(static_cast<AdaptiveCards::ContainerStyle>(m_style));

        GenerateSharedElements(m_body.Get(), adaptiveCard->GetBody());
        GenerateSharedActions(m_actions.Get(), adaptiveCard->GetActions());

        sharedModel = adaptiveCard;
        return S_OK;
    }
}}}
