// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionElement.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    winrt::Windows::Data::Json::JsonObject AdaptiveActionElementBase::ToJson()
    {
        return StringToJsonObject(GetSharedModel()->Serialize());
    }

    void AdaptiveActionElementBase::CopySharedElementProperties(::AdaptiveCards::BaseActionElement& sharedCardElement)
    {
        sharedCardElement.SetId(HStringToUTF8(Id));
        sharedCardElement.SetTitle(HStringToUTF8(Title));
        sharedCardElement.SetIconUrl(HStringToUTF8(IconUrl));
        sharedCardElement.SetStyle(HStringToUTF8(Style));
        sharedCardElement.SetTooltip(HStringToUTF8(Tooltip));
        sharedCardElement.SetFallbackType(MapUwpFallbackTypeToShared(m_fallbackType));
        sharedCardElement.SetIsEnabled(IsEnabled.get());
        sharedCardElement.SetMode(static_cast<::AdaptiveCards::Mode>(Mode.get()));

        if (m_fallbackType == FallbackType::Content)
        {
            auto fallbackSharedModel = GenerateSharedAction(FallbackContent);
            sharedCardElement.SetFallbackContent(std::static_pointer_cast<::AdaptiveCards::BaseElement>(fallbackSharedModel));
        }

        if (AdditionalProperties.get() != nullptr)
        {
            sharedCardElement.SetAdditionalProperties(JsonObjectToJsonCpp(AdditionalProperties));
        }
    }

    void AdaptiveActionElementBase::InitializeBaseElement(const std::shared_ptr<::AdaptiveCards::BaseActionElement>& sharedModel)
    {
        Id = UTF8ToHString(sharedModel->GetId());
        Title = UTF8ToHString(sharedModel->GetTitle());

        AdditionalProperties = JsonCppToJsonObject(sharedModel->GetAdditionalProperties());
        ActionTypeString = UTF8ToHString(sharedModel->GetElementTypeString());

        IconUrl = UTF8ToHString(sharedModel->GetIconUrl());
        Style = UTF8ToHString(sharedModel->GetStyle());
        Tooltip = UTF8ToHString(sharedModel->GetTooltip());
        Mode = static_cast<Uwp::ActionMode>(sharedModel->GetMode());

        IsEnabled = sharedModel->GetIsEnabled();

        InternalId = sharedModel->GetInternalId().Hash();
        m_fallbackType = static_cast<Uwp::FallbackType>(MapSharedFallbackTypeToUwp(sharedModel->GetFallbackType()));
        if (m_fallbackType == Uwp::FallbackType::Content)
        {
            if (auto fallback = std::static_pointer_cast<::AdaptiveCards::BaseActionElement>(sharedModel->GetFallbackContent()))
            {
                FallbackContent = GenerateActionProjection(fallback);
            }
        }
    }

}
