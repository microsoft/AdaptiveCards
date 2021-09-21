// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "SemanticVersion.h"
#include "BaseElement.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct AdaptiveCardElementBase
    {
        void InitializeBaseElement(const std::shared_ptr<::AdaptiveCards::BaseCardElement>& sharedModel);

        property<Uwp::Spacing> Spacing;
        property<bool> Separator;
        property<bool> IsVisible;
        property<hstring> Id;
        property<uint32_t> InternalId;
        property<hstring> ElementTypeString;
        property<winrt::Windows::Data::Json::JsonObject> AdditionalProperties;
        property<Uwp::HeightType> Height;
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveRequirement>> Requirements;

        winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType FallbackType() { return m_fallbackType; }
        void FallbackType(winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType const& fallback);
        winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement FallbackContent() { return m_fallbackContent; }
        void FallbackContent(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement const& content);

        winrt::Windows::Data::Json::JsonObject ToJson();

        void CopySharedElementProperties(::AdaptiveCards::BaseCardElement& sharedCardElement);

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() = 0;

    private:
        winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType m_fallbackType;
        winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement m_fallbackContent;
    };
}
