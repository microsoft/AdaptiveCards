// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveAuthentication.h"
#include "AdaptiveTokenExchangeResource.h"
#include "AdaptiveAuthCardButton.h"

#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveAuthentication::RuntimeClassInitialize() noexcept
    {
        std::shared_ptr<AdaptiveCards::Authentication> authentication = std::make_shared<AdaptiveCards::Authentication>();
        return RuntimeClassInitialize(authentication);
    }

    HRESULT AdaptiveAuthentication::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Authentication>& sharedAuthentication)
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedAuthentication->GetText(), m_text.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedAuthentication->GetConnectionName(), m_connectionName.GetAddressOf()));

        auto tokenExchangeResource = sharedAuthentication->GetTokenExchangeResource();
        if (tokenExchangeResource != nullptr)
        {
            MakeAndInitialize<AdaptiveTokenExchangeResource>(m_tokenExchangeResource.GetAddressOf(), tokenExchangeResource);
        }

        m_buttons = Microsoft::WRL::Make<Vector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveAuthCardButton*>>();
        for (auto& button : sharedAuthentication->GetButtons())
        {
            ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveAuthCardButton> adaptiveAuthCardButton;
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveAuthCardButton>(&adaptiveAuthCardButton, button));

            RETURN_IF_FAILED(m_buttons->Append(adaptiveAuthCardButton.Detach()));
        }

        return S_OK;
    }

    HRESULT AdaptiveAuthentication::get_Text(_Outptr_ HSTRING* text) { return m_text.CopyTo(text); }

    HRESULT AdaptiveAuthentication::put_Text(_In_ HSTRING text) { return m_text.Set(text); }

    HRESULT AdaptiveAuthentication::get_ConnectionName(_Outptr_ HSTRING* connectionName)
    {
        return m_connectionName.CopyTo(connectionName);
    }

    HRESULT AdaptiveAuthentication::put_ConnectionName(_In_ HSTRING connectionName)
    {
        return m_connectionName.Set(connectionName);
    }

    HRESULT AdaptiveAuthentication::get_TokenExchangeResource(
        _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTokenExchangeResource** tokenExchangeResource)
    {
        return m_tokenExchangeResource.CopyTo(tokenExchangeResource);
    }

    HRESULT AdaptiveAuthentication::put_TokenExchangeResource(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTokenExchangeResource* tokenExchangeResource)
    {
        m_tokenExchangeResource = tokenExchangeResource;
        return S_OK;
    }

    HRESULT AdaptiveAuthentication::get_Buttons(_COM_Outptr_ IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveAuthCardButton*>** buttons)
    {
        return m_buttons.CopyTo(buttons);
    }

    HRESULT AdaptiveAuthentication::GetSharedModel(std::shared_ptr<AdaptiveCards::Authentication>& sharedModel)
    {
        std::shared_ptr<AdaptiveCards::Authentication> authentication = std::make_shared<AdaptiveCards::Authentication>();

        std::string text;
        RETURN_IF_FAILED(HStringToUTF8(m_text.Get(), text));
        authentication->SetText(text);

        std::string connectionName;
        RETURN_IF_FAILED(HStringToUTF8(m_connectionName.Get(), connectionName));
        authentication->SetConnectionName(connectionName);

        if (m_tokenExchangeResource)
        {
            ComPtr<AdaptiveTokenExchangeResource> tokenExchangeResourceImpl =
                PeekInnards<AdaptiveTokenExchangeResource>(m_tokenExchangeResource);

            std::shared_ptr<AdaptiveCards::TokenExchangeResource> sharedModelTokenExchangeResource;
            RETURN_IF_FAILED(tokenExchangeResourceImpl->GetSharedModel(sharedModelTokenExchangeResource));
            authentication->SetTokenExchangeResource(sharedModelTokenExchangeResource);
        }

        if (m_buttons)
        {
            IterateOverVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveAuthCardButton, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveAuthCardButton>(
                m_buttons.Get(), [&](ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveAuthCardButton* authCardButton) {
                    ComPtr<AdaptiveCards::Rendering::Uwp::AdaptiveAuthCardButton> buttonImpl =
                        PeekInnards<AdaptiveCards::Rendering::Uwp::AdaptiveAuthCardButton>(authCardButton);

                    std::shared_ptr<AdaptiveCards::AuthCardButton> sharedAuthCardButton;
                    RETURN_IF_FAILED(buttonImpl->GetSharedModel(sharedAuthCardButton));
                    authentication->GetButtons().push_back(std::AdaptivePointerCast<AdaptiveCards::AuthCardButton>(sharedAuthCardButton));
                    return S_OK;
                });
        }

        sharedModel = std::move(authentication);
        return S_OK;
    }
}
