// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.ObjectModel.WinUI3.h"
#include "ObjectModelUtil.h"

namespace AdaptiveCards::ObjectModel::WinUI3
{
    class CustomElementWrapper : public AdaptiveCards::BaseCardElement
    {
    public:
        CustomElementWrapper(_In_ winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement);

        bool GetSeparator() const override;
        void SetSeparator(bool value) override;

        Spacing GetSpacing() const override;
        void SetSpacing(Spacing value) override;

        void SetId(std::string&& value) override;
        void SetId(const std::string& value) override;

        virtual Json::Value SerializeToJsonValue() const override;

        virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

        winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement GetWrappedElement();

    private:
        std::string GetCardElementId() const;
        void SetCardElementId(const std::string& value);

        winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement m_cardElement;
    };
}
