// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "SemanticVersion.h"
#include "BaseElement.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct AdaptiveCardElementBase
    {
        void InitializeBaseElement(const std::shared_ptr<::AdaptiveCards::BaseCardElement>& sharedModel);

        property<winrt::AdaptiveCards::ObjectModel::WinUI3::Spacing> Spacing;
        property<bool> Separator;
        property<bool> IsVisible;
        property<hstring> Id;
        property<uint32_t> InternalId;
        property<hstring> ElementTypeString;
        property<winrt::Windows::Data::Json::JsonObject> AdditionalProperties;
        property<winrt::AdaptiveCards::ObjectModel::WinUI3::HeightType> Height;
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveRequirement>> Requirements;

        winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType FallbackType() { return m_fallbackType; }
        void FallbackType(winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType const& fallback);
        winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement FallbackContent() { return m_fallbackContent; }
        void FallbackContent(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& content);

        winrt::Windows::Data::Json::JsonObject ToJson();

        void CopySharedElementProperties(::AdaptiveCards::BaseCardElement& sharedCardElement);

        virtual std::shared_ptr<::AdaptiveCards::BaseCardElement> GetSharedModel() = 0;

    private:
        winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType m_fallbackType;
        winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement m_fallbackContent;
    };
}
