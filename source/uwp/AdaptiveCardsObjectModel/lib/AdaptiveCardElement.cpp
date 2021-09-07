// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardElement.h"
#include "SemanticVersion.h"
#include "ObjectModelUtil.h"
#include "Vector.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveCardElementBase::InitializeBaseElement(const std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel)
    {
        m_spacing = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::Spacing>(sharedModel->GetSpacing());
        m_separator = sharedModel->GetSeparator();
        m_isVisible = sharedModel->GetIsVisible();
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedModel->GetAdditionalProperties(), &m_additionalProperties));
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetElementTypeString(), m_typeString.GetAddressOf()));
        m_height = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::HeightType>(sharedModel->GetHeight());
        m_internalId = sharedModel->GetInternalId().Hash();
        m_fallbackType = MapSharedFallbackTypeToUwp(sharedModel->GetFallbackType());
        if (m_fallbackType == ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content)
        {
            const auto fallbackObject =
                std::static_pointer_cast<AdaptiveCards::BaseCardElement>(sharedModel->GetFallbackContent());
            if (fallbackObject)
            {
                RETURN_IF_FAILED(GenerateElementProjection(fallbackObject, m_fallbackContent.GetAddressOf()));
            }
        }
        m_requirements = Microsoft::WRL::Make<Vector<AdaptiveRequirement*>>();
        GenerateRequirementsProjection(sharedModel->GetRequirements(), m_requirements.Get());
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_Spacing(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_Spacing(ABI::AdaptiveCards::ObjectModel::Uwp::Spacing spacing)
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

    IFACEMETHODIMP AdaptiveCardElementBase::get_FallbackType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType* fallback)
    {
        *fallback = m_fallbackType;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_FallbackContent(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement** content)
    {
        return m_fallbackContent.CopyTo(content);
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_FallbackType(ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType fallback)
    {
        if (fallback != ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content)
        {
            m_fallbackContent.Reset();
        }

        m_fallbackType = fallback;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_FallbackContent(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* content)
    {
        m_fallbackContent = content;

        if (content == nullptr && m_fallbackType == ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content)
        {
            m_fallbackType = ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType::None;
        }
        else if (content != nullptr)
        {
            m_fallbackType = ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content;
        }

        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_Id(_Outptr_ HSTRING* id) { return m_id.CopyTo(id); }

    IFACEMETHODIMP AdaptiveCardElementBase::put_Id(_In_ HSTRING id) { return m_id.Set(id); }

    IFACEMETHODIMP AdaptiveCardElementBase::get_InternalId(_Out_ UINT32* id)
    {
        *id = m_internalId;
        return S_OK;
    }

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

    IFACEMETHODIMP AdaptiveCardElementBase::get_Height(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::HeightType* height)
    {
        *height = m_height;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_Height(ABI::AdaptiveCards::ObjectModel::Uwp::HeightType height)
    {
        m_height = height;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_Requirements(
        ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveRequirement*>** requirements)
    {
        return m_requirements.CopyTo(requirements);
    }

    IFACEMETHODIMP AdaptiveCardElementBase::ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveCards::BaseCardElement> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    HRESULT AdaptiveCardElementBase::CopySharedElementProperties(AdaptiveCards::BaseCardElement& sharedCardElement)
    {
        sharedCardElement.SetId(HStringToUTF8(m_id.Get()));
        sharedCardElement.SetSeparator(m_separator);
        sharedCardElement.SetIsVisible(m_isVisible);
        sharedCardElement.SetSpacing(static_cast<AdaptiveCards::Spacing>(m_spacing));
        sharedCardElement.SetHeight(static_cast<AdaptiveCards::HeightType>(m_height));
        sharedCardElement.SetFallbackType(MapUwpFallbackTypeToShared(m_fallbackType));

        RETURN_IF_FAILED(GenerateSharedRequirements(m_requirements.Get(), sharedCardElement.GetRequirements()));

        if (m_fallbackType == ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content)
        {
            std::shared_ptr<AdaptiveCards::BaseCardElement> fallbackSharedModel;
            RETURN_IF_FAILED(GenerateSharedElement(m_fallbackContent.Get(), fallbackSharedModel));
            sharedCardElement.SetFallbackContent(std::static_pointer_cast<AdaptiveCards::BaseElement>(fallbackSharedModel));
        }

        if (m_additionalProperties != nullptr)
        {
            Json::Value jsonCpp;
            RETURN_IF_FAILED(JsonObjectToJsonCpp(m_additionalProperties.Get(), &jsonCpp));
            sharedCardElement.SetAdditionalProperties(std::move(jsonCpp));
        }

        return S_OK;
    }
}
