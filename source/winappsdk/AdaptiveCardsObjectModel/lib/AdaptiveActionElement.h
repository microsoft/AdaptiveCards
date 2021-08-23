// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct AdaptiveActionElementBase
    {
        property<hstring> Id;
        property<hstring> Title;
        property<hstring> IconUrl;
        property<hstring> Style;
        property<hstring> Tooltip;
        property<uint32_t> InternalId;
        property<winrt::Windows::Data::Json::JsonObject> AdditionalProperties;

        property<IAdaptiveActionElement> FallbackContent;
        property<ActionMode> Mode;
        property<hstring> ActionTypeString;
        property<bool> IsEnabled;

        virtual std::shared_ptr<::AdaptiveCards::BaseActionElement> GetSharedModel() = 0;

        winrt::Windows::Data::Json::JsonObject ToJson();

        void CopySharedElementProperties(::AdaptiveCards::BaseActionElement& sharedCardElement);

        void InitializeBaseElement(const std::shared_ptr<::AdaptiveCards::BaseActionElement>& sharedModel);

        WinUI3::FallbackType FallbackType() { return m_fallbackType; }

        void FallbackType(WinUI3::FallbackType const& fallback)
        {
            if (fallback != WinUI3::FallbackType::Content)
            {
                FallbackContent = nullptr;
            }
            m_fallbackType = fallback;
        }

        WinUI3::FallbackType m_fallbackType;
    };
}
