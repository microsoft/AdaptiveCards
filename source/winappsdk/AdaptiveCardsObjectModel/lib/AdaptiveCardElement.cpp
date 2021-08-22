// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardElement.h"
#include "SemanticVersion.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation::Collections;

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    void AdaptiveCardElementBase::InitializeBaseElement(const std::shared_ptr<::AdaptiveCards::BaseCardElement>& sharedModel)
    {
        Spacing = static_cast<winrt::AdaptiveCards::ObjectModel::WinUI3::Spacing>(sharedModel->GetSpacing());
        Separator = sharedModel->GetSeparator();
        IsVisible = sharedModel->GetIsVisible();
        Id = UTF8ToHString(sharedModel->GetId());
        AdditionalProperties = JsonCppToJsonObject(sharedModel->GetAdditionalProperties());
        ElementTypeString = UTF8ToHString(sharedModel->GetElementTypeString());
        Height = static_cast<winrt::AdaptiveCards::ObjectModel::WinUI3::HeightType>(sharedModel->GetHeight());
        InternalId = sharedModel->GetInternalId().Hash();
        m_fallbackType = MapSharedFallbackTypeToWinUI3(sharedModel->GetFallbackType());
        if (m_fallbackType == winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType::Content)
        {
            if (auto fallbackObject = sharedModel->GetFallbackContent())
            {
                m_fallbackContent = GenerateElementProjection(fallbackObject);
            }
        }
        Requirements = GenerateRequirementsProjection(sharedModel->GetRequirements());
    }

    void AdaptiveCardElementBase::FallbackType(winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType const& fallback)
    {
        if (fallback != winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType::Content)
        {
            m_fallbackContent = nullptr;
        }

        m_fallbackType = fallback;
    }

    void AdaptiveCardElementBase::FallbackContent(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& content)
    {
        m_fallbackContent = content;

        if (content == nullptr && m_fallbackType == winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType::Content)
        {
            m_fallbackType = winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType::None;
        }
        else if (content != nullptr)
        {
            m_fallbackType = winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType::Content;
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
        sharedCardElement.SetFallbackType(MapWinUI3FallbackTypeToShared(m_fallbackType));

        sharedCardElement.GetRequirements() = GenerateSharedRequirements(Requirements);

        if (m_fallbackType == winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType::Content)
        {
            sharedCardElement.SetFallbackContent(GenerateSharedElement(m_fallbackContent));
        }

        if (AdditionalProperties != nullptr)
        {
            sharedCardElement.SetAdditionalProperties(JsonObjectToJsonCpp(AdditionalProperties));
        }
    }
}
