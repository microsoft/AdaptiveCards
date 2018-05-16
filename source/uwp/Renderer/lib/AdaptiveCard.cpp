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

using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

AdaptiveNamespaceStart
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
            std::shared_ptr<AdaptiveSharedNamespace::ParseResult> sharedParseResult = AdaptiveSharedNamespace::AdaptiveCard::DeserializeFromString(jsonString, c_rendererVersion, sharedModelElementParserRegistration, sharedModelActionParserRegistration);
            ComPtr<IAdaptiveCard> adaptiveCard;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCard>(&adaptiveCard, sharedParseResult->GetAdaptiveCard()));
            RETURN_IF_FAILED(adaptiveParseResult->put_AdaptiveCard(adaptiveCard.Get()));

            ComPtr<IVector<IAdaptiveWarning*>> warnings;
            RETURN_IF_FAILED(adaptiveParseResult->get_Warnings(&warnings));

            for (auto sharedWarning : sharedParseResult->GetWarnings())
            {
                HString warningMessage;
                RETURN_IF_FAILED(UTF8ToHString(sharedWarning->GetReason(), warningMessage.GetAddressOf()));
                            
                ABI::AdaptiveNamespace::WarningStatusCode statusCode = static_cast<ABI::AdaptiveNamespace::WarningStatusCode>(sharedWarning->GetStatusCode());

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
            ABI::AdaptiveNamespace::ErrorStatusCode statusCode = static_cast<ABI::AdaptiveNamespace::ErrorStatusCode>(e.GetStatusCode());
            RETURN_IF_FAILED(UTF8ToHString(e.GetReason(), errorMessage.GetAddressOf()));
            ComPtr<IAdaptiveError> adaptiveError;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveError>(&adaptiveError, statusCode, errorMessage.Get()));
            RETURN_IF_FAILED(errors->Append(adaptiveError.Get()));
            return adaptiveParseResult.CopyTo(parseResult);
        }
    }

    HRESULT AdaptiveCard::RuntimeClassInitialize()
    {
        std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard> adaptiveCard = std::make_shared<AdaptiveSharedNamespace::AdaptiveCard>();
        return RuntimeClassInitialize(adaptiveCard);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveCard::RuntimeClassInitialize(std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard> sharedAdaptiveCard)
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
        RETURN_IF_FAILED(GenerateActionProjection(sharedAdaptiveCard->GetSelectAction(), &m_selectAction));

        RETURN_IF_FAILED(UTF8ToHString(sharedAdaptiveCard->GetVersion(), m_version.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedAdaptiveCard->GetFallbackText(), m_fallbackText.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedAdaptiveCard->GetSpeak(), m_speak.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedAdaptiveCard->GetLanguage(), m_language.GetAddressOf()));

        m_style = static_cast<ABI::AdaptiveNamespace::ContainerStyle>(sharedAdaptiveCard->GetStyle());

        RETURN_IF_FAILED(UTF8ToHString(sharedAdaptiveCard->GetBackgroundImage(), m_backgroundImageUrl.GetAddressOf()));

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
    HRESULT AdaptiveCard::get_Language(HSTRING* language)
    {
        return m_language.CopyTo(language);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_Language(HSTRING language)
    {
        return m_language.Set(language);
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
    HRESULT AdaptiveCard::get_BackgroundImage(HSTRING* backgroundImageUri)
    {
        return m_backgroundImageUrl.CopyTo(backgroundImageUri);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_BackgroundImageUrl(HSTRING backgroundImageUri)
    {
        return m_backgroundImageUrl.Set(backgroundImageUri);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveCard::get_SelectAction(IAdaptiveActionElement** action)
    {
        return m_selectAction.CopyTo(action);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveCard::put_SelectAction(IAdaptiveActionElement* action)
    {
        m_selectAction = action;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Style(ABI::AdaptiveNamespace::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_Style(ABI::AdaptiveNamespace::ContainerStyle style)
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
        std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    HRESULT AdaptiveCard::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard>& sharedModel)
    {
        std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard> adaptiveCard = std::make_shared<AdaptiveSharedNamespace::AdaptiveCard>();

        adaptiveCard->SetVersion(HStringToUTF8(m_version.Get()));
        adaptiveCard->SetFallbackText(HStringToUTF8(m_fallbackText.Get()));
        adaptiveCard->SetSpeak(HStringToUTF8(m_speak.Get()));
        adaptiveCard->SetLanguage(HStringToUTF8(m_language.Get()));
        adaptiveCard->SetBackgroundImage(HStringToUTF8(m_backgroundImageUrl.Get()));

        adaptiveCard->SetStyle(static_cast<AdaptiveSharedNamespace::ContainerStyle>(m_style));

        if (m_selectAction != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_selectAction.Get(), sharedAction));
            adaptiveCard->SetSelectAction(sharedAction);
        }

        GenerateSharedElements(m_body.Get(), adaptiveCard->GetBody());
        GenerateSharedActions(m_actions.Get(), adaptiveCard->GetActions());

        sharedModel = adaptiveCard;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::GetResourceUris(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVectorView<ABI::Windows::Foundation::Uri*>** uris)
    {
        std::shared_ptr<AdaptiveCards::AdaptiveCard> sharedModel;
        GetSharedModel(sharedModel);

        std::vector<std::string> resourceUriStrings = sharedModel->GetResourceUris();

        ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
        RETURN_IF_FAILED(GetActivationFactory(
            HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(),
            &uriActivationFactory));

        ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::Windows::Foundation::Uri*>> resourceUris = Make<Vector<Uri*>>();
        for (auto resourceUriString : resourceUriStrings)
        {
            HString resourceUriHString;
            RETURN_IF_FAILED(UTF8ToHString(resourceUriString, resourceUriHString.GetAddressOf()));
         
            ComPtr<IUriRuntimeClass> resourceUri;
            RETURN_IF_FAILED(uriActivationFactory->CreateUri(resourceUriHString.Get(), resourceUri.GetAddressOf()));

            RETURN_IF_FAILED(resourceUris->Append(resourceUri.Get()));
        }

        RETURN_IF_FAILED(resourceUris->GetView(uris));

        return S_OK;
    }
AdaptiveNamespaceEnd