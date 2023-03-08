// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
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
        property<ActionRole> Role;

        virtual std::shared_ptr<::AdaptiveCards::BaseActionElement> GetSharedModel() = 0;

        winrt::Windows::Data::Json::JsonObject ToJson();

        void CopySharedElementProperties(::AdaptiveCards::BaseActionElement& sharedCardElement);

        void InitializeBaseElement(const std::shared_ptr<::AdaptiveCards::BaseActionElement>& sharedModel);

        Xaml_OM::FallbackType FallbackType() { return m_fallbackType; }

        void FallbackType(Xaml_OM::FallbackType const& fallback)
        {
            if (fallback != Xaml_OM::FallbackType::Content)
            {
                FallbackContent = nullptr;
            }
            m_fallbackType = fallback;
        }

        Xaml_OM::FallbackType m_fallbackType;
    };
}
