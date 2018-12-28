#include "pch.h"
#include "AdaptiveActionElement.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveActionElementBase::InitializeBaseElement(const std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel)
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetTitle(), m_title.GetAddressOf()));

        RETURN_IF_FAILED(JsonCppToJsonObject(sharedModel->GetAdditionalProperties(), &m_additionalProperties));
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetElementTypeString(), m_typeString.GetAddressOf()));

        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetIconUrl(), m_iconUrl.GetAddressOf()));

        m_sentiment = static_cast<ABI::AdaptiveNamespace::Sentiment>(sharedModel->GetSentiment());

        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_Title(_Outptr_ HSTRING* title) { return m_title.CopyTo(title); }

    IFACEMETHODIMP AdaptiveActionElementBase::put_Title(_In_ HSTRING title) { return m_title.Set(title); }

    IFACEMETHODIMP AdaptiveActionElementBase::get_Id(_Outptr_ HSTRING* id) { return m_id.CopyTo(id); }

    IFACEMETHODIMP AdaptiveActionElementBase::put_Id(_In_ HSTRING id) { return m_id.Set(id); }

    HRESULT AdaptiveActionElementBase::get_IconUrl(_Outptr_ HSTRING* iconUrl) { return m_iconUrl.CopyTo(iconUrl); }

    HRESULT AdaptiveActionElementBase::put_IconUrl(_In_ HSTRING iconUrl) { return m_iconUrl.Set(iconUrl); }

    IFACEMETHODIMP AdaptiveActionElementBase::get_Sentiment(_Out_ ABI::AdaptiveNamespace::Sentiment* sentiment)
    {
        *sentiment = m_sentiment;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::put_Sentiment(ABI::AdaptiveNamespace::Sentiment sentiment)
    {
        m_sentiment = sentiment;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_AdditionalProperties(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    IFACEMETHODIMP AdaptiveActionElementBase::put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveActionElementBase::get_ActionTypeString(_Outptr_ HSTRING* type)
    {
        return m_typeString.CopyTo(type);
    }

    IFACEMETHODIMP AdaptiveActionElementBase::ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    HRESULT AdaptiveActionElementBase::SetSharedElementProperties(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> sharedCardElement)
    {
        sharedCardElement->SetId(HStringToUTF8(m_id.Get()));
        sharedCardElement->SetTitle(HStringToUTF8(m_title.Get()));
        sharedCardElement->SetIconUrl(HStringToUTF8(m_iconUrl.Get()));
        sharedCardElement->SetSentiment(static_cast<AdaptiveSharedNamespace::Sentiment>(m_sentiment));

        if (m_additionalProperties != nullptr)
        {
            Json::Value jsonCpp;
            RETURN_IF_FAILED(JsonObjectToJsonCpp(m_additionalProperties.Get(), &jsonCpp));
            sharedCardElement->SetAdditionalProperties(jsonCpp);
        }

        return S_OK;
    }
}
