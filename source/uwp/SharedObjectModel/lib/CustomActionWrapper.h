// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::ObjectModel::Xaml_OM
{
    class CustomActionWrapper : public AdaptiveCards::BaseActionElement
    {
    public:
        CustomActionWrapper(winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveActionElement const& actionElement);

        void SetId(std::string&& value) override;
        void SetId(const std::string& value) override;

        void SetTitle(std::string&& value) override;
        void SetTitle(const std::string& value) override;

        virtual Json::Value SerializeToJsonValue() const override;

        winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveActionElement GetWrappedElement();

        virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

    private:
        std::string GetActionElementId() const;
        void SetActionElementId(const std::string& value);

        std::string GetActionElementTitle() const;
        void SetActionElementTitle(const std::string& value);

        winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveActionElement m_actionElement;
    };
}
