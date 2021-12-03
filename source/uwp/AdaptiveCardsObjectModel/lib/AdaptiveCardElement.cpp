// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardElement.h"
#include "SemanticVersion.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    void AdaptiveCardElementBase::InitializeBaseElement(const std::shared_ptr<::AdaptiveCards::BaseCardElement>& sharedModel)
    {
        Spacing = static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::Spacing>(sharedModel->GetSpacing());
        Separator = sharedModel->GetSeparator();
        IsVisible = sharedModel->GetIsVisible();
        Id = UTF8ToHString(sharedModel->GetId());
        AdditionalProperties = JsonCppToJsonObject(sharedModel->GetAdditionalProperties());
        ElementTypeString = UTF8ToHString(sharedModel->GetElementTypeString());
        Height = static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::HeightType>(sharedModel->GetHeight());
        InternalId = sharedModel->GetInternalId().Hash();
        m_fallbackType = MapSharedFallbackTypeToUwp(sharedModel->GetFallbackType());
        if (m_fallbackType == winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content)
        {
            if (auto fallbackObject = sharedModel->GetFallbackContent())
            {
                m_fallbackContent = GenerateElementProjection(std::static_pointer_cast<::AdaptiveCards::BaseCardElement>(fallbackObject));
            }
        }
        Requirements = GenerateRequirementsProjection(sharedModel->GetRequirements());
    }

    void AdaptiveCardElementBase::FallbackType(winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType const& fallback)
    {
        if (fallback != winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content)
        {
            m_fallbackContent = nullptr;
        }

        m_fallbackType = fallback;
    }

    void AdaptiveCardElementBase::FallbackContent(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement const& content)
    {
        m_fallbackContent = content;

        if (content == nullptr && m_fallbackType == winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content)
        {
            m_fallbackType = winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType::None;
        }
        else if (content != nullptr)
        {
            m_fallbackType = winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content;
        }
    }

    winrt::Windows::Data::Json::JsonObject AdaptiveCardElementBase::ToJson()
    {
        return StringToJsonObject(GetSharedModel()->Serialize());
    }

    void AdaptiveCardElementBase::CopySharedElementProperties(::AdaptiveCards::BaseCardElement& sharedCardElement)
    {
        sharedCardElement.SetId(HStringToUTF8(Id));
        sharedCardElement.SetSeparator(Separator);
        sharedCardElement.SetIsVisible(IsVisible);
        sharedCardElement.SetSpacing(static_cast<::AdaptiveCards::Spacing>(Spacing.get()));
        sharedCardElement.SetHeight(static_cast<::AdaptiveCards::HeightType>(Height.get()));
        sharedCardElement.SetFallbackType(MapUwpFallbackTypeToShared(m_fallbackType));

        sharedCardElement.GetRequirements() = GenerateSharedRequirements(Requirements);

        if (m_fallbackType == winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content)
        {
            sharedCardElement.SetFallbackContent(GenerateSharedElement(m_fallbackContent));
        }

        if (AdditionalProperties != nullptr)
        {
            sharedCardElement.SetAdditionalProperties(JsonObjectToJsonCpp(AdditionalProperties));
        }
    }
}
