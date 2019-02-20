#include "pch.h"
#include "AdaptiveCardElement.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    static ABI::AdaptiveNamespace::FallbackType MapSharedFallbackTypeToUwp(const AdaptiveSharedNamespace::FallbackType type)
    {
        switch (type)
        {
            case FallbackType::Drop:
            {
                return ABI::AdaptiveNamespace::FallbackType::Drop;
            }

            case FallbackType::Content:
            {
                return ABI::AdaptiveNamespace::FallbackType::Content;
            }

            case FallbackType::None:
            default:
            {
                return ABI::AdaptiveNamespace::FallbackType::None;
            }
        }
    }

    static AdaptiveSharedNamespace::FallbackType MapUwpFallbackTypeToShared(const ABI::AdaptiveNamespace::FallbackType type)
    {
        switch (type)
        {
            case ABI::AdaptiveNamespace::FallbackType::Drop:
            {
                return FallbackType::Drop;
            }

            case ABI::AdaptiveNamespace::FallbackType::Content:
            {
                return FallbackType::Content;
            }

            case ABI::AdaptiveNamespace::FallbackType::None:
            default:
            {
                return FallbackType::None;
            }
        }
    }

    HRESULT AdaptiveCardElementBase::InitializeBaseElement(const std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel)
    {
        m_spacing = static_cast<ABI::AdaptiveNamespace::Spacing>(sharedModel->GetSpacing());
        m_separator = sharedModel->GetSeparator();
        m_isVisible = sharedModel->GetIsVisible();
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedModel->GetAdditionalProperties(), &m_additionalProperties));
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetElementTypeString(), m_typeString.GetAddressOf()));
        m_height = static_cast<ABI::AdaptiveNamespace::HeightType>(sharedModel->GetHeight());
        m_fallbackType = MapSharedFallbackTypeToUwp(sharedModel->GetFallbackType());
        if (m_fallbackType == ABI::AdaptiveNamespace::FallbackType::Content)
        {
            const auto fallbackObject = std::static_pointer_cast<AdaptiveSharedNamespace::BaseCardElement>(sharedModel->GetFallbackContent());
            if (fallbackObject)
            {
                RETURN_IF_FAILED(GenerateElementProjection(fallbackObject, m_fallbackContent.GetAddressOf()));
            }
        }

        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_Spacing(ABI::AdaptiveNamespace::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_Separator(_Out_ boolean* separator)
    {
        *separator = m_separator;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_Separator(boolean separator)
    {
        m_separator = separator;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_IsVisible(_Out_ boolean* isVisible)
    {
        *isVisible = m_isVisible;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_IsVisible(boolean isVisible)
    {
        m_isVisible = isVisible;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_FallbackType(_Out_ ABI::AdaptiveNamespace::FallbackType * fallback)
    {
        *fallback = m_fallbackType;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_FallbackContent(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement ** content)
    {
        return m_fallbackContent.CopyTo(content);
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_Id(_Outptr_ HSTRING* id) { return m_id.CopyTo(id); }

    IFACEMETHODIMP AdaptiveCardElementBase::put_Id(_In_ HSTRING id) { return m_id.Set(id); }

    IFACEMETHODIMP AdaptiveCardElementBase::get_ElementTypeString(_Outptr_ HSTRING* type)
    {
        return m_typeString.CopyTo(type);
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_AdditionalProperties(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_Height(_Out_ ABI::AdaptiveNamespace::HeightType* height)
    {
        *height = m_height;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_Height(ABI::AdaptiveNamespace::HeightType height)
    {
        m_height = height;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    HRESULT AdaptiveCardElementBase::SetSharedElementProperties(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> sharedCardElement)
    {
        sharedCardElement->SetId(HStringToUTF8(m_id.Get()));
        sharedCardElement->SetSeparator(m_separator);
        sharedCardElement->SetIsVisible(m_isVisible);
        sharedCardElement->SetSpacing(static_cast<AdaptiveSharedNamespace::Spacing>(m_spacing));
        sharedCardElement->SetHeight(static_cast<AdaptiveSharedNamespace::HeightType>(m_height));
        sharedCardElement->SetFallbackType(MapUwpFallbackTypeToShared(m_fallbackType));

        if (m_fallbackType == ABI::AdaptiveNamespace::FallbackType::Content)
        {
            ComPtr<AdaptiveNamespace::AdaptiveCardElementBase> fallbackElement = PeekInnards<AdaptiveNamespace::AdaptiveCardElementBase>(m_fallbackContent);
            std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> fallbackSharedModel;
            RETURN_IF_FAILED(fallbackElement->GetSharedModel(fallbackSharedModel));
            sharedCardElement->SetFallbackContent(std::static_pointer_cast<AdaptiveSharedNamespace::BaseElement>(fallbackSharedModel));
        }

        if (m_additionalProperties != nullptr)
        {
            Json::Value jsonCpp;
            RETURN_IF_FAILED(JsonObjectToJsonCpp(m_additionalProperties.Get(), &jsonCpp));
            sharedCardElement->SetAdditionalProperties(jsonCpp);
        }

        return S_OK;
    }
}
