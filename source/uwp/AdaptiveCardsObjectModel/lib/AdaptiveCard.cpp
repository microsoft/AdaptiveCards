// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCard.h"
#include "AdaptiveCardParseResult.h"
#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveCardParseException.h"
#include "AdaptiveError.h"
#include "AdaptiveWarning.h"
#include <BaseCardElement.h>

#include <json.h>
#include "ObjectModelUtil.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveCardStaticsImpl::FromJsonString(_In_ HSTRING adaptiveJson, _COM_Outptr_ IAdaptiveCardParseResult** parseResult) noexcept
    try
    {
        return FromJsonStringWithParserRegistration(adaptiveJson, nullptr, nullptr, parseResult);
    }
    CATCH_RETURN;

    HRESULT AdaptiveCardStaticsImpl::FromJsonStringWithParserRegistration(_In_ HSTRING adaptiveJson,
                                                                          _In_ IAdaptiveElementParserRegistration* elementParserRegistration,
                                                                          _In_ IAdaptiveActionParserRegistration* actionParserRegistration,
                                                                          _COM_Outptr_ IAdaptiveCardParseResult** parseResult) noexcept
    try
    {
        *parseResult = nullptr;

        std::string adaptiveJsonString;
        RETURN_IF_FAILED(HStringToUTF8(adaptiveJson, adaptiveJsonString));

        return _FromJsonString(adaptiveJsonString, elementParserRegistration, actionParserRegistration, parseResult);
    }
    CATCH_RETURN;

    HRESULT AdaptiveCardStaticsImpl::FromJson(_In_ IJsonObject* adaptiveJson, _COM_Outptr_ IAdaptiveCardParseResult** parseResult) noexcept
    try
    {
        return FromJsonWithParserRegistration(adaptiveJson, nullptr, nullptr, parseResult);
    }
    CATCH_RETURN;

    HRESULT AdaptiveCardStaticsImpl::FromJsonWithParserRegistration(_In_ IJsonObject* adaptiveJson,
                                                                    _In_ IAdaptiveElementParserRegistration* elementParserRegistration,
                                                                    _In_ IAdaptiveActionParserRegistration* actionParserRegistration,
                                                                    _COM_Outptr_ IAdaptiveCardParseResult** parseResult) noexcept
    try
    {
        *parseResult = nullptr;

        std::string adaptiveJsonString;
        RETURN_IF_FAILED(JsonObjectToString(adaptiveJson, adaptiveJsonString));

        return _FromJsonString(adaptiveJsonString, elementParserRegistration, actionParserRegistration, parseResult);
    }
    CATCH_RETURN;

    HRESULT AdaptiveCardStaticsImpl::_FromJsonString(const std::string& jsonString,
                                                     _In_ IAdaptiveElementParserRegistration* elementParserRegistration,
                                                     _In_ IAdaptiveActionParserRegistration* actionParserRegistration,
                                                     _COM_Outptr_ IAdaptiveCardParseResult** parseResult)
    {
        std::shared_ptr<ElementParserRegistration> sharedModelElementParserRegistration;
        if (elementParserRegistration != nullptr)
        {
            ComPtr<AdaptiveElementParserRegistration> elementParserRegistrationImpl =
                PeekInnards<AdaptiveElementParserRegistration>(elementParserRegistration);
            if (elementParserRegistrationImpl != nullptr)
            {
                sharedModelElementParserRegistration = elementParserRegistrationImpl->GetSharedParserRegistration();
            }
        }

        std::shared_ptr<ActionParserRegistration> sharedModelActionParserRegistration;
        if (actionParserRegistration != nullptr)
        {
            ComPtr<AdaptiveActionParserRegistration> actionParserRegistrationImpl =
                PeekInnards<AdaptiveActionParserRegistration>(actionParserRegistration);
            if (actionParserRegistrationImpl != nullptr)
            {
                sharedModelActionParserRegistration = actionParserRegistrationImpl->GetSharedParserRegistration();
            }
        }

        ComPtr<AdaptiveCardParseResult> adaptiveParseResult;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCardParseResult>(&adaptiveParseResult));
        try
        {
            ParseContext context(sharedModelElementParserRegistration, sharedModelActionParserRegistration);
            const std::string c_rendererVersion = "1.5";
            std::shared_ptr<AdaptiveCards::ParseResult> sharedParseResult =
                AdaptiveCards::AdaptiveCard::DeserializeFromString(jsonString, c_rendererVersion, context);
            ComPtr<IAdaptiveCard> adaptiveCard;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCard>(&adaptiveCard, sharedParseResult->GetAdaptiveCard()));
            RETURN_IF_FAILED(adaptiveParseResult->put_AdaptiveCard(adaptiveCard.Get()));

            ComPtr<IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning*>> warnings;
            RETURN_IF_FAILED(adaptiveParseResult->get_Warnings(&warnings));

            RETURN_IF_FAILED(SharedWarningsToAdaptiveWarnings(sharedParseResult->GetWarnings(), warnings.Get()));

            return adaptiveParseResult.CopyTo(parseResult);
        }
        catch (const AdaptiveCardParseException& e)
        {
            ComPtr<IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveError*>> errors;
            RETURN_IF_FAILED(adaptiveParseResult->get_Errors(&errors));
            HString errorMessage;
            ABI::AdaptiveCards::ObjectModel::Uwp::ErrorStatusCode statusCode =
                static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ErrorStatusCode>(e.GetStatusCode());
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

    HRESULT AdaptiveCard::RuntimeClassInitialize(std::shared_ptr<AdaptiveCards::AdaptiveCard> sharedAdaptiveCard)
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

        m_style = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle>(sharedAdaptiveCard->GetStyle());
        m_verticalAlignment = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>(
            sharedAdaptiveCard->GetVerticalContentAlignment());
        m_height = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::HeightType>(sharedAdaptiveCard->GetHeight());
        m_minHeight = sharedAdaptiveCard->GetMinHeight();

        auto backgroundImage = sharedAdaptiveCard->GetBackgroundImage();
        if (backgroundImage != nullptr && !backgroundImage->GetUrl().empty())
        {
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveBackgroundImage>(m_backgroundImage.GetAddressOf(), backgroundImage));
        }

        auto refresh = sharedAdaptiveCard->GetRefresh();
        if (refresh != nullptr)
        {
            MakeAndInitialize<AdaptiveRefresh>(m_refresh.GetAddressOf(), refresh);
        }

        auto authentication = sharedAdaptiveCard->GetAuthentication();
        if (authentication != nullptr)
        {
            MakeAndInitialize<AdaptiveAuthentication>(m_authentication.GetAddressOf(), authentication);
        }

        m_internalId = sharedAdaptiveCard->GetInternalId().Hash();

        return S_OK;
    }

    HRESULT AdaptiveCard::get_InternalId(_Out_ UINT32* id)
    {
        *id = m_internalId;
        return S_OK;
    }

    HRESULT AdaptiveCard::get_Version(_Outptr_ HSTRING* version) { return m_version.CopyTo(version); }

    HRESULT AdaptiveCard::put_Version(_In_ HSTRING version) { return m_version.Set(version); }

    HRESULT AdaptiveCard::get_FallbackText(_Outptr_ HSTRING* fallbackText)
    {
        return m_fallbackText.CopyTo(fallbackText);
    }

    HRESULT AdaptiveCard::put_FallbackText(_In_ HSTRING fallbackText) { return m_fallbackText.Set(fallbackText); }

    HRESULT AdaptiveCard::get_Language(_Outptr_ HSTRING* language) { return m_language.CopyTo(language); }

    HRESULT AdaptiveCard::put_Language(_In_ HSTRING language) { return m_language.Set(language); }

    HRESULT AdaptiveCard::get_Body(_COM_Outptr_ IVector<IAdaptiveCardElement*>** body) { return m_body.CopyTo(body); }

    HRESULT AdaptiveCard::get_Actions(_COM_Outptr_ IVector<IAdaptiveActionElement*>** actions)
    {
        return m_actions.CopyTo(actions);
    }

    HRESULT AdaptiveCard::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::AdaptiveCard;
        return S_OK;
    }

    HRESULT AdaptiveCard::get_BackgroundImage(_Outptr_ IAdaptiveBackgroundImage** backgroundImage)
    {
        return m_backgroundImage.CopyTo(backgroundImage);
    }

    HRESULT AdaptiveCard::put_BackgroundImage(_In_ IAdaptiveBackgroundImage* backgroundImage)
    {
        m_backgroundImage = backgroundImage;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCard::get_SelectAction(_COM_Outptr_ IAdaptiveActionElement** action)
    {
        return m_selectAction.CopyTo(action);
    }

    IFACEMETHODIMP AdaptiveCard::put_SelectAction(_In_ IAdaptiveActionElement* action)
    {
        m_selectAction = action;
        return S_OK;
    }

    HRESULT AdaptiveCard::get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    HRESULT AdaptiveCard::put_Style(ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    HRESULT AdaptiveCard::get_Speak(_Outptr_ HSTRING* speak) { return m_speak.CopyTo(speak); }

    HRESULT AdaptiveCard::put_Speak(_In_ HSTRING speak) { return m_speak.Set(speak); }

    HRESULT AdaptiveCard::get_VerticalContentAlignment(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment* verticalAlignment)
    {
        *verticalAlignment = m_verticalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveCard::put_VerticalContentAlignment(ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment verticalAlignment)
    {
        m_verticalAlignment = verticalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveCard::get_Height(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::HeightType* heightType)
    {
        *heightType = m_height;
        return S_OK;
    }

    HRESULT AdaptiveCard::put_Height(ABI::AdaptiveCards::ObjectModel::Uwp::HeightType heightType)
    {
        m_height = heightType;
        return S_OK;
    }

    HRESULT AdaptiveCard::get_MinHeight(_Out_ UINT32* minHeight)
    {
        *minHeight = m_minHeight;
        return S_OK;
    }

    HRESULT AdaptiveCard::put_MinHeight(UINT32 minHeight)
    {
        m_minHeight = minHeight;
        return S_OK;
    }

    HRESULT AdaptiveCard::get_Refresh(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveRefresh** refresh)
    {
        return m_refresh.CopyTo(refresh);
    }

    HRESULT AdaptiveCard::put_Refresh(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveRefresh* refresh)
    {
        m_refresh = refresh;
        return S_OK;
    }

    HRESULT AdaptiveCard::get_Authentication(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveAuthentication** authentication)
    {
        return m_authentication.CopyTo(authentication);
    }

    HRESULT AdaptiveCard::put_Authentication(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveAuthentication* authentication)
    {
        m_authentication = authentication;
        return S_OK;
    }

    HRESULT AdaptiveCard::ToJson(_COM_Outptr_ IJsonObject** result)
    {
        std::shared_ptr<AdaptiveCards::AdaptiveCard> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    HRESULT AdaptiveCard::GetSharedModel(std::shared_ptr<AdaptiveCards::AdaptiveCard>& sharedModel)
    {
        std::shared_ptr<AdaptiveCards::AdaptiveCard> adaptiveCard = std::make_shared<AdaptiveCards::AdaptiveCard>();

        adaptiveCard->SetVersion(HStringToUTF8(m_version.Get()));
        adaptiveCard->SetFallbackText(HStringToUTF8(m_fallbackText.Get()));
        adaptiveCard->SetSpeak(HStringToUTF8(m_speak.Get()));
        adaptiveCard->SetHeight(static_cast<AdaptiveCards::HeightType>(m_height));
        adaptiveCard->SetLanguage(HStringToUTF8(m_language.Get()));
        adaptiveCard->SetMinHeight(m_minHeight);

        ComPtr<AdaptiveBackgroundImage> adaptiveBackgroundImage = PeekInnards<AdaptiveBackgroundImage>(m_backgroundImage);
        std::shared_ptr<AdaptiveCards::BackgroundImage> sharedBackgroundImage;
        if (adaptiveBackgroundImage && SUCCEEDED(adaptiveBackgroundImage->GetSharedModel(sharedBackgroundImage)))
        {
            adaptiveCard->SetBackgroundImage(std::move(sharedBackgroundImage));
        }

        adaptiveCard->SetStyle(static_cast<AdaptiveCards::ContainerStyle>(m_style));
        adaptiveCard->SetVerticalContentAlignment(static_cast<AdaptiveCards::VerticalContentAlignment>(m_verticalAlignment));

        if (m_selectAction != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_selectAction.Get(), sharedAction));
            adaptiveCard->SetSelectAction(std::move(sharedAction));
        }

        GenerateSharedElements(m_body.Get(), adaptiveCard->GetBody());
        GenerateSharedActions(m_actions.Get(), adaptiveCard->GetActions());

        if (m_refresh)
        {
            ComPtr<AdaptiveRefresh> refreshImpl = PeekInnards<AdaptiveRefresh>(m_refresh);

            std::shared_ptr<AdaptiveCards::Refresh> sharedModelRefresh;
            RETURN_IF_FAILED(refreshImpl->GetSharedModel(sharedModelRefresh));
            adaptiveCard->SetRefresh(sharedModelRefresh);
        }

        if (m_authentication)
        {
            ComPtr<AdaptiveAuthentication> authenticationImpl = PeekInnards<AdaptiveAuthentication>(m_authentication);

            std::shared_ptr<AdaptiveCards::Authentication> sharedModelAuthentication;
            RETURN_IF_FAILED(authenticationImpl->GetSharedModel(sharedModelAuthentication));
            adaptiveCard->SetAuthentication(sharedModelAuthentication);
        }

        sharedModel = std::move(adaptiveCard);
        return S_OK;
    }

    HRESULT AdaptiveCard::GetResourceInformation(
        _COM_Outptr_ ABI::Windows::Foundation::Collections::IVectorView<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveRemoteResourceInformation*>** resourceInformationView)
    {
        std::shared_ptr<AdaptiveCards::AdaptiveCard> sharedModel;
        GetSharedModel(sharedModel);

        std::vector<RemoteResourceInformation> sharedResourceInformationVector = sharedModel->GetResourceInformation();

        ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveRemoteResourceInformation*>> resourceInformation =
            Make<Vector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveRemoteResourceInformation*>>();
        for (auto sharedResourceInformation : sharedResourceInformationVector)
        {
            ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveRemoteResourceInformation> remoteResourceInformation;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRemoteResourceInformation>(remoteResourceInformation.GetAddressOf(),
                                                                                  sharedResourceInformation));

            HString resourceUriHString;
            RETURN_IF_FAILED(UTF8ToHString(sharedResourceInformation.url, resourceUriHString.GetAddressOf()));
            RETURN_IF_FAILED(remoteResourceInformation->put_Url(resourceUriHString.Get()));

            HString mimeType;
            RETURN_IF_FAILED(UTF8ToHString(sharedResourceInformation.mimeType, mimeType.GetAddressOf()));
            RETURN_IF_FAILED(remoteResourceInformation->put_MimeType(mimeType.Get()));

            RETURN_IF_FAILED(resourceInformation->Append(remoteResourceInformation.Get()));
        }

        RETURN_IF_FAILED(resourceInformation->GetView(resourceInformationView));

        return S_OK;
    }
}
