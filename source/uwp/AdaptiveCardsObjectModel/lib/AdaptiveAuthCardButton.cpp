// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveAuthCardButton.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveAuthCardButton::RuntimeClassInitialize() noexcept
    {
        std::shared_ptr<AdaptiveCards::AuthCardButton> authCardButton = std::make_shared<AdaptiveCards::AuthCardButton>();
        return RuntimeClassInitialize(authCardButton);
    }

    HRESULT AdaptiveAuthCardButton::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::AuthCardButton>& sharedAuthCardButton)
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedAuthCardButton->GetType(), m_type.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedAuthCardButton->GetTitle(), m_title.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedAuthCardButton->GetImage(), m_image.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedAuthCardButton->GetValue(), m_value.GetAddressOf()));

        return S_OK;
    }

    HRESULT AdaptiveAuthCardButton::get_Type(_Outptr_ HSTRING* type) { return m_type.CopyTo(type); }

    HRESULT AdaptiveAuthCardButton::put_Type(_In_ HSTRING type) { return m_type.Set(type); }

    HRESULT AdaptiveAuthCardButton::get_Title(_Outptr_ HSTRING* title) { return m_title.CopyTo(title); }

    HRESULT AdaptiveAuthCardButton::put_Title(_In_ HSTRING title) { return m_title.Set(title); }

    HRESULT AdaptiveAuthCardButton::get_Image(_Outptr_ HSTRING* image) { return m_image.CopyTo(image); }

    HRESULT AdaptiveAuthCardButton::put_Image(_In_ HSTRING image) { return m_image.Set(image); }

    HRESULT AdaptiveAuthCardButton::get_Value(_Outptr_ HSTRING* value) { return m_value.CopyTo(value); }

    HRESULT AdaptiveAuthCardButton::put_Value(_In_ HSTRING value) { return m_value.Set(value); }

    HRESULT AdaptiveAuthCardButton::GetSharedModel(std::shared_ptr<AdaptiveCards::AuthCardButton>& sharedModel)
    {
        std::shared_ptr<AdaptiveCards::AuthCardButton> authCardButton = std::make_shared<AdaptiveCards::AuthCardButton>();

        std::string type;
        RETURN_IF_FAILED(HStringToUTF8(m_type.Get(), type));
        authCardButton->SetType(type);

        std::string title;
        RETURN_IF_FAILED(HStringToUTF8(m_title.Get(), title));
        authCardButton->SetTitle(title);

        std::string image;
        RETURN_IF_FAILED(HStringToUTF8(m_image.Get(), image));
        authCardButton->SetImage(image);

        std::string value;
        RETURN_IF_FAILED(HStringToUTF8(m_value.Get(), value));
        authCardButton->SetValue(value);

        sharedModel = std::move(authCardButton);
        return S_OK;
    }
}
