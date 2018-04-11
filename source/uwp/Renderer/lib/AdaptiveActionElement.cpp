#include "pch.h"
#include "AdaptiveActionElement.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

AdaptiveNamespaceStart
    HRESULT AdaptiveActionElementBase::InitializeBaseElement(const std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel)
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetTitle(), m_title.GetAddressOf()));

        RETURN_IF_FAILED(JsonCppToJsonObject(sharedModel->GetAdditionalProperties(), &m_additionalProperties));
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetElementTypeString(), m_typeString.GetAddressOf()));

        ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
        RETURN_IF_FAILED(GetActivationFactory(
            HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(),
            &uriActivationFactory));

        std::wstring iconUrl = StringToWstring(sharedModel->GetIconUrl());
        if (!iconUrl.empty())
        {
            RETURN_IF_FAILED(uriActivationFactory->CreateUri(HStringReference(iconUrl.c_str()).Get(), m_iconUrl.GetAddressOf()));
        }

        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_Title(HSTRING* title)
    {
        return m_title.CopyTo(title);
    }

    IFACEMETHODIMP AdaptiveActionElementBase::put_Title(HSTRING title)
    {
        return m_title.Set(title);
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_Id(HSTRING* id)
    {
        return m_id.CopyTo(id);
    }

    IFACEMETHODIMP AdaptiveActionElementBase::put_Id(HSTRING id)
    {
        return m_id.Set(id);
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_IconUrl(IUriRuntimeClass** iconUrl)
    {
        return m_iconUrl.CopyTo(iconUrl);
    }

    IFACEMETHODIMP AdaptiveActionElementBase::put_IconUrl(IUriRuntimeClass* iconUrl)
    {
        m_iconUrl = iconUrl;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    IFACEMETHODIMP AdaptiveActionElementBase::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_ActionTypeString(HSTRING* type)
    {
        return m_typeString.CopyTo(type);
    }

    IFACEMETHODIMP AdaptiveActionElementBase::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    HRESULT AdaptiveActionElementBase::SetSharedElementProperties(
        std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> sharedCardElement)
    {
        sharedCardElement->SetId(HStringToUTF8(m_id.Get()));
        sharedCardElement->SetTitle(HStringToUTF8(m_title.Get()));

        if (m_additionalProperties != nullptr)
        {
            Json::Value jsonCpp;
            RETURN_IF_FAILED(JsonObjectToJsonCpp(m_additionalProperties.Get(), &jsonCpp));
            sharedCardElement->SetAdditionalProperties(jsonCpp);
        }

        return S_OK;
    }
AdaptiveNamespaceEnd
